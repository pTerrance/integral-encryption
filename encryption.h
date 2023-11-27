#include <cstdint>
#include <array>
#include <ranges>
#include <cmath>
#include <bit>
#include <bitset>
#include <algorithm>

namespace enc {
#define ENCRYPTION_FORCEINLINE __forceinline

static constexpr std::size_t kEncryptionDepth = 100;

template<std::integral auto T>
concept NonZero = T != 0;

template<std::uint64_t X, std::uint64_t Y, std::uint64_t Z> requires NonZero<Y> && NonZero<Z>
struct Seeder {
  using Next = Seeder<0x19BAFFBED * X + 0x12D687,
                      ((Y ^ (Y << 13)) ^ ((Y ^ (Y << 13)) >> 17)) ^ (((Y ^ (Y << 13)) ^ ((Y ^ (Y << 13)) >> 17)) << 43),
                      Z + (Z << 58)>;
  static constexpr std::uint64_t kValue = X + Y + Z;
};

template<std::uint64_t X, std::uint64_t Y, std::uint64_t Z>
struct SafeSeeder : Seeder<X, Y == 0 ? 1 : Y, Z == 0 ? 1 : Z> {};

template<std::uint64_t Iterations, std::uint64_t Seed>
struct CompileTimeRandom {
  friend CompileTimeRandom<Iterations + 1, Seed>;
  using Current = typename CompileTimeRandom<Iterations - 1, Seed>::Current::Next;
  static constexpr std::uint64_t kValue = Current::kValue;
};

template<std::uint64_t Seed>
struct CompileTimeRandom<0, Seed> {
  friend CompileTimeRandom<1, Seed>;
  using Current = typename SafeSeeder<Seed ^ 0x3C9A83566FA12,
                                      Seed ^ 0x507A1F38CB440C4,
                                      Seed ^ 0x112210F4B16C1CB1>::Next;
  static constexpr std::uint64_t kValue = Current::kValue;
};

template<std::uint64_t Iteration, uint64_t Seed>
static constexpr std::uint64_t kCompileTimeRandomValue = CompileTimeRandom<Iteration, Seed>::kValue;

static constexpr std::uint64_t kRandomTimeBasedSeed =
	kCompileTimeRandomValue<0, (__TIME__[0]) ^
		kCompileTimeRandomValue<0, (__TIME__[1]) ^
			kCompileTimeRandomValue<0, (__TIME__[3]) ^
				kCompileTimeRandomValue<0, (__TIME__[4]) ^
					kCompileTimeRandomValue<0, (__TIME__[6]) ^
						kCompileTimeRandomValue<0, (__TIME__[7])>>>>>> ^
		kCompileTimeRandomValue<0, (__TIMESTAMP__[0]) ^
			kCompileTimeRandomValue<0, (__TIMESTAMP__[1]) ^
				kCompileTimeRandomValue<0, (__TIMESTAMP__[2]) ^
					kCompileTimeRandomValue<0, (__TIMESTAMP__[4]) ^
						kCompileTimeRandomValue<0, (__TIMESTAMP__[5]) ^
							kCompileTimeRandomValue<0, (__TIMESTAMP__[6])>>>>>> ^
		kCompileTimeRandomValue<0, (__TIMESTAMP__[8]) ^
			kCompileTimeRandomValue<0, (__TIMESTAMP__[9]) ^
				kCompileTimeRandomValue<0, (__TIMESTAMP__[20]) ^
					kCompileTimeRandomValue<0, (__TIMESTAMP__[21]) ^
						kCompileTimeRandomValue<0, (__TIMESTAMP__[22]) ^
							kCompileTimeRandomValue<0, (__TIMESTAMP__[23])>>>>>>;

static constexpr std::uint64_t kRandomSeed = 0xEC0DEADBEEFC0FFE ^ kRandomTimeBasedSeed;

enum class OperationType { kAdd, kSub, kXor, kRotateLeft, kRotateRight };

static constexpr std::size_t kAmountOperations = 5;

template<OperationType, std::integral T>
struct Operations;

template<std::integral T>
struct Operations<OperationType::kAdd, T> {
  ENCRYPTION_FORCEINLINE static constexpr void Do(T &data, const T value) noexcept { data += value; }
  ENCRYPTION_FORCEINLINE static constexpr void Undo(volatile T &data, const T value) noexcept { data -= value; }
};
template<std::integral T>
struct Operations<OperationType::kSub, T> {
  ENCRYPTION_FORCEINLINE static constexpr void Do(T &data, const T value) noexcept { data -= value; }
  ENCRYPTION_FORCEINLINE static constexpr void Undo(volatile T &data, const T value) noexcept { data += value; }
};
template<std::integral T>
struct Operations<OperationType::kXor, T> {
  ENCRYPTION_FORCEINLINE static constexpr void Do(T &data, const T value) noexcept { data ^= value; }
  ENCRYPTION_FORCEINLINE static constexpr void Undo(volatile T &data, const T value) noexcept { data ^= value; }
};
template<std::integral T>
struct Operations<OperationType::kRotateLeft, T> {
  ENCRYPTION_FORCEINLINE static constexpr void Do(T &data, const T value) noexcept { data = std::rotl(data,static_cast<int>(value)); }
  ENCRYPTION_FORCEINLINE static constexpr void Undo(volatile T &data, const T value) noexcept { data = std::rotr(data, static_cast<int>(value)); }
};
template<std::integral T>
struct Operations<OperationType::kRotateRight, T> {
  ENCRYPTION_FORCEINLINE static constexpr void Do(T &data, const T value) noexcept { data = std::rotr(data, static_cast<int>(value)); }
  ENCRYPTION_FORCEINLINE static constexpr void Undo(volatile T &data, const T value) noexcept { data = std::rotl(data, static_cast<int>(value)); }
};

template<std::size_t N>
struct Num { static constexpr std::size_t kIndex = N; };

template<class F, std::size_t... Is>
ENCRYPTION_FORCEINLINE consteval void ConstevalFor(const F func, const std::index_sequence<Is...>) noexcept {
  using Expander = int[];
  (void) Expander{0, ((void) func(Num<Is>{}), 0)...};
}

template<std::size_t N, typename F>
ENCRYPTION_FORCEINLINE consteval void ConstevalFor(const F func) noexcept {
  ConstevalFor(func, std::make_index_sequence<N>());
}

template<class F, std::size_t... Is>
ENCRYPTION_FORCEINLINE constexpr void ConstexprFor(const F func, const std::index_sequence<Is...>) noexcept {
  using Expander = int[];
  (void) Expander{0, ((void) func(Num<Is>{}), 0)...};
}

template<std::size_t N, typename F>
ENCRYPTION_FORCEINLINE constexpr void ConstexprFor(const F func) noexcept {
  ConstexprFor(func, std::make_index_sequence<N>());
}

ENCRYPTION_FORCEINLINE constexpr std::uint64_t RandomRuntime(const std::uint64_t iterations = 0,
                                                             const std::uint64_t seed = kRandomSeed) noexcept {
  std::uint64_t x = seed ^ 0x3C9A83566FA12;
  std::uint64_t y = seed ^ 0X507A1F38CB440C4;
  std::uint64_t z = seed ^ 0X112210F4B16C1CB1;

  if (y == 0) [[unlikely]] y = 1;
  if (z == 0) [[unlikely]] z = 1;

  std::ranges::for_each(std::views::iota(0ULL, iterations + 1), [&x, &y, &z](auto) constexpr noexcept -> void {
	x = 0x19BAFFBED * x + 0x12D687;
	y = ((y ^ (y << 13)) ^ ((y ^ (y << 13)) >> 17)) ^ (((y ^ (y << 13)) ^ ((y ^ (y << 13)) >> 17)) << 43);
	z = z + (z << 58);
  });

  return x + y + z;
}

template<std::size_t EncryptionDepth, std::uint64_t Seed>
ENCRYPTION_FORCEINLINE constexpr decltype(auto) GenerateSeeds() noexcept {
  std::array<std::uint64_t, EncryptionDepth> result{};
  std::ranges::for_each(result | std::views::enumerate, [](auto &&entry) constexpr noexcept {
	auto &[index, seed] = entry;
	seed = RandomRuntime(index, Seed);
  });
  return result;
}

template<std::integral T, std::uint64_t Seed = kRandomSeed, std::size_t EncryptionDepth = kEncryptionDepth>
class IntegralEncryption {
 public:
  ENCRYPTION_FORCEINLINE explicit consteval IntegralEncryption(T to_encrypt) noexcept: backing_(Encrypt(to_encrypt)) {}
  ENCRYPTION_FORCEINLINE ~IntegralEncryption() noexcept { backing_ = 0; }
  IntegralEncryption(IntegralEncryption &) = delete;
  IntegralEncryption(IntegralEncryption &&) = delete;

  [[nodiscard]]
  ENCRYPTION_FORCEINLINE consteval decltype(auto) Encrypt(T to_encrypt) const noexcept {
	ConstevalFor<EncryptionDepth>([&to_encrypt](const auto e) consteval noexcept -> void {
	  constexpr std::uint64_t kGen = kCompileTimeRandomValue<e.kIndex, Seed>;
	  Operations<static_cast<OperationType>(kGeneratedSeedValues[e.kIndex] % kAmountOperations), T>::Do(to_encrypt, kGen);
	});
	return to_encrypt;
  }

  [[nodiscard]]
  ENCRYPTION_FORCEINLINE constexpr decltype(auto) Decrypt(T to_decrypt) const noexcept {
	ConstexprFor<EncryptionDepth>([&to_decrypt](const auto e) constexpr noexcept -> void {
	  constexpr std::size_t kReverseIndex = EncryptionDepth - e.kIndex - 1;
	  constexpr std::uint64_t kGen = kCompileTimeRandomValue<kReverseIndex, Seed>;
	  Operations<static_cast<OperationType>(kGeneratedSeedValues[kReverseIndex] % kAmountOperations), T>::Undo(to_decrypt, kGen);
	});
	return to_decrypt;
  }

  [[nodiscard]]
  ENCRYPTION_FORCEINLINE constexpr decltype(auto) operator()() const noexcept { return Decrypt(backing_); }
 private:
  std::uint64_t backing_;
  static constexpr std::array<std::uint64_t, EncryptionDepth> kGeneratedSeedValues = GenerateSeeds<EncryptionDepth, Seed>();
};

template<std::uint64_t Base, std::uint64_t Line, std::integral auto Value>
static constexpr std::uint64_t kCreateIntegralSeed = (Base ^ Value) ^ (Line * (0x69420421266 ^ Value));
}

#define INTEGRAL_ENC(x) enc::IntegralEncryption<decltype(x), enc::kCreateIntegralSeed<enc::kRandomSeed, __LINE__, x>>{x}()

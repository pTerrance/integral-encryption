#Integral Encryption
Compile time encryption for integral constants without macro abuse. Unique encryption keys and encryption algorithms for every usage. Completly new output for each compilation. Tested and working on MSVC, Clang, and GCC.

**Example Usage**

```c++
#include "encryption.h"

int main() {
  std::println("0x{:X}", INTEGRAL_ENC(0xDEADBEEFULL)); // '0xDEADBEEF'
}
```

**Decompiled**
This result uses a low 10-instruction encryption depth. Two printf examples encrypting 0xDEADBEEF. As you can see, this results in two completely different encryption algorithms.
```c++
int __cdecl main(int argc, const char **argv, const char **envp)
{
  _main(argc, argv, envp);
  printf(
    "0x%llx\n",
    __ROR8__(
      __ROR8__(
        __ROR8__(__ROR8__(__ROL8__(0x7207DF2079FF2C9Bi64, 29) - 0x1A788208BBC958i64, 6) - 0x64999D2B5148BF9Ei64, 26)
      + 0x4F5AB27444FC3235i64,
        8)
    - 0x7246DA45C94DBA54i64,
      21));
  printf(
    "0x%llx\n",
    __ROL8__(
      __ROL8__(
        __ROR8__(
          __ROL8__(__ROL8__(__ROR8__(__ROR8__(__ROR8__(__ROR8__(0xFD56A635BA2D8EAEui64, 17), 14), 11), 15), 4), 29),
          13) ^ 0xADBE3AAA006AB531ui64,
        26),
      15));
  return 0;
}
```
An example with 300 instructions:
```c++
int __cdecl main(int argc, const char **argv, const char **envp)
{
  __int64 v3; // rax

  _main(argc, argv, envp);
  v3 = __ROR8__(
         (__ROR8__(
            (__ROR8__(
               __ROL8__(
                 __ROR8__(
                   __ROL8__(
                     __ROL8__(
                       ((__ROR8__(
                           __ROL8__(
                             __ROR8__(
                               __ROL8__(
                                 (((__ROL8__(
                                      __ROL8__(
                                        __ROR8__(
                                          __ROL8__(
                                            __ROL8__(
                                              __ROR8__(
                                                __ROL8__(
                                                  (__ROR8__(
                                                     __ROR8__(
                                                       (((__ROR8__(
                                                            ((__ROR8__(
                                                                __ROR8__(
                                                                  __ROR8__(
                                                                    __ROR8__(
                                                                      ((__ROR8__(
                                                                          __ROL8__(
                                                                            __ROL8__(
                                                                              __ROR8__(
                                                                                __ROR8__(
                                                                                  (__ROR8__(
                                                                                     (__ROL8__(
                                                                                        __ROR8__(
                                                                                          __ROL8__(
                                                                                            __ROL8__(
                                                                                              __ROL8__(
                                                                                                __ROR8__(
                                                                                                  __ROR8__(
                                                                                                    (__ROR8__(__ROL8__(((__ROL8__((__ROR8__(__ROL8__(__ROL8__(__ROL8__(__ROL8__(__ROL8__(__ROR8__(__ROR8__(__ROL8__((__ROR8__(__ROL8__(__ROL8__((__ROL8__(((__ROR8__(__ROL8__(__ROL8__(__ROR8__(0x630A6871F263AED4i64, 23), 23) - 0x69EC96B301E30A93i64, 20), 24) + 0x7A6D4DE6B0111442i64) ^ 0xE5FAA69D133C04ACui64) + 0x70FF915D8E72B4D2i64, 14) ^ 0x318D3A0F6ADB25i64) - 0x6C07235ACF574F8Fi64, 30), 31), 10) ^ 0x8773D7F6B8FB29DCui64) + 0x691D1305EEF3B1ECi64, 23) ^ 0xDF63A025BF28D900ui64, 30) - 0x42B37F1E2357642Ei64 + 0x4D540B34BF333ECBi64, 7), 8) ^ 0xF8F236BCF4B01C39ui64, 17) ^ 0x298CDFFDDEDB343Ei64, 4) - 0x133C6CF215673229i64 + 0x1754C2648CD0F066i64, 13), 16), 2) + 0x4FAB57EE773E43F0i64) ^ 0x8F3574BF294E86F1ui64, 6) - 0x77BC18DBD0B99D3Ci64) ^ 0x7DAF30086C70F6A0i64) + 0x3DB8EFCA6179E1BBi64, 22) ^ 0xE88112EC066A675Cui64, 12) ^ 0xAF91BD656CAB7DB2ui64) - 0x10C599E56F59C7C4i64,
                                                                                                    29),
                                                                                                  3),
                                                                                                28),
                                                                                              23),
                                                                                            15)
                                                                                        - 0x70D42AA5A60C1348i64,
                                                                                          26)
                                                                                      - 0x19C887D7F3CD56Bi64
                                                                                      + 0x235774D21286E179i64,
                                                                                        31)
                                                                                    + 0x5640E6B76A345820i64) ^ 0x13A6E78B5AD9CD0i64,
                                                                                     11) ^ 0xD3F38FEAA1A4E2F0ui64)
                                                                                + 0x3DF91B1053C91F17i64,
                                                                                  20) ^ 0xBD9E5B2E094AEF6i64,
                                                                                22),
                                                                              10) ^ 0x75FC25CC9CEB78C1i64,
                                                                            21),
                                                                          3)
                                                                      + 0x5557DD871A4EC98i64) ^ 0x9881F88D6C95D9FDui64)
                                                                    + 0x51902D7827BE0606i64,
                                                                      19)
                                                                  - 0x2310CF08FB6025D7i64
                                                                  + 0x2CA41186CBD091A1i64,
                                                                    25)
                                                                - 0x528DD9AC802079A6i64,
                                                                  13)
                                                              + 0x2F219F9C13AA9B4Di64,
                                                                2)
                                                            - 0x4B32B32A2F6B4EBBi64) ^ 0x7177DE4F74CE863Ai64)
                                                          - 0x10A21C535F97B9EBi64,
                                                            9) ^ 0x9FA0B449326C0BBFui64)
                                                       + 0x520112368C395D60i64) ^ 0xACE80E4DF749B515ui64)
                                                     - 0x1CF7EFF8C06F8589i64,
                                                       10)
                                                   + 0x28EA70E28BD68882i64,
                                                     26) ^ 0xE3EFEE9914BF80Bi64)
                                                + 0x4800AB36BAD5B40Fi64,
                                                  22)
                                              - 0x59D204CC4BD2B6E5i64,
                                                3),
                                              16)
                                          - 0x592761BFF5D3FA3i64,
                                            30),
                                          10)
                                      + 0x1A7F21AF0E7F82F9i64,
                                        15),
                                      15)
                                  - 0x79E2AB60329CAD48i64) ^ 0xED4464974596B619ui64)
                                + 0x4D7E3AFE18A34168i64) ^ 0x8628FEC694B3DCAEui64,
                                 5) ^ 0xC80F377E6B869D99ui64,
                               29),
                             25),
                           10)
                       - 0x21C5D6EFD5595F73i64) ^ 0xB16C463B4BBA7AF5ui64)
                     - 0x311A83A6127643A5i64,
                       20)
                   + 0x36109AD725CAA51Ci64,
                     16)
                 + 0x5F85F2D709C13623i64,
                   21),
                 13)
             + 0x7F950A6D16C53767i64,
               2) ^ 0xF0A1633C666684C4ui64)
          - 0x71A6F78FA1C919BDi64,
            10)
        - 0x1E8E5473CEF46CBAi64) ^ 0x37A8AEF11889C1EBi64,
         15);
  printf(
    "0x%llx\n",
    __ROL8__(
      __ROR8__(
        (__ROR8__(
           __ROL8__(
             __ROL8__(
               __ROL8__(
                 __ROL8__(
                   __ROR8__(
                     __ROL8__(
                       __ROL8__(
                         __ROL8__(
                           __ROL8__(
                             __ROR8__(
                               __ROR8__(
                                 __ROL8__(
                                   __ROR8__(
                                     __ROL8__(
                                       __ROL8__(
                                         (__ROR8__(
                                            __ROR8__(
                                              __ROR8__(
                                                __ROL8__(
                                                  __ROR8__(
                                                    __ROL8__(
                                                      (__ROL8__(
                                                         __ROL8__(
                                                           __ROL8__(
                                                             __ROR8__(
                                                               __ROR8__(
                                                                 __ROL8__(
                                                                   __ROL8__(
                                                                     __ROL8__(
                                                                       __ROR8__(
                                                                         __ROR8__(
                                                                           (__ROL8__(
                                                                              __ROR8__(
                                                                                __ROR8__(
                                                                                  __ROL8__(
                                                                                    __ROR8__(
                                                                                      __ROR8__(
                                                                                        (__ROR8__(
                                                                                           __ROR8__(
                                                                                             ((__ROR8__(
                                                                                                 __ROR8__(
                                                                                                   __ROR8__(
                                                                                                     __ROL8__(__ROR8__(__ROR8__(__ROR8__(__ROR8__((__ROL8__((__ROR8__((__ROR8__((__ROL8__(__ROR8__(__ROR8__(__ROL8__(((((__ROL8__(__ROR8__(__ROR8__((__ROR8__(__ROL8__(__ROR8__((((__ROL8__((v3 ^ 0xA570ECDF19C2F21Eui64) - 0x2635DDE182BFCE06i64 + 0xEC7C2EF1719AAC0i64, 11) ^ 0x8E197906747BC79Bui64) - 0x7659FE86CE9B095Ai64 + 0x393C0D810DF398D6i64) ^ 0x9F931446BAA12516ui64) + 0x6C4A0B8A819A5229i64, 31), 20) ^ 0xE43FFD3FF8663B81ui64, 31) ^ 0x5D42AF6D685BDEA7i64) + 0x86837B4FF85E700i64, 28), 17) - 0x7CCF01B2545EA385i64, 4) - 0x1679F0F63D8BF9C5i64) ^ 0xB71835982E2C93B7ui64) - 0x163234F5278998D9i64) ^ 0xE13FA7D374956F96ui64) - 0x1E34DA180080B573i64, 27) - 0x1B48A3DAF78EC70Ci64, 24), 4), 28) - 0x1B67A65B7C0CDBC6i64) ^ 0xE3E4D53183B65A34ui64, 4) - 0x4FED61E7F2D6BDB5i64) ^ 0xC247D554ACA0B34Fui64, 23) ^ 0xF01AEB9DC7674332ui64) - 0x5919D6DCB988789Ci64, 18) ^ 0xFF49FFF3A37ECE74ui64) + 0x3473BB69013854Bi64, 14), 10), 12), 12), 11),
                                                                                                     25),
                                                                                                   25),
                                                                                                 12)
                                                                                             + 0x13ECE76DC23D2F04i64) ^ 0x70205009ED0D8AC6i64)
                                                                                           + 0x315DB4FAD62E8420i64,
                                                                                             15)
                                                                                         - 0x51A7805E6B5EA5ADi64,
                                                                                           11)
                                                                                       - 0xC0C9CEF4E7B07FCi64) ^ 0x7AA4E23CD0C62EF8i64,
                                                                                        9),
                                                                                      18),
                                                                                    8)
                                                                                - 0x75407195B6654C98i64
                                                                                + 0x56835142DB95E34Di64,
                                                                                  24),
                                                                                29),
                                                                              2) ^ 0xFD47E98A7423D8Fi64)
                                                                         + 0x3A1D67754EC35B96i64,
                                                                           4)
                                                                       - 0x215BFF79AD42579Fi64,
                                                                         29),
                                                                       14),
                                                                     28)
                                                                 + 0x6CC0A14946F53054i64,
                                                                   9),
                                                                 12) ^ 0x2DFD1D9CD0C2FB18i64,
                                                               13),
                                                             20),
                                                           9)
                                                       - 0x86587ABAABF80CEi64
                                                       + 0x42657D18F6C5A255i64,
                                                         23) ^ 0x52AEE0D781C67FDFi64)
                                                    - 0x2ABB2E16CE472CEDi64,
                                                      16),
                                                    24)
                                                - 0x617CB5B2412B0624i64
                                                + 0x73B8DBAA3A96C25Bi64,
                                                  13)
                                              + 0x1F308A2EF059B698i64,
                                                14)
                                            - 0x6E53548228E24648i64,
                                              1),
                                            27) ^ 0x8BFE9DD0D7820B3Fui64)
                                       - 0x46A30C055FF3153Di64,
                                         20),
                                       8)
                                   + 0x7C47E62F1D0AA05Fi64,
                                     23) ^ 0xAC18282FDE895D84ui64,
                                   23)
                               + 0x559353729D579DB0i64,
                                 17),
                               24),
                             23)
                         + 0x27B08F096011ADD0i64,
                           22)
                       - 0x7AC7C4E0B59AB8FAi64,
                         32) ^ 0xC0EC161CE242C8F2ui64,
                       10)
                   + 0x3E56622453F054BBi64,
                     3),
                   5) ^ 0xE8563885CBB44193ui64,
                 8)
             - 0xA2AA05D749AD458i64,
               17)
           + 0x59070C26B4439DF1i64,
             18),
           16) ^ 0xFCED10623693FD5i64)
      - 0x1A90151777DC820Ci64,
        4),
      25)
  + 0x6CA4991342618E57i64);
  return 0;
}
```

**Notes**
Your encrypted value will at some point appear on the stack. It's important to remember that this is only an inconvenience for reverse engineers. There is no BCF or other inconveniences for reverse engineers in this library. All of the encryption could be automatically optimized away.

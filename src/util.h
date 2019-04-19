#ifndef BIP39_UTIL_H
#define BIP39_UTIL_H

#include "bip39/word_list.h"

#include <cstdint>
#include <string>

#if (defined ARDUINO || defined ESP8266 || defined ESP32)

#define BIP39_PLATFORM_IOT

#include <Arduino.h>
#include <pgmspace.h>

// Workaround issue: https://github.com/esp8266/Arduino/issues/2078
#ifdef ESP8266
#undef PSTR
#define PSTR(s) (s)
#endif

#else

#include <cstring>

// Define compatibility macros for non-Arduino platforms
#define PROGMEM
#define PGM_P const char*

#define pgm_read_ptr_far(p) (*(p))
#define strcpy_P strcpy // NOLINT

#endif

// Some platforms handle PROGMEM differently.
// This macro resolves "pointer-to-object" errors in those platforms.
// src: https://github.com/SlashDevin/NeoGPS/issues/112
#if defined(ESP8266) |              \
    defined(ARDUINO_SAMD_MKRZERO) | \
    defined(ARDUINO_SAMD_ZERO) |    \
    defined(ARDUINO_SAM_DUE) |      \
    defined(ARDUINO_ARCH_ARC32) |   \
    defined(__TC27XX__) |           \
    (defined(TEENSYDUINO) && (TEENSYDUINO < 139))
#undef pgm_read_ptr
#define pgm_read_ptr(addr) (*(const void **)(addr))
#endif

namespace BIP39 {

word_list split(const std::string& s, char delimiter);

template <typename InputIt>
inline std::string join(InputIt begin, InputIt end, const std::string& separator) {
    std::string s;

    for (auto it = begin; it != end; ++it) {
        s += *it;
        if (it + 1 != end) {
            s += separator;
        }
    }
    
    return s;
}

}

#endif

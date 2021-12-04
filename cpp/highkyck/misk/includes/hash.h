#pragma once

#include "encoding.h"
#include <cstdlib>
#include <iostream>

#ifndef FALLTHROUGH_INTENDED
#    define FALLTHROUGH_INTENDED \
        do {                     \
        } while (0)
#endif

namespace test {
inline uint32_t Hash(const char* data, size_t n, uint32_t seed)
{
    // Similar to murmur hash
    const uint32_t m     = 0xc6a4a793;
    const uint32_t r     = 24;
    const char*    limit = data + n;
    uint32_t       h     = seed ^ (n * m);
    // std::cout << "seed:" << seed << std::endl;
    // std::cout << "n:" << n << std::endl;
    // std::cout << "h:" << h << std::endl;

    // Pick up four bytes at a time
    while (data + 4 <= limit) {
        uint32_t w = DecodeFixed32(data);
        // std::cout << "w:" << w << std::endl;
        data += 4;
        h += w;
        h *= m;
        h ^= (h >> 16);
    }

    // std::cout << "h:" << h << std::endl;
    // std::cout << "left:" << (limit - data) << std::endl;
    // Pick up remaining bytes
    switch (limit - data) {
    case 3: h += static_cast<uint8_t>(data[2]) << 16; FALLTHROUGH_INTENDED;
    case 2: h += static_cast<uint8_t>(data[1]) << 8; FALLTHROUGH_INTENDED;
    case 1:
        h += static_cast<uint8_t>(data[0]);
        h *= m;
        h ^= (h >> r);
        break;
    }
    return h;
}
}  // namespace test

#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

/**
 * Templated on both the bit index and the dynamic range
 * to give the compiler as much information as possible
 * Downsize is that syntax is not so clear
 */
template <size_t bit_index, size_t dr>
std::vector<int> ExtractBits(const std::vector<uint64_t> &data) {
    constexpr size_t data_size = 3 * 32;
    std::vector<int> result(data_size);
    auto ptr = data.data();
    for (auto &r : result) {
        for (size_t i = 0; i != dr; ++i) {
            int bit = static_cast<int>((*ptr++ >> bit_index) & 1);
            r |= bit << i;
        }
    }
    return result;
}

/* pointer version */
template <size_t dr = 24>
void ExtractBitsPointer(const uint64_t *src, int *dst, size_t bit_index = 17) {
    for (int j = 0; j != 96; ++j) {
        for (size_t i = 0; i != dr; ++i) {
            auto bit = static_cast<int>((*src++ >> bit_index) & 1);
            *dst |= bit << i;
        }
        ++dst;
    }
}

/**
 * Templated only on bit index to give more flexibility
 */
template <size_t bit_index>
std::vector<int> ExtractBits1(const std::vector<uint64_t> &data,
                              unsigned dr = 24) {
    const size_t NumCompleteSamples = data.size() / dr;
    std::vector<int> result(NumCompleteSamples);
    auto ptr = data.data();
    for (auto &r : result) {
        for (unsigned i = 0; i != dr; ++i) {
            auto bit = static_cast<int>((*ptr++ >> bit_index) & 1);
            r |= bit << i;
        }
    }
    return result;
}

std::vector<int> ExtractBitsNoTemplate(const std::vector<uint64_t> &data,
                              size_t bit_index = 12, size_t dr = 24);

// inline std::vector<int> ExtractBitsNoTemplate(const std::vector<uint64_t> &data,
//                               size_t bit_index=17, size_t dr=24) {
//     const size_t NumCompleteSamples = data.size() / dr;
//     std::vector<int> result(NumCompleteSamples);
//     auto ptr = data.data();
//     for (auto &r : result) {
//         for (size_t i = 0; i != dr; ++i) {
//             auto bit = static_cast<int>((*ptr++ >> bit_index) & 1);
//             r |= bit << i;
//         }
//     }
//     return result;
// }

std::vector<int> ExtractBits3(std::vector<uint64_t> data, size_t bit_index = 12,
                              size_t dr = 24);

constexpr size_t data_size = 3 * 32;
template <size_t bit_index, size_t dr>
std::array<int, data_size>
ExtractBits4(const std::array<uint64_t, 2304> &data) {
    std::array<int, data_size> result{};
    auto ptr = data.data();
    for (auto &r : result) {
        for (size_t i = 0; i != dr; ++i) {
            auto bit = static_cast<int>((*ptr++ >> bit_index) & 1);
            r |= bit << i;
        }
    }
    return result;
}



template <size_t bit_index0, size_t bit_index1>
std::vector<int> ExtractTwoBits(const std::vector<uint64_t> &data,
                                int dr = 24) {
    constexpr int mask0 = (1 << bit_index0);
    constexpr int mask1 = (1 << bit_index1);
    constexpr int NumStrips = 2;
    const int NumCompleteSamples = data.size() / dr;
    const int NumCounters = NumCompleteSamples * NumStrips;

    std::vector<int> result(NumCounters);

    auto ptr = data.data();

    auto strip0 = result.data();
    auto strip1 = strip0 + NumCompleteSamples;

    for (int j = 0; j != NumCompleteSamples; ++j) {
        for (int i = 0; i != dr; ++i) {
            int bit0 = (*ptr & mask0) >> bit_index0;
            int bit1 = (*ptr++ & mask1) >> bit_index1;
            *strip0 |= bit0 << i;
            *strip1 |= bit1 << i;
        }
        strip0++;
        strip1++;
    }
    return result;
}
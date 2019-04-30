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

std::vector<int> ExtractBits2(const std::vector<uint64_t> &data,
                              size_t bit_index = 12, size_t dr = 24) {
    const size_t NumCompleteSamples = data.size() / dr;
    std::vector<int> result(NumCompleteSamples);
    auto ptr = data.data();
    for (auto &r : result) {
        for (size_t i = 0; i != dr; ++i) {
            auto bit = static_cast<int>((*ptr++ >> bit_index) & 1);
            r |= bit << i;
        }
    }
    return result;
}

std::vector<int> ExtractBits3(std::vector<uint64_t> data, size_t bit_index = 12,
                              size_t dr = 24) {
    const size_t NumCompleteSamples = data.size() / dr;
    std::vector<int> result(NumCompleteSamples);
    auto ptr = data.data();

    std::transform(begin(data), end(data), begin(data),
                   [bit_index](uint64_t x) { return (x >> bit_index) & 1; });

    for (auto &r : result) {
        for (size_t i = 0; i != dr; ++i) {
            r |= static_cast<int>(*ptr++ << i);
        }
    }
    return result;
}

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

/* pointer version */
template<size_t dr=24>
void ExtractBits(const uint64_t *src, int *dst, size_t bit_index = 17) {
    for (int j = 0; j != 96; ++j) {
        for (size_t i = 0; i != dr; ++i) {
            auto bit = static_cast<int>((*src++ >> bit_index) & 1);
            *dst |= bit << i;
        }
        ++dst;
    }
}
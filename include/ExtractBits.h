#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <array>

template <size_t bit_index, size_t dr>
std::vector<int> ExtractBits(const std::vector<uint64_t> &data) {
    constexpr uint64_t mask = (1u << bit_index);
    constexpr size_t data_size = 3 * 32;
    std::vector<int> result(data_size);
    auto ptr = data.data();
    for (auto &r : result) {
        for (size_t i = 0; i != dr; ++i) {
            int bit = static_cast<int>((*ptr++ & mask) >> bit_index);
            r |= bit << i;
        }
    }
    return result;
}



template <size_t bit_index>
std::vector<int> ExtractBits1(const std::vector<uint64_t> &data,
                              unsigned dr = 24) {
    constexpr uint64_t mask = (1u << bit_index);
    const size_t NumCompleteSamples = data.size() / dr;
    std::vector<int> result(NumCompleteSamples);
    auto ptr = data.data();
    for (auto &r : result) {
        for (unsigned i = 0; i != dr; ++i) {
            auto bit = static_cast<int>((*ptr++ & mask) >> bit_index);
            r |= bit << i;
        }
    }
    return result;
}

std::vector<int> ExtractBits2(const std::vector<uint64_t> &data,
                              size_t bit_index = 12, size_t dr = 24) {
    uint64_t mask = (1u << bit_index);
    const size_t NumCompleteSamples = data.size() / dr;
    std::vector<int> result(NumCompleteSamples);
    auto ptr = data.data();
    for (auto &r : result) {
        for (size_t i = 0; i != dr; ++i) {
            auto bit = static_cast<int>((*ptr++ & mask) >> bit_index);
            // auto bit = static_cast<int>((*ptr++ >> bit_index) & 1u);
            r |= bit << i;
        }
    }
    return result;
}

std::vector<int> ExtractBits3(std::vector<uint64_t> data, size_t bit_index = 12,
                              size_t dr = 24) {
    uint64_t mask = (1u << bit_index);
    const size_t NumCompleteSamples = data.size() / dr;
    std::vector<int> result(NumCompleteSamples);
    auto ptr = data.data();

    std::transform(
        begin(data), end(data), begin(data),
        [mask, bit_index](uint64_t x) { return (x & mask) >> bit_index; });

    for (auto &r : result) {
        for (size_t i = 0; i != dr; ++i) {
            r |= static_cast<int>(*ptr++ << i);
        }
    }
    return result;
}


constexpr size_t data_size = 3 * 32;
template <size_t bit_index, size_t dr>
std::array<int, data_size> ExtractBits4(const std::array<uint64_t, 2304> &data) {
    constexpr uint64_t mask = (1u << bit_index);
    std::array<int, data_size> result{};
    auto ptr = data.data();
    for (auto &r : result) {
        for (size_t i = 0; i != dr; ++i) {
            int bit = static_cast<int>((*ptr++ & mask) >> bit_index);
            r |= bit << i;
        }
    }
    return result;
}
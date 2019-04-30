#include "ExtractBits.h"

std::vector<int> ExtractBitsNoTemplate(const std::vector<uint64_t> &data,
                                              size_t bit_index, size_t dr) {
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

std::vector<int> ExtractBits3(std::vector<uint64_t> data, size_t bit_index,
                              size_t dr) {
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
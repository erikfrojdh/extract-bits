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

std::vector<int> ExtractBitsSerial(const std::vector<uint64_t> &data,
                                   std::vector<size_t> bit_index, int dr) {
    const int NumCounters = data.size() / dr * bit_index.size();
    std::vector<int> result(NumCounters);
    auto res = result.data();
    for (auto bi : bit_index) {
        for (auto ptr = begin(data); ptr < end(data);) {
            for (int i = 0; i != dr; ++i) {
                int bit = (*ptr++ >> bi) & 1;
                *res |= bit << i;
            }
            ++res;
        }
    }
    return result;
}

std::vector<int> ExtractBitsSerialComposed(const std::vector<uint64_t> &data,
                                           std::vector<size_t> bit_index,
                                           int dr) {
    const int NumCompleteSamples = data.size() / dr;
    const int NumCounters = NumCompleteSamples * bit_index.size();
    std::vector<int> result(NumCounters);
    auto res = result.data();
    for (auto bi : bit_index) {
        res = ExtractBitsPointer(data.data(), res, bi);
    }
    return result;
}

std::vector<int> ExtractBitsVector(const std::vector<uint64_t> &data,
                                   std::vector<size_t> bit_index, int dr) {
    const int NumCompleteSamples = data.size() / dr;
    const int NumCounters = NumCompleteSamples * bit_index.size();
    std::vector<int> result;
    result.reserve(NumCounters);
    int counter = 0;
    for (auto bi : bit_index) {
        auto ptr = data.data();
        for (int j = 0; j != 96; ++j) {
            int value = 0;
            for (int i = 0; i != dr; ++i) {
                int bit = (*ptr++ >> bi) & 1;
                value |= bit << i;
            }
            result.push_back(value);
        }
    }
    return result;
}
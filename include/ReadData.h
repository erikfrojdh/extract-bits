#pragma once

#include <vector>
#include <array>
std::vector<uint64_t> ReadData(const std::string &fname);
std::array<uint64_t, 2304> ReadDataArray(const std::string &fname);
#include "ExtractBits.h"
#include "ReadData.h"
#include "catch.hpp"

auto raw_data = ReadData("data/single.bin");
auto raw_data_arr = ReadDataArray("data/single.bin");

TEST_CASE("data loading") {
    REQUIRE(raw_data.size() == raw_data_arr.size());
    for (size_t i = 0; i != raw_data.size(); ++i) {
        CHECK(raw_data[i] == raw_data_arr[i]);
    }
}

TEST_CASE("template bit number") {
    auto data = ExtractBits1<17>(raw_data);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i != 96; ++i) {
        CHECK(data[i] == i);
    }
}

TEST_CASE("no template") {
    auto data = ExtractBits2(raw_data, 17);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i != 96; ++i) {
        CHECK(data[i] == i);
    }
}

TEST_CASE("template dr and bit nr") {
    auto data = ExtractBits<17, 24>(raw_data);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i != 96; ++i) {
        CHECK(data[i] == i);
    }
}

TEST_CASE("memory access") {
    auto data = ExtractBits3(raw_data, 17);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i != 96; ++i) {
        CHECK(data[i] == i);
    }
}

TEST_CASE("array") {
    auto data = ExtractBits4<17, 24>(raw_data_arr);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i != 96; ++i) {
        CHECK(data[i] == i);
    }
}
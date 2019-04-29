#include "catch.hpp"
#include "ExtractBits.h"
#include "ReadData.h"

auto raw_data = ReadData("data/single.bin");



TEST_CASE("template bit number"){
    auto data = ExtractBits1<17>(raw_data);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i!=96; ++i){
        CHECK(data[i] == i);
    }
}

TEST_CASE("no template"){
    auto data = ExtractBits2(raw_data, 17);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i!=96; ++i){
        CHECK(data[i] == i);
    }
}

TEST_CASE("template dr and bit nr"){
    auto data = ExtractBits<17, 24>(raw_data);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i!=96; ++i){
        CHECK(data[i] == i);
    }
}

TEST_CASE("memory access"){
    auto data = ExtractBits3(raw_data, 17);
    REQUIRE(data.size() == 96);
    for (size_t i = 0; i!=96; ++i){
        CHECK(data[i] == i);
    }
}
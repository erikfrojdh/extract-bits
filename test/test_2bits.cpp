#include "catch2/catch.hpp"

#include "ExtractBits.h"
#include "ReadData.h"

// 
// auto raw_data_arr = ReadDataArray("data/single.bin");

TEST_CASE("Extract two bits template"){
    auto raw_data = ReadData("data/single.bin");
    auto data = ExtractTwoBitsTemplate<17, 6>(raw_data);
    REQUIRE(data.size() == 192);
    for(size_t i=0; i!=data.size(); ++i){
        CHECK(data[i] == i);
    }
}

TEST_CASE("Extract two bits"){
    auto raw_data = ReadData("data/single.bin");
    auto data = ExtractTwoBits(raw_data, 17, 6);
    REQUIRE(data.size() == 192);
    for(size_t i=0; i!=data.size(); ++i){
        CHECK(data[i] == i);
    }
}

TEST_CASE("Extract two bits serial"){
    auto raw_data = ReadData("data/single.bin");
    auto data = ExtractBitsSerial(raw_data, {17,6});
    REQUIRE(data.size() == 192);
    for(size_t i=0; i!=data.size(); ++i){
        CHECK(data[i] == i);
    }
}

TEST_CASE("Extract two bits serial composed"){
    auto raw_data = ReadData("data/single.bin");
    auto data = ExtractBitsSerialComposed(raw_data, {17,6});
    REQUIRE(data.size() == 192);
    for(size_t i=0; i!=data.size(); ++i){
        CHECK(data[i] == i);
    }
}

TEST_CASE("Extract two bits vector"){
    auto raw_data = ReadData("data/single.bin");
    auto data = ExtractBitsVector(raw_data, {17,6});
    REQUIRE(data.size() == 192);
    for(size_t i=0; i!=data.size(); ++i){
        CHECK(data[i] == i);
    }
}
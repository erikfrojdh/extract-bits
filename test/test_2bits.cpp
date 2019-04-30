#include "catch2/catch.hpp"

#include "ExtractBits.h"
#include "ReadData.h"

// 
// auto raw_data_arr = ReadDataArray("data/single.bin");

TEST_CASE("Extract two bits"){
    auto raw_data = ReadData("data/single.bin");
    auto data = ExtractTwoBits<17, 6>(raw_data);
    REQUIRE(data.size() == 192);
    for(size_t i=0; i!=data.size(); ++i){
        CHECK(data[i] == i);
    }
}
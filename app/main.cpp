
#include "ExtractBits.h"
#include "ReadData.h"

#include <fstream>
#include <iostream>
#include <vector>

template <typename T> void print(const std::vector<T> &data) {
    for (size_t i = 0; i != 5; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "...\n";
    for (size_t i = 0; i != 5; ++i) {
        std::cout << data[i] << " ";
    }
}

int main() {


    auto raw_data = ReadData("data/single.bin");
    auto raw_data_arr = ReadDataArray("data/single.bin");
    for (size_t i = 0; i!=96; ++i){
        std::cout << raw_data[i] << " " << raw_data_arr[i] << "\n";
    }
    // auto raw_data = ReadData("data/single.bin");
    // print(raw_data);

    std::cout << "\n\n";
    auto data = ExtractBitsSerial(raw_data, {17, 6});
    print(data);

    // std::cout << "\n\n";
    // auto data1 = ExtractBits1<17>(raw_data);
    // print(data1);

    // std::cout << "\n\n";
    // auto data2 = ExtractBits2(raw_data, 17);
    // print(data2);
}
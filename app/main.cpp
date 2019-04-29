
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
    print(raw_data);

    std::cout << "\n\n";
    auto data = ExtractBits<17, 24>(raw_data);
    print(data);

    std::cout << "\n\n";
    auto data1 = ExtractBits1<17>(raw_data);
    print(data1);

    std::cout << "\n\n";
    auto data2 = ExtractBits2(raw_data, 17);
    print(data2);
}
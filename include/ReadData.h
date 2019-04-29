#include <vector>
#include <fstream>

std::vector<uint64_t> ReadData(const std::string &fname) {
    std::ifstream is;
    is.open(fname, std::ios::binary);
    if (is.good()) {
        std::vector<uint64_t> data(2304);
        is.read(reinterpret_cast<char *>(data.data()), 2304 * 8);
        return data;
    }else{
        throw 1;
    }
}
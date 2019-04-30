#include <benchmark/benchmark.h>
#include "ExtractBits.h"
#include "ReadData.h"

static std::vector<uint64_t> raw_data = ReadData("data/single.bin");
static std::array<uint64_t, 2304> raw_data_arr = ReadDataArray("data/single.bin");

std::vector<uint64_t> getVector(){
  std::vector<uint64_t> v(96);
  for(size_t i = 0; i!=v.size(); ++i){
    v[i] = i;
  }
  return v;
}


static void BM_CreateVector(benchmark::State& state) {
  for (auto _ : state)
    auto d = getVector();
}
// Register the function as a benchmark
BENCHMARK(BM_CreateVector);

// Define another benchmark
static void BM_TemplateOneBitAndDr(benchmark::State& state) {

  for (auto _ : state)
    auto d = ExtractBits<5,24>(raw_data);
}
BENCHMARK(BM_TemplateOneBitAndDr);


static void BM_TemplateOneBit(benchmark::State& state) {

  for (auto _ : state)
    auto d = ExtractBits1<5>(raw_data);
}
BENCHMARK(BM_TemplateOneBit);

static void BM_NoTemplate(benchmark::State& state) {
  for (auto _ : state)
    auto d = ExtractBitsNoTemplate(raw_data, 17);
}
BENCHMARK(BM_NoTemplate);

static void BM_NoTemplate_mem(benchmark::State& state) {
  for (auto _ : state)
    auto d = ExtractBits3(raw_data, 17);
}
BENCHMARK(BM_NoTemplate_mem);

static void BM_AllTemplate_array(benchmark::State& state) {

  for (auto _ : state)
    auto d = ExtractBits4<17,24>(raw_data_arr);
}
BENCHMARK(BM_AllTemplate_array);


static void BM_pointers(benchmark::State& state) {
  std::vector<int> data(96,0);
  for (auto _ : state)
    ExtractBitsPointer(raw_data.data(), data.data());
}
BENCHMARK(BM_pointers);

static void BM_ExtractTwoBitsTemplate(benchmark::State& state) {
  std::vector<int> data(96,0);
  for (auto _ : state)
    ExtractTwoBitsTemplate<17,6>(raw_data);
}
BENCHMARK(BM_ExtractTwoBitsTemplate);

static void BM_ExtractTwoBits(benchmark::State& state) {
  std::vector<int> data(96,0);
  for (auto _ : state)
    ExtractTwoBits(raw_data, 17,6);
}
BENCHMARK(BM_ExtractTwoBits);

static void BM_ExtractBitsSerial(benchmark::State& state) {
  std::vector<int> data(96,0);
  for (auto _ : state)
    ExtractBitsSerial(raw_data, {17,6});
}
BENCHMARK(BM_ExtractBitsSerial);

static void BM_ExtractBitsSerialArray(benchmark::State& state) {
  std::vector<int> data(96,0);
  for (auto _ : state)
    ExtractBitsSerialArray<2>(raw_data, {17,6});
}
BENCHMARK(BM_ExtractBitsSerialArray);

static void BM_ExtractBitsSerialComposed(benchmark::State& state) {
  std::vector<int> data(96,0);
  for (auto _ : state)
    ExtractBitsSerialComposed(raw_data, {17,6});
}
BENCHMARK(BM_ExtractBitsSerialComposed);

static void BM_ExtractBitsVector(benchmark::State& state) {
  std::vector<int> data(96,0);
  for (auto _ : state)
    ExtractBitsVector(raw_data, {17,6});
}
BENCHMARK(BM_ExtractBitsVector);

BENCHMARK_MAIN();
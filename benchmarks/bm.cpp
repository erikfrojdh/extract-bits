#include <benchmark/benchmark.h>
#include "ExtractBits.h"
#include "ReadData.h"

static std::vector<uint64_t> raw_data = ReadData("data/single.bin");

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
    auto d = ExtractBits2(raw_data, 17);
}
BENCHMARK(BM_NoTemplate);

static void BM_NoTemplate_mem(benchmark::State& state) {

  for (auto _ : state)
    auto d = ExtractBits3(raw_data, 17);
}
BENCHMARK(BM_NoTemplate_mem);

BENCHMARK_MAIN();
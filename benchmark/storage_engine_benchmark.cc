#include <benchmark/benchmark.h>

#include "std_map_storage_engine.h"

class StandardMapStorageEngineFixture : public benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &state) {}

  void TearDown(const ::benchmark::State &state) {}

  const size_t num_keys = 100000;
  std::vector<std::string> keys;

  StandardMapStorageEngine storage_engine;
};

BENCHMARK_DEFINE_F(StandardMapStorageEngineFixture, Set)
(benchmark::State &state) {

  if (state.thread_index == 0) {
    keys.resize(num_keys);
    for (unsigned int i = 0; i < num_keys; i++) {
      keys[i] = i;
    }
  }

  for (auto _ : state) {
    for (unsigned int i = 0; i < num_keys; i++) {
      storage_engine.Set(keys[i], keys[i]);
    }
  }

  if (state.thread_index == 0) {
    // Teardown code here.
  }

  state.SetItemsProcessed(state.iterations() * num_keys);
}
BENCHMARK_REGISTER_F(StandardMapStorageEngineFixture, Set)
    ->ThreadRange(1, 16)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime();

BENCHMARK_DEFINE_F(StandardMapStorageEngineFixture, Get)
(benchmark::State &state) {
  const size_t num_keys = 100000;
  std::vector<std::string> keys;

  StandardMapStorageEngine storage_engine;

  if (state.thread_index == 0) {
    keys.resize(num_keys);
    for (unsigned int i = 0; i < num_keys; i++) {
      keys[i] = i;
      storage_engine.Set(keys[i], keys[i]);
    }
  }

  for (auto _ : state) {
    for (unsigned int i = 0; i < num_keys; i++) {
      storage_engine.Get(keys[i]);
    }
  }

  if (state.thread_index == 0) {
    // Teardown code here.
  }

  state.SetItemsProcessed(state.iterations() * num_keys);
}
BENCHMARK_REGISTER_F(StandardMapStorageEngineFixture, Get)
    ->ThreadRange(1, 16)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime();

BENCHMARK_MAIN();

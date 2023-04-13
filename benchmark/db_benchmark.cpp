#include <benchmark/benchmark.h>

#include <cstdlib>
#include <ctime>
#include <unordered_map>

#include "textdb/db.h"

static auto db = textdb::DB::Open("store.textdb");
static std::unordered_map<std::string, std::string> map;

static void DB_Put(benchmark::State& state) {
    srand(time(nullptr));

    for (auto _ : state) {
        state.PauseTiming();
        std::string key = "key_" + std::to_string(rand()), value = "value_" + std::to_string(rand());
        map[key] = value;
        state.ResumeTiming();

        db->Put(key, value);
    }
}

static void DB_Get(benchmark::State& state) {
    srand(time(nullptr));

    auto map_it = map.begin();

    for (auto _ : state) {
        state.PauseTiming();
        std::string key = map_it->first;
        state.ResumeTiming();

        db->Get(key);
    }
}

static void DB_GetNonexistent(benchmark::State& state) {
    for (auto _ : state) {
        db->Get("nonexistent_key");
    }
}

BENCHMARK(DB_Put);
BENCHMARK(DB_Get);
BENCHMARK(DB_GetNonexistent);

BENCHMARK_MAIN();
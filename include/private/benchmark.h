#pragma once
#include <chrono>
#include <vector>

#include "../public/primos.h"

struct benchmark_result {
    benchmark_result(uint64_t t, std::vector<uint64_t> r) : time{t}, result{r} {};
    uint64_t time{};
    std::vector<uint64_t> result{};
};

benchmark_result benchmark(primos::iprimo &contestant, const uint64_t &teto);
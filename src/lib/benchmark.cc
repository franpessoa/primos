#include "benchmark.h"

#include <chrono>
#include <vector>

#include "primos.h"

benchmark_result benchmark(primos::iprimo &p, const uint64_t &teto) {
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;

    auto now{high_resolution_clock::now()};
    std::vector<uint64_t> r(p.gen_primos(teto));
    auto then{high_resolution_clock::now()};

    return benchmark_result(duration_cast<std::chrono::seconds>(then - now).count(), std::move(r));
}
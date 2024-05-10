#include <fmt/color.h>
#include <fmt/core.h>

#include <array>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <future>
#include <iostream>
#include <thread>

#include "benchmark.h"
#include "macros.h"
#include "primos.h"

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int main(int argc, const char **argv) {
    if (argc != 3) {
        fmt::println("Providencie um mínimo de argumentos");
        return -1;
    };

    const uint64_t teto{static_cast<uint64_t>(std::atoi(argv[1]))};

    primos::parallel_sieve psv{};
    std::future<benchmark_result> psv_async = std::async(
        std::launch::async, [psv = std::move(psv), teto]() mutable { return std::move(benchmark(psv, teto)); });

    benchmark_result psv_r = psv_async.get();

    PRINT_BOLD_COLOR("Resultados", fmt::color::red);

    fmt::println("\n{}", FORMAT_BOLD_COLOR("tempo: ", fmt::color::red));
    fmt::println("parallel: {}", psv_r.time);

    std::ofstream out;
    out.open(argv[2]);

    for (uint64_t primo : psv_r.result) {
        out << fmt::format("{}\n", primo);
    }

    out.close();
}

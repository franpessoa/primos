#include "primos.h"

#include <math.h>

#include <algorithm>
#include <cstdint>
#include <future>
#include <iterator>
#include <numeric>
#include <string_view>
#include <thread>
#include <vector>

// Implementação do crivo de Erastótenes
std::vector<uint64_t> primos::crivo_erasthotenes::gen_primos(const uint64_t &teto) {
    std::vector<bool> tests(teto); // numbers[0] = 1
    std::fill(tests.begin(), tests.end(), true);
    tests[0] = false;

    for (auto prime_candidate = 1; prime_candidate <= teto; prime_candidate++) {
        if (tests[prime_candidate]) {
            for (auto n = (prime_candidate + 1) * 2; // NOT USABLE FOR INDEXING => this is the real number
                 n <= tests.size(); n += (prime_candidate + 1)) {
                tests[n - 1] = false;
            };
        }
    }

    std::vector<uint64_t> prime_numbers{};
    for (uint64_t prime = 0; prime < teto; prime++) {
        if (tests[prime]) {
            prime_numbers.push_back(prime + 1);
        }
    }

    return std::move(prime_numbers);
}

constexpr std::string_view primos::crivo_erasthotenes::name() {
    return std::move(std::string_view("crivo de erastótenes simples"));
};

// Crivo de Erastótenes segmentado
std::vector<uint64_t> primos::crivo_segmentado::gen_primos(const uint64_t &teto) {
    const uint64_t seg_size{static_cast<uint64_t>(ceil(sqrt(teto)))};
    const uint64_t remainder{teto % seg_size};
    const uint64_t number_of_segs{(teto - remainder) / seg_size};

    // gera os números primos até \sqrt(teto)
    crivo_erasthotenes crivo_simples{};
    const std::vector<uint64_t> elem_primes{crivo_simples.gen_primos(seg_size)};

    // Vetor de resultados
    std::vector<uint64_t> primos;
    primos.reserve(teto);

    primos.insert(primos.end(), elem_primes.begin(), elem_primes.end());

    for (uint64_t seg_number = 1; seg_number < number_of_segs; seg_number++) {
        const int seg_start = seg_number * seg_size;

        std::vector<bool> seg{primos::sieve_segment(elem_primes, seg_size, seg_start)};
        std::vector<uint64_t> result = insert_primes_from_bool_array(seg, seg_start);

        for (auto &r : result) {
            primos.push_back(r);
        }
    }

    if (remainder != 0) {
        std::vector<bool> seg_remainder{primos::sieve_segment(elem_primes, remainder, seg_size * number_of_segs)};
        auto result = insert_primes_from_bool_array(seg_remainder, number_of_segs * seg_size);
        primos.insert(primos.end(), result.begin(), result.end());
    }

    return std::move(primos);
}

std::vector<uint64_t> primos::insert_primes_from_bool_array(std::vector<bool> &seg, const uint64_t seg_start) {
    std::vector<uint64_t> primos;
    const uint64_t seg_size(seg.size());

    for (uint64_t number = 0; number < seg_size; number++) {
        if (seg[number]) {
            primos.push_back(seg_start + number);
        }
    }

    return std::move(primos);
}

std::vector<bool> primos::sieve_segment(const std::vector<uint64_t> &primos_elementares, const uint64_t seg_size,
                                        const uint64_t first) {
    std::vector<bool> seg{};
    seg.resize(seg_size);
    for (auto i : seg) {
        i = true;
    };

    for (auto &prime : primos_elementares) {
        // Finds the first divider "div" of prime such that (first + div) is divisible by that prime
        for (uint64_t div = 0; div < seg_size; div++) {
            if ((first + div) % prime == 0) {
                for (uint64_t non_prime = div; non_prime < seg_size; non_prime += prime) {
                    seg[non_prime] = false;
                }

                break;
            }
        }
    }

    return std::move(seg);
};

constexpr std::string_view primos::crivo_segmentado::name() { return std::move(std::string_view("crivo segmentado")); };

std::vector<uint64_t> primos::parallel_sieve::gen_primos(const uint64_t &teto) {
    const uint64_t seg_size{static_cast<uint64_t>(ceil(sqrt(teto)))};
    const uint64_t remainder{teto % seg_size};
    const uint64_t number_of_segs{(teto - remainder) / seg_size};

    // gera os números primos até \sqrt(teto)
    crivo_erasthotenes crivo_simples{};
    std::vector<uint64_t> primos{crivo_simples.gen_primos(seg_size)};

    std::vector<std::future<std::vector<bool>>> handles{};
    handles.reserve(number_of_segs);

    for (uint64_t seg_number = 1; seg_number < number_of_segs; seg_number++) {
        const int seg_start = seg_number * seg_size;

        // std::vector<bool> seg{ primos::sieve_segment(elem_primes, seg_size, seg_start) };
        handles.push_back(std::async(std::launch::async,
                                     [seg_start = std::move(seg_start), elem_primes = primos, seg_size = seg_size]() {
                                         return primos::sieve_segment(elem_primes, seg_size, seg_start);
                                     }));
    }

    if (remainder != 0) {
        handles.push_back(
            std::async(std::launch::async | std::launch::deferred,
                       [seg_start = seg_size * number_of_segs, elem_primes = primos, seg_size = seg_size]() {
                           return primos::sieve_segment(elem_primes, seg_size, seg_start);
                       }));
    };

    const uint64_t handle_number = handles.size();
    for (uint64_t h = 0; h < handle_number; h++) {
        auto result = handles[h].get();
        const auto result_numbers = insert_primes_from_bool_array(result, (h + 1) * seg_size);

        primos.insert(primos.end(), std::make_move_iterator(result_numbers.begin()),
                      std::make_move_iterator(result_numbers.end()));
    };

    return std::move(primos);
}

constexpr std::string_view primos::parallel_sieve::name() { return std::move(std::string_view("crivo paralelo")); }
#pragma once
#include <cstdint>
#include <string_view>
#include <vector>

namespace primos {
std::vector<bool> sieve_segment(const std::vector<uint64_t> &primos_elementares, const uint64_t seg_size,
                                const uint64_t first);
std::vector<uint64_t> insert_primes_from_bool_array(std::vector<bool> &seg, const uint64_t seg_start);

struct iprimo {
    virtual std::vector<uint64_t> gen_primos(const uint64_t &teto) = 0;
    virtual constexpr std::string_view name() = 0;
};

struct parallel_sieve : public iprimo {
    std::vector<uint64_t> gen_primos(const uint64_t &teto) override;
    constexpr std::string_view name() override;
};

struct crivo_erasthotenes : public iprimo {
    std::vector<uint64_t> gen_primos(const uint64_t &teto) override;

    constexpr std::string_view name() override;
};

struct crivo_segmentado : public iprimo {
    std::vector<uint64_t> gen_primos(const uint64_t &teto) override;
    constexpr std::string_view name() override;
};

} // namespace primos
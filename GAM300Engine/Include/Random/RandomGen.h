#pragma once
#include <random>
#include <pch.h>
#include <type_traits>
namespace TDS
{
    class CustomRandom {
    public:
        // Constructor with optional seed
        explicit CustomRandom(uint64_t seed = std::random_device{}())
            : m_Engine(seed), m_GenerationCount(0) {}

        // Generate a random number within a specified range for integral types
        template <typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
        T get(T min, T max) {
            std::uniform_int_distribution<T> distribution(min, max);
            return generate(distribution);
        }

        // Generate a random number within a specified range for floating-point types
        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
        T get(T min, T max) {
            std::uniform_real_distribution<T> distribution(min, max);
            return generate(distribution);
        }

        // Returns the number of random numbers generated so far
        uint64_t getGenerationCount() const {
            return m_GenerationCount;
        }

    private:
        std::mt19937_64 m_Engine; // Mersenne Twister 64-bit engine
        uint64_t m_GenerationCount;

        // Helper function to generate a random number using the given distribution
        template <typename T, typename Distribution>
        T generate(Distribution& distribution) {
            ++m_GenerationCount;
            return distribution(m_Engine);
        }
    };
}
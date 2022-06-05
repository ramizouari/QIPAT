//
// Created by ramizouari on 06/05/22.
//

#ifndef IMAGEPROCESSING_UTILITY_H
#define IMAGEPROCESSING_UTILITY_H

#include <thread>
#include <random>


namespace utility {
    const unsigned int HARD_CONCURRENCY_LIMIT=std::thread::hardware_concurrency();
    const unsigned int SOFT_CONCURRENCY_LIMIT=4*HARD_CONCURRENCY_LIMIT;
    class RandomNumberGenerator {
    public:
        explicit RandomNumberGenerator(unsigned int seed);
        RandomNumberGenerator();
        ~RandomNumberGenerator() = default;
        auto operator()() -> unsigned int;
    private:
        inline static std::random_device rd{};
        std::mt19937_64 rng;
    };
}

#endif //IMAGEPROCESSING_UTILITY_H

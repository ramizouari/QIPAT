//
// Created by ramizouari on 06/05/22.
//

#include "utility.h"

namespace utility {

    RandomNumberGenerator::RandomNumberGenerator(unsigned int seed) :rng(seed) {}

    auto RandomNumberGenerator::operator()() -> unsigned int {
        return rng();
    }

    RandomNumberGenerator::RandomNumberGenerator():rng(rd()) {}
}
#pragma once

#include <random>
#include <chrono>

namespace Core::Random{

    inline std::mt19937 create(){
        std::random_device rd{};
        std::seed_seq seedSequence{
            static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
            rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() 
        };

        return std::mt19937{seedSequence};
    };

    static std::mt19937 generator {create()};

    inline int getRandomInt(int start, int end){
        std::uniform_int_distribution distribution{start, end};
        return distribution(generator);
    }

    inline double getRandomDouble(double start, double end){
        std::uniform_real_distribution distribution{start, end};
        return distribution(generator);
    }
}

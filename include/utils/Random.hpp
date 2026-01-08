#pragma once
#include <random>

class Random {
public:
    static inline std::mt19937& engine() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
    static inline float real(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(engine());
    }
    static inline int Int(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine());
    }
};
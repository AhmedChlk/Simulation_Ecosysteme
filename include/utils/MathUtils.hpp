#pragma once
#include <cmath>
#include <algorithm>
#include "Config.hpp"

class MathUtils {
public:
    static float getNoiseElevation(int x, int y, const GenerationConfig& config) {
        double s = static_cast<double>(config.seed % 10000);
        double dx = static_cast<double>(x);
        double dy = static_cast<double>(y);
        double noise1 = std::sin(dx * config.scaleContinent + s) + 
                       std::cos(dy * config.scaleContinent + s);
        double noise2 = std::sin(dx * config.scaleDetail + s) * std::cos(dy * config.scaleDetail + s);

        double combined = (noise1 * config.weightContinent) + (noise2 * config.weightDetail);
        
        float result = static_cast<float>((combined + 1.5) / 3.0);

        return std::clamp(result, 0.0f, 1.0f);
    }
};
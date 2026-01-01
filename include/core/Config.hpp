#pragma once

struct GenerationConfig {
    unsigned int seed = 0;
    float scaleContinent = 0.08f; // Légèrement augmenté pour plus de variations
    float scaleDetail = 0.4f;      // Plus de détails locaux
    
    float weightContinent = 0.7f;
    float weightDetail = 0.3f;

    float thresholdWater = 0.25f;  // Moins d'eau
    float thresholdSand = 0.30f;   // Moins de sable
    float thresholdGrass = 0.60f;  // Plus d'herbe
    float thresholdForest = 0.80f; 
};

struct GameConfig {
    int windowWidth;
    int windowHeight;
    int worldWidth;
    int worldHeight;
    float tileSize;
    GenerationConfig genConfig; 
};

namespace Config {
    inline constexpr float TILE_SIZE = 10.0f;
}
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// --- TERRAIN ---
// On a enlevé ROCK (Roche)
enum class TerrainType {
    WATER, SAND, DIRT, GRASS, SNOW, Count
};

struct TerrainData {
    std::string name;
    sf::Color color;
    bool isWalkable;
    float walkSpeed;
};

class TerrainLibrary {
public:
    static const TerrainData& get(TerrainType type);
};

// --- PROPS (Objets) ---
// On a enlevé BOULDER (Rocher)
enum class PropType {
    NONE, TREE, Count
};

struct PropData {
    std::string name;
    sf::Color color;
    bool isBlocking;
};

class PropLibrary {
public:
    static const PropData& get(PropType type);
};
#include "ConcreteBiomes.hpp"
#include "Config.hpp"
#include <cmath>

namespace {
    // Petite fonction utilitaire pour varier un peu
    float getPseudoNoise(int x, int y, float scale) {
        return std::sin(x * scale) + std::cos(y * scale * 1.5f);
    }
}

std::unique_ptr<Tile> GrassBiome::generateTile(int x, int y) const {
    float s = (float)Config::TILE_SIZE;
    PropType prop = PropType::NONE;
    // Quelques arbres par-ci par-là
    if (getPseudoNoise(x, y, 0.2f) > 1.4f) prop = PropType::TREE;
    return std::make_unique<Tile>(x * s, y * s, s, TerrainType::GRASS, prop);
}

std::unique_ptr<Tile> DesertBiome::generateTile(int x, int y) const {
    float s = (float)Config::TILE_SIZE;
    // Désert simple (Sable uniquement, pas de rochers)
    return std::make_unique<Tile>(x * s, y * s, s, TerrainType::SAND, PropType::NONE);
}

std::unique_ptr<Tile> ForestBiome::generateTile(int x, int y) const {
    float s = (float)Config::TILE_SIZE;
    // Beaucoup d'arbres
    if (getPseudoNoise(x, y, 0.3f) > -0.5f) 
        return std::make_unique<Tile>(x * s, y * s, s, TerrainType::DIRT, PropType::TREE);
    return std::make_unique<Tile>(x * s, y * s, s, TerrainType::GRASS, PropType::NONE);
}

std::unique_ptr<Tile> TundraBiome::generateTile(int x, int y) const {
    float s = (float)Config::TILE_SIZE;
    // Toundra enneigée simple
    return std::make_unique<Tile>(x * s, y * s, s, TerrainType::SNOW, PropType::NONE);
}

std::unique_ptr<Tile> OceanBiome::generateTile(int x, int y) const {
    float s = (float)Config::TILE_SIZE;
    return std::make_unique<Tile>(x * s, y * s, s, TerrainType::WATER, PropType::NONE);
}
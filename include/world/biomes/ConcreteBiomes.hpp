#pragma once
#include "Biome.hpp"
#include <memory>


class GrassBiome : public Biome {
public:
    std::unique_ptr<Tile> generateTile(int x, int y) const override;
};

class DesertBiome : public Biome {
public:
    std::unique_ptr<Tile> generateTile(int x, int y) const override;
};

class ForestBiome : public Biome {
public:
    std::unique_ptr<Tile> generateTile(int x, int y) const override;
};

class TundraBiome : public Biome {
public:
    std::unique_ptr<Tile> generateTile(int x, int y) const override;
};

class OceanBiome : public Biome {
public:
    std::unique_ptr<Tile> generateTile(int x, int y) const override;
};
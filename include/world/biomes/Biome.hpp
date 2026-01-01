#pragma once
#include <memory>
#include "Tile.hpp"

class Biome {
public:
    virtual ~Biome() = default;
    virtual std::unique_ptr<Tile> generateTile(int x, int y) const = 0;
};
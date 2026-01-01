#pragma once
#include "Grid.hpp"
#include "Tile.hpp"
#include "Config.hpp"
#include <memory>

class WorldGenerator {
public:
    void generate(Grid<std::unique_ptr<Tile>>& grid, const GenerationConfig& config);
};
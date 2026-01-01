#include "WorldGenerator.hpp"
#include "MathUtils.hpp"
#include "ConcreteBiomes.hpp"

void WorldGenerator::generate(Grid<std::unique_ptr<Tile>>& grid, const GenerationConfig& config) {
    int w = grid.getWidth();
    int h = grid.getHeight();

    auto bOcean = std::make_unique<OceanBiome>();
    auto bDesert = std::make_unique<DesertBiome>();
    auto bGrass = std::make_unique<GrassBiome>();
    auto bForest = std::make_unique<ForestBiome>();
    auto bTundra = std::make_unique<TundraBiome>();

    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            float elevation = MathUtils::getNoiseElevation(x, y, config);

            Biome* chosen = nullptr;
            if (elevation < config.thresholdWater)      chosen = bOcean.get();
            else if (elevation < config.thresholdSand)  chosen = bDesert.get();
            else if (elevation < config.thresholdGrass) chosen = bGrass.get();
            else if (elevation < config.thresholdForest)chosen = bForest.get();
            else                                        chosen = bTundra.get();

            grid[x][y] = chosen->generateTile(x, y);
        }
    }
}
#include "Renderer.hpp"
#include "Config.hpp"

void Renderer::draw(sf::RenderWindow& window, const Grid<std::unique_ptr<Tile>>& grid) {
    window.clear();

    // On parcourt toute la grille
    for (int x = 0; x < grid.getWidth(); ++x) {
        for (int y = 0; y < grid.getHeight(); ++y) {
            const auto& tile = grid[x][y];
            if (tile) {
                tile->draw(window); 
            }
        }
    }

    window.display(); // On affiche le résultat final à l'écran
}
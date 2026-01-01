#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Tile.hpp"
#include <memory>

class Renderer {
public:
    Renderer() = default;

    // J'ai supprimé le 3ème argument : const sf::RectangleShape& nightLayer
    void draw(sf::RenderWindow& window, const Grid<std::unique_ptr<Tile>>& grid);
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Material.hpp"

class Tile {
public:
    // Constructeur
    Tile(float x, float y, float size, TerrainType terrain, PropType prop = PropType::NONE);

    TerrainType getTerrain() const;
    PropType getProp() const;

    // Méthode d'affichage
    void draw(sf::RenderWindow& window);

private:
    float m_x, m_y, m_size;
    TerrainType m_terrain;
    PropType m_prop;
};
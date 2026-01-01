#include "Tile.hpp"

Tile::Tile(float x, float y, float size, TerrainType terrain, PropType prop)
        : m_x(x), m_y(y), m_size(size), m_terrain(terrain), m_prop(prop) {}
TerrainType Tile::getTerrain() const { return m_terrain; }
PropType Tile::getProp() const { return m_prop; }

void Tile::draw(sf::RenderWindow& window) {
    sf::RectangleShape groundShape(sf::Vector2f(m_size, m_size));
    groundShape.setPosition(m_x, m_y);
    groundShape.setFillColor(TerrainLibrary::get(m_terrain).color);
    window.draw(groundShape);

    if (m_prop == PropType::TREE) {
        const auto& propData = PropLibrary::get(m_prop);
        
        sf::ConvexShape tree;
        tree.setPointCount(3); 

        float padding = m_size * 0.15f; 
        float bottom = m_y + m_size - padding;
        float top = m_y + padding;
        float centerX = m_x + m_size / 2.0f;
        float left = m_x + padding;
        float right = m_x + m_size - padding;

        tree.setPoint(0, sf::Vector2f(centerX, top));
        tree.setPoint(1, sf::Vector2f(right, bottom));
        tree.setPoint(2, sf::Vector2f(left, bottom));

        tree.setFillColor(propData.color);
        window.draw(tree);
    }
}
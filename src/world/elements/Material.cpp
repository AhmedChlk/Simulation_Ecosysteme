#include "Material.hpp"
#include <array>
#include <cassert>

const TerrainData& TerrainLibrary::get(TerrainType type) {
    static const std::array<TerrainData, static_cast<size_t>(TerrainType::Count)> registry = {{
        { "Water",  sf::Color(60, 160, 220),    false,    0.0f }, // Bleu
        { "Sand",   sf::Color(235, 225, 160),   true,     0.6f }, // Sable
        { "Dirt",   sf::Color(140, 105, 75),    true,     0.9f }, // Terre
        { "Grass",  sf::Color(100, 190, 80),    true,     1.0f }, // Herbe
        { "Snow",   sf::Color(245, 250, 255),   true,     0.7f }  // Neige
    }};

    assert(static_cast<size_t>(type) < registry.size());
    return registry[static_cast<size_t>(type)];
}

const PropData& PropLibrary::get(PropType type) {
    static const std::array<PropData, static_cast<size_t>(PropType::Count)> registry = {{
        { "None",    sf::Color::Transparent,    false },
        { "Tree",    sf::Color(30, 100, 40),    true  }  
    }};

    assert(static_cast<size_t>(type) < registry.size());
    return registry[static_cast<size_t>(type)];
}
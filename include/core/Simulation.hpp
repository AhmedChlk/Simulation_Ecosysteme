#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Tile.hpp"
#include "Renderer.hpp"
#include "WorldGenerator.hpp"
#include "Config.hpp"

class Simulation {
private:
    sf::RenderWindow m_window;
    GameConfig m_config;
    Grid<std::unique_ptr<Tile>> m_grid; 
    std::unique_ptr<WorldGenerator> m_generator; 
    Renderer m_renderer; 

public:
    Simulation(const GameConfig& config);
    void run();

private:
    void processEvents();
    void render();
    void update(float dt);
};
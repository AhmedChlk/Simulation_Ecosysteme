#include "Simulation.hpp" // Tu peux enlever les "../include/core/" grâce à ton CMakeLists
#include "Config.hpp"
#include <SFML/Graphics.hpp>

int main() {
    auto mode = sf::VideoMode::getDesktopMode();
    GameConfig config;
    config.tileSize = Config::TILE_SIZE; 
    
    config.worldWidth = static_cast<int>(mode.width) / static_cast<int>(config.tileSize);
    config.worldHeight = static_cast<int>(mode.height) / static_cast<int>(config.tileSize);
    
    config.windowWidth = config.worldWidth * static_cast<int>(config.tileSize);
    config.windowHeight = config.worldHeight * static_cast<int>(config.tileSize);

    Simulation sim(config);
    sim.run();

    return 0;
}
#include "Simulation.hpp"
#include <random> 
#include <iostream>

Simulation::Simulation(const GameConfig& config) 
    : m_config(config), 
      m_grid(config.worldWidth, config.worldHeight)
{
    m_window.create(sf::VideoMode(m_config.windowWidth, m_config.windowHeight), "Ecosystem Simulation");
    std::random_device rd; 
    std::mt19937 gen(rd());
    m_config.genConfig.seed = gen();
    m_generator = std::make_unique<WorldGenerator>();
    m_generator->generate(m_grid, m_config.genConfig); 
}
void Simulation::run() {
    sf::Clock clock; 
    while (m_window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Simulation::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) m_window.close();
    }
}

void Simulation::update(float dt) {
    // Cette fonction est maintenant vide, mais prête à recevoir d'autres logiques (ex: déplacement des entités).
}


void Simulation::render() {
    m_renderer.draw(m_window, m_grid); 
}
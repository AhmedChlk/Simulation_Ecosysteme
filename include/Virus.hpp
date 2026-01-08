#pragma once
#include "DangerEnvironnemental.hpp"
#include "Herbivore.hpp"
#include "utils/Random.hpp"
#include "Config.hpp"

// Danger de type Virus.
// Il affaiblit l'herbivore et peut se propager.
class Virus : public DangerEnvironnemental {
public:
    Virus(int x, int y) : DangerEnvironnemental(x, y) {}
    
    
    // Réduction d'énergie + possibilité de propagation et de tuer  
    void appliquerEffet(Herbivore& herbivore, Monde& monde) override {
        herbivore.perdreEnergie(herbivore.getEnergie() * 0.5f);

        if (Random::real(0.f, 1.f) < Config::danger.chanceMortVirus) {
            herbivore.tuer();
        }
        if (Random::real(0.f, 1.f) < Config::danger.chancePropagationVirus) {
            int dx = Random::Int(-1, 1);
            int dy = Random::Int(-1, 1);
            monde.ajouterDanger(
                std::make_unique<Virus>(x + dx, y + dy)
            );
        }
        actif = false;
    }
};

#pragma once
#include "DangerEnvironnemental.hpp"
#include "Herbivore.hpp"

// Danger de type Piege
class Piege : public DangerEnvironnemental {
public:
    Piege(int x, int y) : DangerEnvironnemental(x, y) {}
    // S'il est déclenché, il tue instantanément l'herbivore
    void appliquerEffet(Herbivore& herbivore, Monde&) override {
        herbivore.tuer(); 
    }
};

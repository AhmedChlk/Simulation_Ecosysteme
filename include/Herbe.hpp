#pragma once
#include "EntiteVivante.hpp"

class Herbe : public EntiteVivante {
public:
    Herbe(int x, int y);
    
    std::unique_ptr<EntiteVivante> seMultiplier() override;
private:
    // L'herbe pousse puis jaunit et meurt progressivement
    void appliquerMetabolisme(float dt, PhaseVie phase) override;
};

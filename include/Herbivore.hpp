#pragma once
#include "EntiteVivante.hpp"

class Monde;

// Herbivore capable de se déplacer manger de l'herbe et se reproduire
class Herbivore : public EntiteVivante {
public:
    Herbivore(int x, int y);
    
    void update(float dt, Monde& monde);
    
    bool aMange() const;
    
    std::unique_ptr<EntiteVivante> seMultiplier() override;
    
    void tuer();
    
    void perdreEnergie(float e);
private:
    void appliquerMetabolisme(float dt, PhaseVie phase) override;
    
    void seDeplacer(Monde& monde);
    
    void manger(Monde& monde);
    
    float timerMange;
    float timerDeplacement;
};

#include "Herbe.hpp"
#include "Config.hpp"

Herbe::Herbe(int x, int y)
    : EntiteVivante(
        x, y,
        Config::herbe.energieInitiale,
        Config::herbe.energieMax,
        Config::herbe.ageMaturite,
        Config::herbe.ageDeclin,
        Config::herbe.ageMort
      )
{}

void Herbe::appliquerMetabolisme(float dt, PhaseVie phase) {
    if (phase == PhaseVie::Croissance) {
        energie += Config::herbe.gainCroissance * dt;
    }
    else if (phase == PhaseVie::Mature) {
        energie += Config::herbe.gainMature * dt;
    }
    else { // Déclin
        energie -= Config::herbe.perteDeclin * dt;
    }
}
std::unique_ptr<EntiteVivante> Herbe::seMultiplier() {
    resetTimerProcreation(Config::herbe.tempsProcreation);
    energie *= Config::herbe.partageEnergie; 

    return std::make_unique<Herbe>(x, y);
}


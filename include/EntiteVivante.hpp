#pragma once
#include <algorithm>
#include <memory>

enum class PhaseVie {
    Croissance,
    Mature,
    Declin
};
// Classe abstraite représentant toute entité vivante du monde.
class EntiteVivante {
protected:
    int x;
    int y;
    float age;
    float energie;
    float energieMax;
    float ageMaturite;
    float ageDeclin;
    float ageMort;
    bool vivante;
    float timerProcreation;
    
    protected:
    // chaque entité définit son métabolisme   
    virtual void appliquerMetabolisme(float dt, PhaseVie phase) = 0;

public:
    EntiteVivante(int x, int y,float energieInitiale,float energieMax,float ageMaturite,float ageDeclin,float ageMort)
        : x(x), y(y),
          age(0.f),
          energie(energieInitiale),
          energieMax(energieMax),
          ageMaturite(ageMaturite),
          ageDeclin(ageDeclin),
          ageMort(ageMort),
          vivante(true),
          timerProcreation(0.f){}
    
    virtual ~EntiteVivante() = default;

    virtual void update(float dt) {
        if (!vivante) return;
        age += dt;
        if (timerProcreation > 0.f)
            timerProcreation -= dt;
        PhaseVie phase;
        if (age < ageMaturite) phase = PhaseVie::Croissance;
        else if (age < ageDeclin) phase = PhaseVie::Mature;
        else phase = PhaseVie::Declin;
        appliquerMetabolisme(dt, phase);
        energie = std::clamp(energie, 0.f, energieMax);
        if (age >= ageMort || energie <= 0.f) {
            vivante = false;
        }
    }
    bool peutSeReproduire() const {
        return vivante && age >= ageMaturite && energie >= energieMax * 0.7f && timerProcreation <= 0.f;
    }
    // reproduction spécifique à chaque espèce
    virtual std::unique_ptr<EntiteVivante> seMultiplier() = 0;

    
    void resetTimerProcreation(float cooldown) {
        timerProcreation = cooldown;
    }
    
    int getX() const { return x; }
    
    int getY() const { return y; }
    
    float getEnergie() const { return energie; }
    
    float getEnergieMax() const { return energieMax; }

    float ratioEnergie() const {
        return (energieMax <= 0.f) ? 0.f : (energie / energieMax);
    }
    bool estVivante() const { return vivante; }
};

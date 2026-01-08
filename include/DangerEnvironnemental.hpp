#pragma once

class Monde;
class Herbivore;

// Classe abstraite représentant un danger du monde.
class DangerEnvironnemental {
protected:
    int x;
    int y;
    bool actif;
public:

    DangerEnvironnemental(int x, int y): x(x), y(y), actif(true) {}
    
    virtual ~DangerEnvironnemental() = default;
    
     // Applique l'effet du danger sur un herbivore
    virtual void appliquerEffet(Herbivore& herbivore, Monde& monde) = 0;
    
    int getX() const { return x; }
    
    int getY() const { return y; }
    
    bool estActif() const { return actif; }
};

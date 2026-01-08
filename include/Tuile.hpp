#pragma once
#include <iostream>


// Types possibles de terrain
enum class TypeTuile {
    Eau,
    Terre,
    Sable
};

// Représente une case du monde
class Tuile {
private:
    TypeTuile type;
public:
    Tuile() : type(TypeTuile::Eau) {} 
    
    Tuile(TypeTuile type);
    
    TypeTuile getType() const;
    
    void setType(TypeTuile nouveauType);

    friend std::ostream& operator<<(std::ostream& os, const Tuile& tuile);
};
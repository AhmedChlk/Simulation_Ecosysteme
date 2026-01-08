#pragma once
#include <SFML/Graphics.hpp>
#include "Monde.hpp"

// Classe responsable du rendu graphique
class Affichage {
private:
    sf::RenderWindow fenetre; // Fenêtre SFML
    const Monde& monde; // Référence constante vers le monde
    int tailleCase; // Taille d'une tuile en pixels
public:
    Affichage(const Monde& monde);
    
    ~Affichage() = default;
    
    bool estOuvert() const;
    
    void gererEvenements();
    
    void dessiner();
};
#include <iostream>
#include "Monde.hpp"
#include "Affichage.hpp"
#include "utils/Random.hpp"

int main() {

    Monde monde;
    //système d'affichage
    Affichage affichage(monde);

    // Horloge pour gérer le temps (delta time)
    sf::Clock horloge;

    while (affichage.estOuvert()) {
         // calculer le temps écoulé depuis la dernière frame
        float dt = horloge.restart().asSeconds();
        if (dt > 0.05f) dt = 0.05f;

        //gerer events
        affichage.gererEvenements();
        // Mise à jour logique du monde
        monde.update(dt);
        // Dessiner le monde
        affichage.dessiner();
    }


    return 0;
}
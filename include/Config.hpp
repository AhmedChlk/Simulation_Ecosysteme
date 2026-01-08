#pragma once
#include <SFML/Graphics.hpp>

// Espace de noms regroupant tous les paramètres du projet
// Permet d'ajuster facilement la simulation sans toucher au code
namespace Config {
    //affichage
    constexpr int tailleTuile = 10;
    inline const unsigned int largeurFenetre = sf::VideoMode::getDesktopMode().width;
    inline const unsigned int hauteurFenetre = sf::VideoMode::getDesktopMode().height;
    inline const int largeurMonde = largeurFenetre / tailleTuile;
    inline const int hauteurMonde = hauteurFenetre / tailleTuile;

    //generation monde (bruit)
    constexpr float frequenceBruit = 0.03f;
    
    struct HerbeConfig {
        float energieInitiale = 0.2f;
        float energieMax = 10.0f;
        float ageMaturite = 8.0f;
        float ageDeclin = 20.0f;
        float ageMort = 30.0f;
        float gainCroissance = 1.0f;
        float delaiRepousse = 0.1f;
        float gainMature = 0.2f;
        float perteDeclin = 0.6f;
        int   essaisParFrame = 15;
        float chanceRepousse = 0.20f;
        float tempsProcreation = 5.0f;
        float partageEnergie = 0.5f;
    };
    struct HerbivoreConfig {
        float energieInitiale = 20.0f;
        float energieMax = 20.0f;
        float ageMaturite = 10.0f;
        float ageDeclin = 30.0f;
        float ageMort = 50.0f;
        float perteEnergie = 0.5f;
        float gainParHerbe = 6.0f;
        int populationInitiale = 20;
        float delaiDeplacement = 0.1f;
        float tempsProcreation = 5.0f;
        float coutProcreation = 0.4f;
    };
    struct DangerConfig {
        int nombreInitialPieges = 50;
        int nombreInitialVirus  = 25;
        float chancePropagationVirus = 0.5f;
        float chanceMortVirus = 0.5f;
    };
    inline const HerbivoreConfig herbivore{};
    inline const HerbeConfig herbe{};
    inline const DangerConfig danger{};

}

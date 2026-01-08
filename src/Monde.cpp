#include "Monde.hpp"
#include "Config.hpp"
#include "utils/FastNoiseLite.h"
#include "utils/Random.hpp"

#include "Herbe.hpp"
#include "Herbivore.hpp"
#include "Piege.hpp"
#include "Virus.hpp"

#include <algorithm>
#include <iostream>

Monde::Monde()
    : grille(Config::largeurMonde,
             Config::hauteurMonde,
             Config::tailleTuile),
      timerReplantation(0.f)
{
    genererMonde();
    creerPopulationInitialeHerbivores();
    genererDangersAleatoires();

}

//ajouter un danger
void Monde::ajouterDanger(std::unique_ptr<DangerEnvironnemental> d) {
    dangers.push_back(std::move(d));
}
//generer les dangers
void Monde::genererDangersAleatoires() {
    // Génération des pieges
    int pieges = Config::danger.nombreInitialPieges;
    while (pieges > 0) {
        int x = Random::Int(0, getLargeur() - 1);
        int y = Random::Int(0, getHauteur() - 1);

        if (getTuile(x, y).getType() != TypeTuile::Terre)
            continue;
        ajouterDanger(std::make_unique<Piege>(x, y));
        pieges--;
    }
    // Génération des virus
    int virus = Config::danger.nombreInitialVirus;
    while (virus > 0) {
        int x = Random::Int(0, getLargeur() - 1);
        int y = Random::Int(0, getHauteur() - 1);
        if (getTuile(x, y).getType() != TypeTuile::Terre)
            continue;
        ajouterDanger(std::make_unique<Virus>(x, y));
        virus--;
    }
}

//generer le terrain  
void Monde::genererMonde() {
    FastNoiseLite bruit;
    bruit.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    bruit.SetSeed(Random::Int(0, 10000));
    bruit.SetFrequency(Config::frequenceBruit);

    for (int y = 0; y < getHauteur(); ++y) {
        for (int x = 0; x < getLargeur(); ++x) {
            // Bruit de base
            float n = bruit.GetNoise((float)x, (float)y);

            // Facteur radial pour créer des continents
            float nx = 2.f * x / getLargeur() - 1.f;
            float ny = 2.f * y / getHauteur() - 1.f;
            float distance = nx * nx + ny * ny;

            // Combinaison bruit + distance
            float valeur = n + (1.f - distance * 1.5f);

            if (valeur > 0.4f)
                grille(x, y).setType(TypeTuile::Terre);
            else if (valeur > 0.2f)
                grille(x, y).setType(TypeTuile::Sable);
            else
                grille(x, y).setType(TypeTuile::Eau);
        }
    }
}

//update monde 
void Monde::update(float dt) {

    // Mise à jour des entités
    for (auto& e : entites) {
        if (auto* herbivore = dynamic_cast<Herbivore*>(e.get())) {
            herbivore->update(dt, *this);
        } else {
            e->update(dt);
        }
    }

    // appliquer les dangers
    for (auto& e : entites) {
        auto* herbivore = dynamic_cast<Herbivore*>(e.get());
        if (!herbivore || !herbivore->estVivante())
            continue;

        for (auto& d : dangers) {
            if (!d->estActif())
                continue;

            if (d->getX() == herbivore->getX() &&
                d->getY() == herbivore->getY()) {

                d->appliquerEffet(*herbivore, *this);
            }
        }
    }

    //reproduction
    std::vector<std::unique_ptr<EntiteVivante>> nouveauxNes;

    for (auto& e : entites) {
        if (e->peutSeReproduire()) {
            auto bebe = e->seMultiplier();
            if (bebe)
                nouveauxNes.push_back(std::move(bebe));
        }
    }

    for (auto& n : nouveauxNes)
        entites.push_back(std::move(n));

    //supprimer les morts
    entites.erase(
        std::remove_if(entites.begin(), entites.end(),
            [](const std::unique_ptr<EntiteVivante>& e) {
                return !e->estVivante();
            }),
        entites.end()
    );

    //supprimer les pieges inactifs
    dangers.erase(
    std::remove_if(dangers.begin(), dangers.end(),
        [](const std::unique_ptr<DangerEnvironnemental>& d) {
            return !d->estActif();
        }),
    dangers.end()
    );

    //repousse herbe
    timerReplantation += dt;
    if (timerReplantation < Config::herbe.delaiRepousse)
        return;

    timerReplantation = 0.f;

    for (int i = 0; i < Config::herbe.essaisParFrame; ++i) {
        int x = Random::Int(0, getLargeur() - 1);
        int y = Random::Int(0, getHauteur() - 1);

        if (getTuile(x, y).getType() != TypeTuile::Terre)
            continue;

        bool occupe = false;
        for (const auto& e : entites) {
            if (e->getX() == x && e->getY() == y) {
                occupe = true;
                break;
            }
        }

        if (!occupe && Random::real(0.f, 1.f) < Config::herbe.chanceRepousse) {
            ajouterEntite(std::make_unique<Herbe>(x, y));
        }
    }
}

//generer population
void Monde::creerPopulationInitialeHerbivores() {
    int restants = Config::herbivore.populationInitiale;

    while (restants > 0) {
        int x = Random::Int(0, getLargeur() - 1);
        int y = Random::Int(0, getHauteur() - 1);

        if (getTuile(x, y).getType() == TypeTuile::Eau)
            continue;

        bool occupe = false;
        for (const auto& e : entites) {
            if (e->getX() == x && e->getY() == y) {
                occupe = true;
                break;
            }
        }
        if (occupe)
            continue;

        ajouterEntite(std::make_unique<Herbivore>(x, y));
        restants--;
    }
}


Tuile& Monde::getTuile(int x, int y) {
    return grille(x, y);
}

const Tuile& Monde::getTuile(int x, int y) const {
    return grille(x, y);
}

int Monde::getLargeur() const {
    return grille.getLargeur();
}

int Monde::getHauteur() const {
    return grille.getHauteur();
}

int Monde::getTailleCase() const {
    return grille.getTailleCase();
}

void Monde::ajouterEntite(std::unique_ptr<EntiteVivante> e) {
    entites.push_back(std::move(e));
}
const std::vector<std::unique_ptr<DangerEnvironnemental>>& Monde::getDangers() const {
    return dangers;
}

//Debug
std::ostream& operator<<(std::ostream& os, const Monde& monde) {
    int nbHerbes = 0;
    int nbHerbivores = 0;
    float energieTotale = 0.f;

    for (const auto& e : monde.entites) {
        energieTotale += e->getEnergie();

        if (dynamic_cast<const Herbe*>(e.get()))
            nbHerbes++;
        else if (dynamic_cast<const Herbivore*>(e.get()))
            nbHerbivores++;
    }

    os << "\n===== DEBUG MONDE =====\n";
    os << "Herbes      : " << nbHerbes << "\n";
    os << "Herbivores  : " << nbHerbivores << "\n";
    os << "Entites tot : " << monde.entites.size() << "\n";
    os << "Energie moy : "
       << (monde.entites.empty() ? 0.f
                                 : energieTotale / monde.entites.size())
       << "\n";
    os << "=======================\n";

    return os;
}


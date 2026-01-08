#include "Herbivore.hpp"
#include "Monde.hpp"
#include "Config.hpp"
#include "utils/Random.hpp"
#include "Herbe.hpp"

Herbivore::Herbivore(int x, int y)
    : EntiteVivante(
        x, y,
        Config::herbivore.energieInitiale,
        Config::herbivore.energieMax,
        Config::herbivore.ageMaturite,
        Config::herbivore.ageDeclin,
        Config::herbivore.ageMort
      ),
      timerMange(0.f),
      timerDeplacement(0.f)
{}

void Herbivore::appliquerMetabolisme(float dt, PhaseVie) {
    energie -= Config::herbivore.perteEnergie * dt;
}

void Herbivore::update(float dt, Monde& monde) {
    if (!vivante) return;

    timerMange -= dt;
    EntiteVivante::update(dt);
    if (!vivante) return;

    manger(monde);
    timerDeplacement -= dt;
    if (timerDeplacement <= 0.f) {
        seDeplacer(monde);
        timerDeplacement = Config::herbivore.delaiDeplacement;
    }

}

void Herbivore::manger(Monde& monde) {
    for (const auto& e : monde.getEntites()) {
        Herbe* herbe = dynamic_cast<Herbe*>(e.get());
        if (!herbe) continue;

        if (herbe->getX() == x && herbe->getY() == y) {
            energie += Config::herbivore.gainParHerbe;
            timerMange = 0.3f;
            herbe->update(9999.f);
            break;
        }
    }
}

void Herbivore::seDeplacer(Monde& monde) {
    int dx = 0;
    int dy = 0;

    int choix = Random::Int(0, 3);
    if (choix == 0) dx = 1;
    if (choix == 1) dx = -1;
    if (choix == 2) dy = 1;
    if (choix == 3) dy = -1;

    int nx = x + dx;
    int ny = y + dy;

    if (nx < 0 || ny < 0 ||
        nx >= monde.getLargeur() ||
        ny >= monde.getHauteur())
        return;

    if (monde.getTuile(nx, ny).getType() == TypeTuile::Eau)
        return;

    x = nx;
    y = ny;
}

bool Herbivore::aMange() const {
    return timerMange > 0.f;
}

std::unique_ptr<EntiteVivante> Herbivore::seMultiplier() {
    resetTimerProcreation(Config::herbivore.tempsProcreation);
    energie -= energieMax * Config::herbivore.coutProcreation;

    return std::make_unique<Herbivore>(x, y);
}
void Herbivore::tuer(){
    vivante = false;
}
void Herbivore::perdreEnergie(float e) {
    energie -= e;
}

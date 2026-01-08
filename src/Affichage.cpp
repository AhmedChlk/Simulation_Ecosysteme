#include "Affichage.hpp"
#include "Config.hpp"
#include "Herbivore.hpp"
#include "Piege.hpp"
#include "Virus.hpp"

Affichage::Affichage(const Monde& m) : monde(m) {
    tailleCase = monde.getTailleCase();
    fenetre.create(
        sf::VideoMode(Config::largeurFenetre, Config::hauteurFenetre),
        "Simulation Ecosysteme",
        sf::Style::Default
    );
    fenetre.setFramerateLimit(60);
}

bool Affichage::estOuvert() const {
    return fenetre.isOpen();
}


void Affichage::gererEvenements() {
    sf::Event evenement;
    while (fenetre.pollEvent(evenement)) {
         // Fermeture de la fenêtre bouton X
        if (evenement.type == sf::Event::Closed)
            fenetre.close();
         // Fermeture de la fenêtre bouton echap
        if (evenement.type == sf::Event::KeyPressed) {
            if (evenement.key.code == sf::Keyboard::Escape) {
                fenetre.close();
            }
        }
         // afficher le print de Debig avec touche D
        if (evenement.key.code == sf::Keyboard::D) {
            std::cout << monde;
        }
    }
}

void Affichage::dessiner() {
    fenetre.clear(sf::Color::Black);
    //Tuile
    for (int y = 0; y < monde.getHauteur(); y++) {
        for (int x = 0; x < monde.getLargeur(); x++) {
            const Tuile& tuile = monde.getTuile(x, y);
            sf::RectangleShape rectangle(sf::Vector2f(tailleCase, tailleCase));
            rectangle.setPosition(x * tailleCase, y * tailleCase);

            switch (tuile.getType()) {
                case TypeTuile::Eau:
                    rectangle.setFillColor(sf::Color::Blue);
                    break;
                case TypeTuile::Terre:
                    rectangle.setFillColor(sf::Color(137, 81, 41));
                    break;
                case TypeTuile::Sable:
                    rectangle.setFillColor(sf::Color::Yellow);
                    break;
                default:
                    rectangle.setFillColor(sf::Color::White);
                    break;
            }

            fenetre.draw(rectangle);
        }
    }

    //herbe
    sf::RectangleShape herbe(
        sf::Vector2f(tailleCase * 0.6f, tailleCase * 0.6f)
    );

    for (const auto& e : monde.getEntites()) {
        float r = e->ratioEnergie(); 
        sf::Color couleur;

        if (r > 0.6f) {
            couleur = sf::Color(40, 180, 40);
        }
        else if (r > 0.3f) {
            couleur = sf::Color(60, 140, 60);
        }
        else {
            float t = r / 0.3f;
            int rouge = 120 + static_cast<int>((255 - 120) * (1.f - t));
            int vert  = 140 - static_cast<int>(80 * (1.f - t));
            couleur = sf::Color(rouge, vert, 40);
        }

        herbe.setFillColor(couleur);

        herbe.setPosition(
            e->getX() * tailleCase + tailleCase * 0.2f,
            e->getY() * tailleCase + tailleCase * 0.2f
        );

        fenetre.draw(herbe);
    }
    //herbivore
    sf::CircleShape herbivoreShape(tailleCase * 0.4f);
    herbivoreShape.setOrigin(
        tailleCase * 0.4f,
        tailleCase * 0.4f
    );

    for (const auto& e : monde.getEntites()) {
        const Herbivore* herbivore = dynamic_cast<const Herbivore*>(e.get());
        if (!herbivore)
            continue;

        // Couleur selon l’état
        if (!herbivore->estVivante()) {
            herbivoreShape.setFillColor(sf::Color::Red);
        }
        else if (herbivore->aMange()) {
            herbivoreShape.setFillColor(sf::Color(200, 200, 200)); // gris clair
        }
        else {
            herbivoreShape.setFillColor(sf::Color::White);
        }

        herbivoreShape.setPosition(
            herbivore->getX() * tailleCase + tailleCase / 2.f,
            herbivore->getY() * tailleCase + tailleCase / 2.f
        );

        fenetre.draw(herbivoreShape);
    }

    // Pièges
    sf::RectangleShape piegeShape(
        sf::Vector2f(tailleCase * 0.6f, tailleCase * 0.6f)
    );
    piegeShape.setFillColor(sf::Color(120, 20, 20));

    // Virus
    sf::CircleShape virusShape(tailleCase * 0.3f);
    virusShape.setFillColor(sf::Color(160, 50, 200));
    virusShape.setOrigin(
        tailleCase * 0.3f,
        tailleCase * 0.3f
    );

    for (const auto& d : monde.getDangers()) {

        if (dynamic_cast<const Piege*>(d.get())) {
            piegeShape.setPosition(
                d->getX() * tailleCase + tailleCase * 0.2f,
                d->getY() * tailleCase + tailleCase * 0.2f
            );
            fenetre.draw(piegeShape);
        }

        else if (dynamic_cast<const Virus*>(d.get())) {
            virusShape.setPosition(
                d->getX() * tailleCase + tailleCase / 2.f,
                d->getY() * tailleCase + tailleCase / 2.f
            );
            fenetre.draw(virusShape);
        }
    }


    fenetre.display();
}

#pragma once
#include <vector>

template <typename T>
class Grille {
    private:
    int largeur;
    int hauteur;
    int tailleCase;
    std::vector<T> donnees;
public:
    Grille(int largeur, int hauteur, int tailleCase) : largeur(largeur), hauteur(hauteur), tailleCase(tailleCase) 
    {
        donnees.resize(largeur * hauteur);
    }
    ~Grille() = default;

    T& operator()(int x, int y) {
        return  donnees[y * largeur + x];;
    }

    const T& operator()(int x, int y) const {
        return donnees[y * largeur + x];
    }

    int pixelVersCase(float position) const {
        return position / tailleCase;
    }

    bool estDansGrille(int x, int y) const {
        return x >= 0 && x < largeur && y >= 0 && y < hauteur;
    }

    void remplir(const T& valeur) {
        for (int i = 0; i < donnees.size(); i++) {
            donnees[i] = valeur;
        }
    }

    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }
    int getTailleCase() const { return tailleCase; }


};
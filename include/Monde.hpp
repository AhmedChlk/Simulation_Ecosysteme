#pragma once
#include <memory>
#include <vector>

#include "utils/Grille.hpp"
#include "Tuile.hpp"
#include "EntiteVivante.hpp"
    #include "DangerEnvironnemental.hpp"

class Monde {
private:
    Grille<Tuile> grille;
    void genererMonde();
    std::vector<std::unique_ptr<DangerEnvironnemental>> dangers;
    std::vector<std::unique_ptr<EntiteVivante>> entites;
    float timerReplantation;
public:
    Monde();
    
    void update(float dt);
    
    void ajouterEntite(std::unique_ptr<EntiteVivante> e);
    
    const std::vector<std::unique_ptr<EntiteVivante>>& getEntites() const { return entites; }
    
    Tuile& getTuile(int x, int y);
    
    const Tuile& getTuile(int x, int y) const;
    
    int getLargeur() const;
    
    int getHauteur() const;
    
    int getTailleCase() const;
    
    const std::vector<std::unique_ptr<DangerEnvironnemental>>& getDangers() const;
    
    void creerPopulationInitialeHerbivores();
    
    void ajouterDanger(std::unique_ptr<DangerEnvironnemental> d);
    
    void genererDangersAleatoires();
    
    friend std::ostream& operator<<(std::ostream& os, const Monde& monde);
};


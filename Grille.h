#pragma once
#include "Cellule.h"
#include "Observateur.h"
#include <vector>
#include <iostream>
#include <cstdlib>

class Grille : public Sujet {
private:
    int ligne, col;
    std::vector<Cellule> plateauJeu;

public:
    Grille(int ligne, int col);

    int getLigne() const;
    int getCol() const;
    const std::vector<Cellule>& getPlateau() const;

    int index(int i, int j) const;

    int Voisin(int i, int j);

    void compterVoisine();

    void jouerTour();

    void setEtats(const std::vector<std::vector<bool>>& etats);
};

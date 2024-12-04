#include "Grille.h"

Grille::Grille(int ligne, int col) : ligne(ligne), col(col), plateauJeu(ligne * col) {}

int Grille::getLigne() const { return ligne; }

int Grille::getCol() const { return col; }

const std::vector<Cellule>& Grille::getPlateau() const { return plateauJeu; }

int Grille::index(int i, int j) const { return i * col + j; }

int Grille::Voisin(int i, int j) {
    int voisinsEnVie = 0;

    if (i > 0) {
        voisinsEnVie += plateauJeu[index(i - 1, j)].isVivante();
        if (j > 0) voisinsEnVie += plateauJeu[index(i - 1, j - 1)].isVivante();
        if (j < (col - 1)) voisinsEnVie += plateauJeu[index(i - 1, j + 1)].isVivante();
    }

    if (i < (ligne - 1)) {
        voisinsEnVie += plateauJeu[index(i + 1, j)].isVivante();
        if (j > 0) voisinsEnVie += plateauJeu[index(i + 1, j - 1)].isVivante();
        if (j < (col - 1)) voisinsEnVie += plateauJeu[index(i + 1, j + 1)].isVivante();
    }

    if (j > 0) voisinsEnVie += plateauJeu[index(i, j - 1)].isVivante();
    if (j < (col - 1)) voisinsEnVie += plateauJeu[index(i, j + 1)].isVivante();

    return voisinsEnVie;
}

void Grille::compterVoisine() {
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < col; ++j) {
            plateauJeu[index(i, j)].setNbrVoisins(Voisin(i, j));
        }
    }
}

void Grille::jouerTour() {
    std::vector<Cellule> nouvelleGeneration = plateauJeu;
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < col; ++j) {
            int voisins = plateauJeu[index(i, j)].getNbrVoisins();
            if (plateauJeu[index(i, j)].isVivante()) {
                nouvelleGeneration[index(i, j)].setEtat(voisins == 2 || voisins == 3);
            } else {
                nouvelleGeneration[index(i, j)].setEtat(voisins == 3);
            }
        }
    }
    plateauJeu = nouvelleGeneration;
    notifierObservateurs(*this);
}

void Grille::setEtats(const std::vector<std::vector<bool>>& etats) {
    if (etats.size() != ligne || (etats.size() > 0 && etats[0].size() != col)) {
        std::cerr << "Erreur : Dimensions incompatibles entre la grille et le vecteur d'états." << std::endl;
        exit(1);
    }

    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < col; ++j) {
            plateauJeu[index(i, j)].setEtat(etats[i][j]);
        }
    }
}


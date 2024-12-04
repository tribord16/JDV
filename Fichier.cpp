#include "Fichier.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

Fichier::Fichier(const std::string& chemin) : chemin(chemin), ligne(0), col(0) {}

int Fichier::getLigne() const { return ligne; }

int Fichier::getCol() const { return col; }

const std::vector<std::vector<bool>>& Fichier::getEtats() const { return etats; }

void Fichier::lireFichier() {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) {
        throw std::runtime_error("Erreur : Impossible d'ouvrir le fichier " + chemin);
    }

    fichier >> ligne >> col;
    std::cout << "Dimensions " << ligne << " x " << col << std::endl;

    etats.resize(ligne, std::vector<bool>(col));
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < col; ++j) {
            int etat;
            fichier >> etat;
            etats[i][j] = (etat == 1);
        }
    }

    fichier.close();
}

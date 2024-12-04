#include "System.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;

System::System(sf::RenderWindow& window, int toursMax, const std::string& fichierEntree, const std::string& dossierSortie, int dureeEntreIterations)
    : grille(nullptr), interfaceGraphique(window, 20), // Taille par défaut des cellules graphiques
      tourActuel(0), tourMax(toursMax),
      fichierEntree(fichierEntree), dossierSortie(dossierSortie), dureeEntreIterations(dureeEntreIterations) {
    if (!fs::exists(dossierSortie)) {
        fs::create_directory(dossierSortie);
    }
    chargerDepuisFichier();
    grille->ajouterObservateur(&interfaceGraphique);
}

System::~System() {
    delete grille; // Libération de la mémoire allouée pour grille
}

void System::chargerDepuisFichier() {
    std::ifstream fichier(fichierEntree);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier d'entrée " << fichierEntree << std::endl;
        exit(1);
    }

    int ligne, col;
    fichier >> ligne >> col;

    grille = new Grille(ligne, col); // Initialisation dynamique de la grille

    std::vector<std::vector<bool>> etats(ligne, std::vector<bool>(col));
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < col; ++j) {
            int etat;
            fichier >> etat;
            etats[i][j] = (etat == 1);
        }
    }
    grille->setEtats(etats);
    fichier.close();
}

void System::sauvegarderDansFichier() {
    if (!fs::exists(dossierSortie)) {
        fs::create_directory(dossierSortie);
    }

    std::ostringstream nomFichier;
    nomFichier << dossierSortie << "/tour_" << tourActuel << ".txt";

    std::ofstream fichier(nomFichier.str());
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier de sortie " << nomFichier.str() << std::endl;
        return;
    }

    std::cout << "Sauvegarde dans le fichier : " << nomFichier.str() << std::endl;

    fichier << grille->getLigne() << " " << grille->getCol() << "\n";
    for (int i = 0; i < grille->getLigne(); ++i) {
        for (int j = 0; j < grille->getCol(); ++j) {
            fichier << (grille->getPlateau()[grille->index(i, j)].isVivante() ? 1 : 0) << " ";
        }
        fichier << "\n";
    }
    fichier.close();
}

void System::gererEvenements(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (interfaceGraphique.isBoutonGraphiqueClicked(mousePos)) {
                interfaceGraphique.basculerMode(false);
            }
            if (interfaceGraphique.isBoutonConsoleClicked(mousePos)) {
                interfaceGraphique.basculerMode(true);
            }
        }
    }
}

void System::demarrerSimulation() {
    sf::RenderWindow& window = interfaceGraphique.getWindow();

    while (window.isOpen() && tourActuel < tourMax) {
        gererEvenements(window);

        grille->compterVoisine();
        grille->jouerTour();

        sauvegarderDansFichier();

        std::this_thread::sleep_for(std::chrono::milliseconds(dureeEntreIterations));
        tourActuel++;
    }
}

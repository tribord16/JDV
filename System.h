#pragma once
#include "Grille.h"
#include "InterfaceGraphique.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>

class System {
private:
    Grille* grille; 
    InterfaceGraphique interfaceGraphique;
    int tourActuel;
    int tourMax;
    std::string fichierEntree;
    std::string dossierSortie;
    int dureeEntreIterations;

    void chargerDepuisFichier();
    void sauvegarderDansFichier();
    void gererEvenements(sf::RenderWindow& window);

public:
    System(sf::RenderWindow& window, int toursMax, const std::string& fichierEntree, const std::string& dossierSortie, int dureeEntreIterations);
    ~System();
    void demarrerSimulation();
};

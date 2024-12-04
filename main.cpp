#include <SFML/Graphics.hpp>
#include "System.h"
#include "Fichier.h"

#include <iostream>
#include <string>

int main() {
    std::string cheminFichier;
    std::cout << "Chemin fichier d'entree : ";
    std::cin >> cheminFichier;

    int dureeEntreIterations;
    std::cout << "Temps entre les interations : ";
    std::cin >> dureeEntreIterations;
   
    try {
        Fichier fichier(cheminFichier);
        fichier.lireFichier();

        sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de la Vie");
        System system(window, 20, fichier.getChemin(), "etat_sauvegarde", dureeEntreIterations);

        system.demarrerSimulation();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
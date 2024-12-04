#include "catch_amalgamated.hpp"
#include "System.h"
#include <sstream>
#include <fstream>
#include <iostream>

TEST_CASE("Tests de la classe System") {
    std::string fichierInitial = "etat_initial.txt";
    std::string fichierSauvegarde = "etat_sauvegarde.txt";

    // Écriture d'un fichier d'état initial pour les tests
    std::ofstream fichier(fichierInitial);
    fichier << "5 5\n"
               "1 1 0 0 1\n"
               "0 1 1 1 0\n"
               "1 1 0 0 0\n"
               "0 0 1 1 1\n"
               "1 0 0 0 1\n";
    fichier.close();

    // Création d'une fenêtre SFML (obligatoire pour l'interface graphique)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test System");

    // Initialisation de l'objet System
    System system(5, 5, 5, window, 3, fichierInitial, fichierSauvegarde,100);

    SECTION("Lecture du fichier initial") {
        REQUIRE_NOTHROW(system.chargerDepuisFichier());
        const Grille& grille = system.getGrille();

        REQUIRE(grille.getLigne() == 5);
        REQUIRE(grille.getCol() == 5);

        REQUIRE(grille.getPlateau()[grille.index(0, 0)].isVivante() == true);
        REQUIRE(grille.getPlateau()[grille.index(2, 2)].isVivante() == false);
        REQUIRE(grille.getPlateau()[grille.index(4, 4)].isVivante() == true);
    }

    SECTION("Simulation d'un tour") {
        system.chargerDepuisFichier();
        system.simulerUnTour();

        const Grille& grille = system.getGrille();

        REQUIRE(grille.getPlateau()[grille.index(0, 0)].isVivante() == true);
        REQUIRE(grille.getPlateau()[grille.index(2, 2)].isVivante() == false);
        REQUIRE(grille.getPlateau()[grille.index(4, 4)].isVivante() == true);
    }

    SECTION("Sauvegarde après un tour") {
        system.chargerDepuisFichier();
        system.simulerUnTour();
        system.sauvegarderDansFichier();

        std::ifstream fichierTest(fichierSauvegarde);
        REQUIRE(fichierTest.is_open());

        std::stringstream contenu;
        contenu << fichierTest.rdbuf();
        fichierTest.close();

          std::string etatAttendu =
            "5 5\n"
            "1 1 0 1 0\n"
            "0 0 0 1 0\n"
            "1 0 0 0 1\n"
            "1 0 1 1 1\n"
            "0 0 0 0 1\n";
        std::cout << "Contenu réel :\n" << contenu.str() << std::endl;
        std::cout << "Contenu attendu :\n" << etatAttendu << std::endl;



      

        REQUIRE(contenu.str() == etatAttendu);
        
    }

    // Nettoyage des fichiers générés
    std::remove(fichierInitial.c_str());
    std::remove(fichierSauvegarde.c_str());
}

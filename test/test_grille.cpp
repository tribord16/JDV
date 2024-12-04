#include "catch_amalgamated.hpp"
#include "Grille.h"

TEST_CASE("Tests de la classe Grille") {
    Grille grille(5, 5);

    SECTION("Initialisation de la grille") {
        REQUIRE(grille.getLigne() == 5);
        REQUIRE(grille.getCol() == 5);
        REQUIRE(grille.getPlateau().size() == 25);
    }

    SECTION("Accès aux indices") {
        REQUIRE(grille.index(0, 0) == 0);
        REQUIRE(grille.index(4, 4) == 24);
    }

    SECTION("Mise à jour des états") {
        std::vector<std::vector<bool>> etats = {
            {1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0},
            {1, 1, 0, 0, 0},
            {0, 0, 1, 1, 1},
            {1, 0, 0, 0, 1}
        };

        grille.setEtats(etats);

        REQUIRE(grille.getPlateau()[grille.index(0, 0)].isVivante() == true);
        REQUIRE(grille.getPlateau()[grille.index(2, 2)].isVivante() == false);
        REQUIRE(grille.getPlateau()[grille.index(4, 4)].isVivante() == true);
    }

    SECTION("Comptage des voisins") {
        std::vector<std::vector<bool>> etats = {
            {1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0},
            {1, 1, 0, 0, 0},
            {0, 0, 1, 1, 1},
            {1, 0, 0, 0, 1}
        };

        grille.setEtats(etats);
        grille.compterVoisine();

        REQUIRE(grille.getPlateau()[grille.index(0, 0)].getNbrVoisins() == 2); 
        REQUIRE(grille.getPlateau()[grille.index(2, 2)].getNbrVoisins() == 6);
        REQUIRE(grille.getPlateau()[grille.index(4, 4)].getNbrVoisins() == 2);
    }

    SECTION("Jouer un tour") {
        std::vector<std::vector<bool>> etats = {
            {1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0},
            {1, 1, 0, 0, 0},
            {0, 0, 1, 1, 1},
            {1, 0, 0, 0, 1}
        };

        grille.setEtats(etats);
        grille.compterVoisine();
        grille.jouerTour();

        REQUIRE(grille.getPlateau()[grille.index(0, 0)].isVivante() == true);
        REQUIRE(grille.getPlateau()[grille.index(2, 2)].isVivante() == false);
        REQUIRE(grille.getPlateau()[grille.index(4, 4)].isVivante() == true); 
    }
}

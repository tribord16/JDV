#include "catch_amalgamated.hpp"
#include "Cellule.h"

TEST_CASE("Tests de la classe Cellule") {
    Cellule cellule;

    SECTION("Initialisation par défaut") {
        REQUIRE(cellule.isVivante() == false);
        INFO("Cellule nouvellement créée doit être morte par défaut.");
        REQUIRE(cellule.getNbrVoisins() == 0);
        INFO("Cellule nouvellement créée doit avoir 0 voisins.");
    }

    SECTION("Modification de l'état") {
        cellule.setEtat(true);
        REQUIRE(cellule.isVivante() == true);
        INFO("Cellule doit être vivante après appel à setEtat(true).");

        cellule.setEtat(false);
        REQUIRE(cellule.isVivante() == false);
        INFO("Cellule doit être morte après appel à setEtat(false).");
    }

    SECTION("Modification du nombre de voisins") {
        cellule.setNbrVoisins(3);
        REQUIRE(cellule.getNbrVoisins() == 3);
        INFO("Cellule doit avoir 3 voisins après appel à setNbrVoisins(3).");

        cellule.setNbrVoisins(0);
        REQUIRE(cellule.getNbrVoisins() == 0);
        INFO("Cellule doit avoir 0 voisins après appel à setNbrVoisins(0).");
    }
}

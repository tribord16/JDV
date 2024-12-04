#pragma once
#include "Interface.h"
#include "Boutton.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class InterfaceGraphique : public Interface {
private:
    sf::RenderWindow& window;
    int tailleCellule;
    bool modeConsole;
    std::vector<Boutton> boutons;

    void afficherGrille(const Grille& grille);
    void afficherConsole(const Grille& grille);

public:
    InterfaceGraphique(sf::RenderWindow& window, int tailleCellule);
    void miseAJour(const Grille& grille) override;
    void basculerMode(bool modeConsole);
    bool isBoutonGraphiqueClicked(const sf::Vector2i& mousePos) const;
    bool isBoutonConsoleClicked(const sf::Vector2i& mousePos) const;
    sf::RenderWindow& getWindow();
    void afficher(const Grille& grille) override; // Ajoutez cette méthode
};

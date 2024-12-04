#include "InterfaceGraphique.h"

InterfaceGraphique::InterfaceGraphique(sf::RenderWindow& window, int tailleCellule)
    : window(window), tailleCellule(tailleCellule), modeConsole(false) {
    boutons.push_back(Boutton("Graphique", 100, 30));
    boutons.push_back(Boutton("Console", 100, 30));

    for (size_t i = 0; i < boutons.size(); ++i) {
        boutons[i].rectangle.setPosition(10 + i * 110, 10);
        boutons[i].text.setPosition(15 + i * 110, 15);
    }
}

void InterfaceGraphique::afficherGrille(const Grille& grille) {
    for (int i = 0; i < grille.getLigne(); ++i) {
        for (int j = 0; j < grille.getCol(); ++j) {
            sf::RectangleShape cellule(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
            cellule.setPosition(j * tailleCellule, i * tailleCellule + 50);
            cellule.setFillColor(grille.getPlateau()[grille.index(i, j)].isVivante() ? sf::Color::Green : sf::Color::Red);
            window.draw(cellule);
        }
    }
}

void InterfaceGraphique::afficherConsole(const Grille& grille) {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) return;

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 50);

    std::string affichage;
    for (int i = 0; i < grille.getLigne(); ++i) {
        for (int j = 0; j < grille.getCol(); ++j) {
            affichage += grille.getPlateau()[grille.index(i, j)].isVivante() ? 'O' : '.';
            affichage += " ";
        }
        affichage += "\n";
    }
    text.setString(affichage);
    window.draw(text);
}

void InterfaceGraphique::miseAJour(const Grille& grille) {
    window.clear(sf::Color::Black);
    if (modeConsole)
        afficherConsole(grille);
    else
        afficherGrille(grille);

    for (const auto& bouton : boutons) {
        window.draw(bouton.rectangle);
        window.draw(bouton.text);
    }
    window.display();
}

void InterfaceGraphique::basculerMode(bool modeConsole) {
    this->modeConsole = modeConsole;
}

bool InterfaceGraphique::isBoutonGraphiqueClicked(const sf::Vector2i& mousePos) const {
    return boutons[0].rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool InterfaceGraphique::isBoutonConsoleClicked(const sf::Vector2i& mousePos) const {
    return boutons[1].rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

sf::RenderWindow& InterfaceGraphique::getWindow() {
    return window;
}

void InterfaceGraphique::afficher(const Grille& grille) {
    if (modeConsole) {
        afficherConsole(grille);
    } else {
        afficherGrille(grille);
    }
}
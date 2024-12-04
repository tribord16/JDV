#include "Boutton.h"

Boutton::Boutton(const std::string& texte, int largeur, int hauteur) {
    rectangle.setSize(sf::Vector2f(largeur, hauteur));
    rectangle.setFillColor(sf::Color::Blue);

    text.setString(texte);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
}

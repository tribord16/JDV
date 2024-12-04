#pragma once 
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Boutton {
public:
    sf::Text text;
    sf::RectangleShape rectangle;

    int hauteur, longueur;
    Boutton(const std::string& texte, int largeur, int hauteur);
};
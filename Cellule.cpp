#include "Cellule.h"

Cellule::Cellule() : etat(false), nbrVoisins(0) {}

Cellule::Cellule(bool etat) : etat(etat), nbrVoisins(0) {}

bool Cellule::isVivante() const { return etat; }

int Cellule::getNbrVoisins() const { return nbrVoisins; }

void Cellule::setEtat(bool nouvelEtat) { etat = nouvelEtat; }

void Cellule::setNbrVoisins(int nbr) { nbrVoisins = nbr; }

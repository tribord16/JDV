#pragma once
#include "Observateur.h"
#include "Grille.h"

class Interface : public Observateur {
public:
    virtual void afficher(const Grille& grille) = 0;
    virtual ~Interface() = default;
};

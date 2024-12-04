#pragma once
#include <vector>

class Grille;

class Observateur {
public:
    virtual void miseAJour(const Grille& grille) = 0; 
    virtual ~Observateur() = default;
};

class Sujet {
private:
    std::vector<Observateur*> observateurs; 

public:
    void ajouterObservateur(Observateur* observateur) {
        observateurs.push_back(observateur);
    }

    void notifierObservateurs(const Grille& grille) {
        for (Observateur* observateur : observateurs) {
            observateur->miseAJour(grille);
        }
    }
};

#pragma once

class Cellule {
private:
    bool etat;          
    int nbrVoisins;     

public:
    Cellule();
    Cellule(bool etat);

    bool isVivante() const;
    int getNbrVoisins() const;

    void setEtat(bool nouvelEtat);
    void setNbrVoisins(int nbr);
};

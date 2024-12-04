#pragma once
#include <string>
#include <vector>

class Fichier {
private:
    std::string chemin;
    int ligne;
    int col;
    std::vector<std::vector<bool>> etats;

public:
    Fichier(const std::string& chemin);

    int getLigne() const;
    int getCol() const;
    const std::vector<std::vector<bool>>& getEtats() const;
    const std::string& getChemin() const {
        return chemin;
    }
    void lireFichier();
};

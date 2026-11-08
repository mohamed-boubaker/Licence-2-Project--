/**
 * @file SautAuto.h
 * @brief Déclaration de la classe SautAuto pour le jeu Geometry Shark.
 */
#ifndef _SAUTAUTO_H
#define _SAUTAUTO_H

#include <vector>
#include <iostream>

using namespace std;


/**
 * @class SautAuto
 * @brief Représente une plateforme qui fait sauter automatiquement le joueur.
 */
class SautAuto {
    private:
        vector<int> v1; // coordonnées du saut automatique (x1, y1, x2, y2)
    
    public:
    /**
     * @brief Constructeur par défaut. Initialise les coordonnées à zéro.
     */
        SautAuto();

    /**
     * @brief Constructeur avec coordonnées.
     * @param v2 Coordonnées du saut automatique
     */
        SautAuto(vector<int> v2);

    /**
     * @brief Fait défiler le saut automatique vers la gauche.
     * @param vitesse_x Vitesse horizontale du défilement
     */
        void defiler_sautAuto(int vitesse_x);

    /**
     * @brief Accès aux coordonnées du saut automatique.
     * @return Référence au vecteur des coordonnées
     */
        vector<int>& getv1() { return v1; }
        
};

#endif

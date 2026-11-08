/**
 * @file SautClick.h
 * @brief Déclaration de la classe SautClick pour le jeu Geometry Shark.
 */
#ifndef _SAUTCLICK_H
#define _SAUTCLICK_H

#include <vector>
#include <iostream>

using namespace std;


/**
 * @class SautClick
 * @brief Représente une zone qui permet au joueur de sauter lorsqu'on appuie sur une touche.
 */
class SautClick {
    private:
        vector<int> v1; // coordonnées de la zone de saut au clic (x1, y1, x2, y2)
    
    public:
     /**
     * @brief Constructeur par défaut. Initialise les coordonnées à zéro.
     */
        SautClick();
    
    /**
     * @brief Constructeur avec coordonnées.
     * @param v2 Coordonnées de la zone de saut au clic
     */
        SautClick(vector<int> v2);
    
    /**
     * @brief Fait défiler la zone de saut au clic vers la gauche.
     * @param vitesse_x Vitesse de déplacement horizontal
     */
        void defiler_sautClick(int vitesse_x);
    
    /**
     * @brief Accès aux coordonnées de la zone.
     * @return Référence au vecteur de coordonnées
     */
        vector<int>& getv1() { return v1; }
        
};

#endif

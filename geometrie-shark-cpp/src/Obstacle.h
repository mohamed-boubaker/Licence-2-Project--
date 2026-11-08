/**
 * @file Obstacle.h
 * @brief Déclaration de la classe Obstacle pour le jeu Geometry Shark.
 */
#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include <vector>
#include <iostream>

using namespace std;

/**
 * @class Obstacle
 * @brief représente les obstacle que le joueur doit éviter.
 */

class Obstacle {
private:
    vector<int> v1;// Coordonnées de l'obstacle (x1, y1, x2, y2)

public:
    /**
     * @brief Constructeur par défaut.
     */
    Obstacle();


    /**
     * @brief Constructeur avec coordonnées.
     * @param v2 Vecteur contenant les coordonnées de l'obstacle
     */
    Obstacle(vector<int> v2);


    /**
     * @brief Fait défiler l'obstacle vers la gauche.
     * @param vitesse_x Vitesse du défilement horizontal
     */
    void defiler_obstacle(int vitesse_x);

    /**
     * @brief Accès aux coordonnées de l'obstacle.
     * @return Référence au vecteur de coordonnées
     */
    vector<int>& getv1() { return v1; };

    
};

#endif

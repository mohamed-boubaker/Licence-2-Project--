/**
 * @file Obstacle.cpp
 * @brief Implémentation des méthodes de la classe Obstacle.
 */
#include "Obstacle.h"
#include <iostream>

using namespace std;

/**
 * @brief Constructeur par défaut. Initialise les coordonnées de l'obstacle à 0.
 */
Obstacle::Obstacle() {
    v1.push_back(0);
    v1.push_back(0);
    v1.push_back(0);
    v1.push_back(0);
}

/**
 * @brief Constructeur avec un vecteur de coordonnées.
 * @param v2 Vecteur contenant les coordonnées de l'obstacle (x1, y1, x2, y2)
 */
Obstacle::Obstacle(vector<int> v2) {
    v1 = v2;
}

/**
 * @brief Fait défiler l'obstacle vers la gauche en fonction de la vitesse.
 * @param vitesse_x Vitesse horizontale du défilement
 */
void Obstacle::defiler_obstacle(int vitesse_x){
    v1[0] -= vitesse_x;
    v1[2] -= vitesse_x;
}


/*
bool Obstacle::pique(vector<int> joueurV1) {
    bool touche = (v1 == joueurV1);

    if (touche) {
        cout << "Le joueur a touché un Pique et meurt !" << endl;
        return true;
    }
    return false;
}
*/

/**
 * @file SautClick.cpp
 * @brief Implémentation des méthodes de la classe SautClick.
 */

#include "SautClick.h"
#include <iostream>


/**
 * @brief Constructeur par défaut. Initialise les coordonnées à 0.
 */
SautClick::SautClick() {
    v1 = {0, 0, 0, 0}; // Initialisation vide par défaut
}

/**
 * @brief Constructeur avec paramètres.
 * @param v2 Coordonnées de la zone de saut au clic
 */
SautClick::SautClick(vector<int> v2) {
    v1 = v2;
}

/**
 * @brief Fait défiler la plateforme de saut au clic vers la gauche.
 * @param vitesse_x Vitesse de déplacement horizontal
 */
void SautClick::defiler_sautClick(int vitesse_x) {
    v1[0] -=vitesse_x;
    v1[2] -=vitesse_x;

}

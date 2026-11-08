/**
 * @file SautAuto.cpp
 * @brief Implémentation des méthodes de la classe SautAuto.
 */
#include "SautAuto.h"
#include <iostream>

/**
 * @brief Constructeur par défaut. Initialise les coordonnées à 0.
 */
SautAuto::SautAuto() {
    v1 = {0, 0, 0, 0}; // Initialisation vide par défaut
}

/**
 * @brief Constructeur avec paramètres.
 * @param v2 Coordonnées de la zone de saut automatique
 */
SautAuto::SautAuto(vector<int> v2) {
    v1 = v2;
}

/**
 * @brief Fait défiler la plateforme de saut automatique vers la gauche.
 * @param vitesse_x Vitesse de déplacement horizontal
 */
void SautAuto::defiler_sautAuto(int vitesse_x) {
    v1[0] -=vitesse_x;
    v1[2] -=vitesse_x;

}


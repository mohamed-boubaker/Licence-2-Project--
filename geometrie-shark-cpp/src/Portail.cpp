/**
 * @file Portail.cpp
 * @brief Implémentation des méthodes de la classe Portail.
 */
#include "Portail.h"
#include <iostream>

using namespace std;

/**
 * @brief Constructeur par défaut du portail. Initialise les coordonnées à 0.
 */
Portail::Portail() {
    v1 = {0, 0, 0, 0}; // Initialisation vide par défaut
}

/**
 * @brief Constructeur avec paramètres.
 * @param v2 Coordonnées du portail (x1, y1, x2, y2)
 * @param mode Mode de fonctionnement du portail (0, 1, 2...)
 */
Portail::Portail(vector<int> v2, int mode) {
    v1 = v2;
    active = true;
    mode_portail = mode;
}


/**
 * @brief Fait défiler le portail vers la gauche.
 * @param vitesse_x Vitesse de déplacement horizontale
 */
void Portail::defiler_portail(int vitesse_x) {
    v1[0] -=vitesse_x;
    v1[2] -=vitesse_x;

}

/**
 * @brief Marque le portail comme utilisé (inactif).
 */
void Portail::portailtoucher(){
    active = false;
}

/**
 * @brief Indique si le portail est encore actif (non utilisé).
 * @return true si le portail est activable, false sinon
 */
bool Portail::getportail(){
    return active;
}
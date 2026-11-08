/**
 * @file Surface.cpp
 * @brief Implémentation des méthodes de la classe Surface.
 */
#include "surface.h"
using namespace std;

/**
 * @brief Constructeur de Surface avec vecteur de coordonnées.
 * @param v2 Coordonnées de la surface (x1, y1, x2, y2)
 */
Surface::Surface(vector<int> v2){
v1 = v2;
} 

/**
 * @brief Constructeur par défaut. Initialise la surface avec des coordonnées nulles.
 */
Surface::Surface(){
    v1.push_back(0);
    v1.push_back(0);
    v1.push_back(0);
    v1.push_back(0);

}

/**
 * @brief Fait défiler la surface vers la gauche.
 * @param vitesse_x Vitesse du défilement horizontal
 */
void Surface::defiler_surface(int vitesse_x){

    v1[0] -= vitesse_x;
    v1[2] -= vitesse_x;
}

/**
 * @brief Met à jour les coordonnées de la surface à partir d'une autre.
 * @param s Pointeur vers la surface source
 */
void Surface::setV1(Surface* s){
    v1= s->getV1();
}
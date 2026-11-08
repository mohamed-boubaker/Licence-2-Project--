/**
 * @file Surface.h
 * @brief Déclaration de la classe Surface pour le jeu Geometry Shark.
 */
#ifndef _SURFACE_H
#define _SURFACE_H

#include <vector>
using namespace std;

/**
 * @class Surface
 * @brief Représente une surface sur laquelle le joueur peut se déplacer ou interagir.
 */
class Surface
{
    private:
    vector<int> v1; // coordonnées de la surface (x1, y1, x2, y2)

    public:

    /**
     * @brief Constructeur par défaut. Initialise une surface vide.
     */
    Surface();

    /**
     * @brief Constructeur avec vecteur de coordonnées.
     * @param v2 Coordonnées de la surface
     */
    Surface(vector<int> v2);

    /**
     * @brief Accès aux coordonnées de la surface.
     * @return Référence au vecteur de coordonnées
     */
    vector<int>& getV1() { return v1; };

    /**
     * @brief Met à jour les coordonnées à partir d'un autre objet Surface.
     * @param s Pointeur vers une autre surface
     */
    void setV1(Surface* s);

    /**
     * @brief Fait défiler la surface vers la gauche.
     * @param vitesse_x Vitesse de déplacement horizontale
     */
    void defiler_surface(int vitesse_x);

};
#endif
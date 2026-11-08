/**
 * @file Joueur.h
 * @brief declaration de la classe Joueur qui gère les propriétés et comportements du joueur dans Geometry Shark
 */

#ifndef _JOUEUR_H
#define _JOUEUR_H
#include <vector>
#include "surface.h"
#include "direction.h"
#include <stdlib.h>

using namespace std;


/**
 * @class Joueur
 * @brief classe représentant le joueur et ses interactions dans le jeu
 */
class Joueur
{
private:
    int direction = 1; /// direction de la gravité (1 = bas, 2 = haut)
    bool est_vivant =true; /// etat de vie du joueur
    vector<int> v1; /// coordonnées du joueur (x1, y1, x2, y2)
    vector<int> v1_initialle; /// coordonnées du joueur (x1, y1, x2, y2)
    int gravite;
    int vitesse_y; ///< vitesse verticale du joueur
    int mode_jeu; /// < Mode de jeu (0 = normal, 1 = vol type Flappy Bird)
public:
    /**
     * @brief constructeur par défaut
     */
    Joueur();

    /**
     * @brief constructeur avec identifiant.
     * @param v1 coordonné de v1
     */
    Joueur(vector<int> v3);

     /**
     * @brief reinitialise le joueur (position, vitesse, direction).
     */
    void initi();
    
    //~Joueur();

    /**
     * @brief verifie si le joueur est posé sur une surface (gravitation vers le bas)
     */
    bool surface_bas(Surface s[], int nbr);

    /**
     * @brief verifie si le joueur est en contact avec une surface au-dessus (gravitation vers le haut)
     */
    bool surface_haut(Surface s[], int nbr); 

    /**
     * @brief detecte un contact latéral avec une surface
     */
    bool surface_cote(Surface s[], int nbr);

    /**
     * @brief fait sauter le joueur vers la direction opposée à la gravité
     * @param y intensité du saut
     */
    void saute(int y);

    /**
     * @brief applique la gravité au joueur
     * @param s tableau des surfaces
     * @param nbr nombre de surfaces
     * @param est_dans_portail indique si le joueur traverse un portail (permet d'éviter certaines collisions)
     */
    void descendre(Surface s[], int nbr,bool est_dans_portail);


    bool touche_obstacle();

    /**
     * @brief renvoie les coordonnées du joueur
     * @return vecteur de 4 entiers
     */
    const vector<int>& getV1() const { return v1; };

    /**
     * @brief inverse la direction de la gravité
     */
    void changedirection();

    /**
     * @brief change le mode de jeu (normal ou vol).
     */
    void changemode();


    /**
     * @brief renvoie la direction actuelle (1 = bas, 2 = haut)
     */
    int getdirection();

    /**
     * @brief renvoie le mode de jeu actuel (0 = normal, 1 = vol)
     */
    int getModeJeu();

    /**
     * @brief renvoie la vitesse verticale du joueur
     */
    const int getvitesse() const { return vitesse_y;};

    /**
     * @brief change la vitesse verticale du joueur
     * @param y nouvelle vitesse
     */
    void setvitesse(int y){vitesse_y = y;};

    /**
     * @brief renvoie l'état de vie du joueur
     * @return true si vivant, false sinon
     */
    bool est_vivantf(){return est_vivant;};

    /**
     * @brief Inverse l'état de vie du joueur.
     */
    void set_est_vivant(){est_vivant = !est_vivant;};
    /**
     * @brief vérification unitaire des méthodes de la classe Joueur. Elle teste les aspects essentiels : position, gravité, direction, saut, changement de mode, etc.
     */

    void testRegression();
};

#endif



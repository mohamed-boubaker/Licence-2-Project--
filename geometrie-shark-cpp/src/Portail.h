/**
 * @file Portail.h
 * @brief Déclaration de la classe Portail pour le jeu Geometry Shark.
 */
#ifndef _PORTAIL_H
#define _PORTAIL_H

#include <vector>
#include <iostream>

using namespace std;

/**
 * @class Portail
 * @brief Représente un portail qui modifie la dynamique du joueur.
 */
class Portail {
private:
    vector<int> v1; // coordonnées du portail (x1, y1, x2, y2)
    bool active; // indique si le portail peut encore être activé
    int mode_portail; // type de portail (0 = inverse gravite, 1 = mode vol, etc.)

public:
    /**
     * @brief Constructeur par défaut.
     */
    Portail();

    /**
     * @brief Constructeur avec coordonnées et mode.
     * @param v2 Vecteur contenant les coordonnées du portail
     * @param mode Mode du portail (0, 1, 2...)
     */
    Portail(vector<int> v2, int mode); 

    /**
     * @brief Accès aux coordonnées du portail.
     * @return Référence constante vers les coordonnées
     */
    const vector<int>& getv1() const { return v1; };

    /**
     * @brief Vérifie si le joueur est en collision avec le portail.
     * @param joueurV1 Coordonnées du joueur
     * @return true si collision
     */
    bool portail(vector<int> joueurV1);

    /**
     * @brief Déplace le portail vers la gauche.
     * @param vitesse_x Vitesse du défilement
     */
    void defiler_portail(int vitesse_x);

    /**
     * @brief Désactive le portail après activation.
     */
    void portailtoucher();

    /**
     * @brief Vérifie si le portail est encore actif.
     * @return true si activable
     */
    bool getportail();

    /**
     * @brief Renvoie le type de portail.
     * @return identifiant du mode de portail
     */
    int getMode() const { return mode_portail; } 
    // bool piece(vector<int> joueurV1);
};

#endif

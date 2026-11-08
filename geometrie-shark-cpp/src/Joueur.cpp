/**
 * @file Joueur.cpp
 * @brief implémentation des méthodes de la classe Joueur
 */
#include <iostream>
#include "Joueur.h"
#include "surface.h"
#include <stdlib.h>
#include <cassert>
using namespace std;



/**
 * @brief Constructeur de base, serra utiliser pour sdl
 */
Joueur::Joueur(){

    ///coordonné joueur
    v1.push_back(30);
    v1.push_back(30);
    v1.push_back(80);
    v1.push_back(80);

    v1_initialle.push_back(30);
    v1_initialle.push_back(30);
    v1_initialle.push_back(80);
    v1_initialle.push_back(80);
    est_vivant = true;
    gravite = 1;
    vitesse_y = 0;
    mode_jeu = 0;
    } 
/**
 * @brief Constructeur de initialiser coordonné joueur
 **/
Joueur::Joueur(vector<int> v3){

    ///coordonné joueur
    v1=v3;
    v1_initialle = v3;
    est_vivant = true;
    gravite = 1;
    vitesse_y = 0;
    mode_jeu = 0;
    } 

    

/**
 * @brief Applique la gravité au joueur et le déplace en conséquence
 * @param s tableau de surfaces
 * @param nbr nombre de surfaces
 * @param est_dans_portail vrai si le joueur est dans un portail (permet d'éviter certaines collisions)
 */
    void Joueur::descendre(Surface s[], int nbr,bool est_dans_portail){    /// Appliquer la gravité en fonction de la direction


        if (direction == 1) {
            // Gravité vers le bas
            if (!surface_bas(s, nbr)) {
                vitesse_y -= gravite;
            }
        } else if (direction == 2) {
            // Gravité vers le haut
            if (!surface_haut(s, nbr)) {

                vitesse_y += gravite;
            }
        }


    for(int i=0;i<abs(vitesse_y);i++){
        if(surface_cote(s,nbr)){
            break;
        }

        if(direction==1 && !(surface_bas(s,nbr))){
            if(surface_haut(s,nbr) && !est_dans_portail){
                break;
            }
            v1[1] += vitesse_y/abs(vitesse_y);
            v1[3] += vitesse_y/abs(vitesse_y);
        } else if (direction == 2 && !(surface_haut(s,nbr))){
            if(surface_bas(s,nbr) && !est_dans_portail){
                break;
            } else {

            v1[1] += vitesse_y/abs(vitesse_y);
            v1[3] += vitesse_y/abs(vitesse_y);
            }
        }


    }

    /// on donne les condition si la personne saute
    
          /// Si le joueur touche le sol (gravité vers le bas)
          if (direction == 1 && surface_bas(s, nbr)) {
               vitesse_y = 0;  /// Réinitialiser la vitesse verticale (le joueur est sous le plafond)

        }
    
        /// Si le joueur touche le plafond (gravité vers le haut)
        if (direction == 2 && surface_haut(s, nbr)) {

                vitesse_y = 0;  /// Réinitialiser la vitesse verticale (le joueur est sous le plafond)
            }
        ///limite la vitesse y    
        if(vitesse_y >= 30) vitesse_y = 20;
        if(vitesse_y <= -30) vitesse_y = -20;


}

        
/**
 * @brief Vérifie si le joueur est posé sur une surface.
 */ 
    bool Joueur::surface_bas(Surface s[], int nbr){
        bool reponse = false;
            for(int i = 0; i < nbr; i++){           
            if (((((s[i].getV1()[0] <= v1[2]) && (s[i].getV1()[2] >= v1[2])) || (s[i].getV1()[0] <= v1[0])) && (s[i].getV1()[2] >= v1[0])) && (s[i].getV1()[3]-v1[1]==0))
            { /// cherche si une surface est en x compris entre 1 et 2 et y en bas du joueur
                reponse = true;
            }
            
        }
        return reponse;
    }

/**
 * @brief Vérifie si le joueur touche une surface par le côté.
 */
bool Joueur::surface_cote(Surface s[], int nbr){
    const int marge = 1; /// marge pour la tolérance de contact
    for (int i = 0; i < nbr; i++) {
        /// meme niveau en y
        bool chevaucheY = !(s[i].getV1()[3] < v1[1] || v1[3] < s[i].getV1()[1]);


        /// Collision côté droit du joueur avec côté gauche de la surface
        bool toucheDroite = abs(v1[2] - s[i].getV1()[0]) <= marge;

        if (chevaucheY && (toucheDroite)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Vérifie si le joueur touche une surface au-dessus.
 */
    bool Joueur::surface_haut(Surface s[], int nbr){
        bool reponse = false;
            for(int i = 0; i < nbr; i++){           
            if (((((s[i].getV1()[2] >= v1[0]) && (s[i].getV1()[0] <= v1[0])) || (s[i].getV1()[2] >= v1[2])) && (s[i].getV1()[0] <= v1[2])) && (s[i].getV1()[1]-v1[3]==0))
            { /// cherche si une surface est en x compris entre 1 et 2 et y en haut du joueur
                reponse = true;
            }
            
        }
        return reponse;
    }
/**
 * @brief Fait sauter le joueur en fonction de la direction.
 * @param y intensité du saut
 */
    void Joueur::saute(int y) {
        if (direction == 1) {
            /// Saut vers le haut (gravité vers le bas)
            vitesse_y = y;  /// Saut vers le haut avec une vitesse initiale négative
        } else if (direction == 2) {
            /// "Saut" vers le bas (gravité inversée)
            vitesse_y = -y;   /// Saut vers le bas avec une vitesse initiale positive
        }

        v1[1] += vitesse_y;
        v1[3] += vitesse_y;
    }

  



/**
 * @brief Inverse la direction de la gravité.
 */  
    void Joueur::changedirection(){
        if(direction == 2){
            direction=1;
        } else {
            direction=2;
        }
    }

/**
 * @brief Change le mode de jeu (normal ou vol).
 */
    void Joueur::changemode(){
        if(mode_jeu==0){
            mode_jeu=1;
        } else {
            mode_jeu=0;
        }
    }


/**
 * @brief Réinitialise les paramètres du joueur.
 */
    void Joueur::initi(){        
        v1=v1_initialle;
        direction=1;
        vitesse_y = 0;
        mode_jeu = 0;
        est_vivant = true;
    }

/**
 * @brief Renvoie la direction actuelle du joueur.
 */
    int Joueur::getdirection(){
        return direction;
    }
/**
 * @brief Renvoie le mode de jeu actuel.
 */
    int Joueur::getModeJeu(){
        return mode_jeu;
    }
    /**
     * @brief vérification unitaire des méthodes de la classe Joueur. Elle teste les aspects essentiels : position, gravité, direction, saut, changement de mode, etc.
     */

    void Joueur::testRegression() {
        cout << "=== Test Joueur ===" << endl;
    
        Joueur j;
    
        /// Test initialisation
        cout << "Test position initiale..." << endl;
        assert(j.getV1()[0] == 30 && j.getV1()[1] == 30);
        assert(j.getdirection() == 1);
        assert(j.getModeJeu() == 0);
        cout << " -> OK" << endl;
    
        /// Test changement de direction
        cout << "Test changement direction..." << endl;
        j.changedirection();
        assert(j.getdirection() == 2);
        j.changedirection();
        assert(j.getdirection() == 1);
        cout << " -> OK" << endl;
    
        /// Test changement de mode
        cout << "Test changement mode..." << endl;
        j.changemode();
        assert(j.getModeJeu() == 1);
        j.changemode();
        assert(j.getModeJeu() == 0);
        cout << " -> OK" << endl;
    
        /// Test saut et gravité
        cout << "Test saut..." << endl;
        int y_init = j.getV1()[1];
        j.saute(10);
        assert(j.getV1()[1] != y_init); // Le joueur doit avoir bougé
        cout << " -> OK" << endl;
    
        /// Test réinitialisation
        cout << "Test réinitialisation..." << endl;
        j.initi();
        assert(j.getV1()[0] == 30 && j.getV1()[1] == 30);
        assert(j.getdirection() == 1);
        assert(j.getModeJeu() == 0);
        cout << " -> OK" << endl;
    
        cout << "Tous les tests Joueur sont passés avec succès." << endl;
    }
    



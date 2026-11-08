/**
 * @file Partie.h
 * @brief Déclaration de la classe Partie qui gère la logique du jeu Geometry Shark.
 */

 #ifndef _PARTIE_H
 #define _PARTIE_H
 #include <vector>
 
 #include "surface.h"
 #include "Joueur.h"
 #include "Obstacle.h"
 #include "Portail.h"
 #include "SautAuto.h"
 #include "SautClick.h"
 #include <cassert>

 #include <fstream>  // Pour ouvrir et lire le fichier
 #include <sstream>  // Pour convertir les données en types spécifiques
 
 
 
 using namespace std;
 
 
 /**
  * @class Partie
  * @brief Classe principale de gestion de la partie.
  */
 
 class Partie
 {
     private:
     int id; // identifant de la partie
     int the_end; // variable pour la fin de la partie
     int the_end__; // 2eme variable de fin 
 
     Joueur j;
 
     Portail* portail_initiales; // tableau de Portails initaux
     Portail* p; // tableau des portails de la partie 
 
     SautAuto* sa_initiales; // tableau de Saut automatique initaux
     SautAuto* sa; // tableau des Saut automatique de la partie
 
     SautClick* sc_initiales; // tableau de Saut clique initaux
     SautClick* sc; // tableau des Saut clique de la partie
 
     Obstacle* o_initiales; // tableau d'Obstacle initaux
     Obstacle* o; // tableau des Obstacles de la partie
 
     Surface* surfaces_initiales; // tableau de Surface initaux
     Surface* s; // tableau des Surfaces de la partie
 
     //int score;
 
     int nb_portail; // nombre de portails dans la partie
     int nb_surface; // nombre de surfaces dans la partie
     int nb_obs; // nombre d'obstacles dans la partie
     int nb_sautauto; // nombre de saut automatique dans la partie
     int nb_sautclick; // nombre de saut clique dans la partie
     
     
     public:
 
     /**
     * @brief accède à la position du joueur
     * @return vecteur représentant les coordonnées du joueur
     */
         const vector<int>& getV1J() const { return j.getV1(); };
         
     // je sais pas
         Partie(const string& filepath);
 
     /**
      * @brief constructeur personnalisé avec initialisation de tous les éléments du jeu
      * @param sur tableau de surfaces
      * @param nb_surface nombre de surfaces positif ou nul
      * @param obs tableau d'obstacles
      * @param nb_obs nombre d'obstacles positif ou nul
      * @param po tableau de portails
      * @param nb_portail nombre de portails positif ou nul
      * @param sa tableau de sauts automatiques
      * @param sc tableau de sauts au clic
      * @param nb_sautauto nombre de sauts automatiques positif ou nul
      * @param nb_sautclick nombre de sauts au clic positif ou nul
      * @param the_end valeur pour la fin de la partie toujours positif
      */
      Partie(Surface* sur,int nb_surface, Obstacle* obs, int nb_obs,Portail* po, int nb_portail,SautAuto* sa, SautClick* sc, int nb_sautauto,int nb_sautclick,int the_end);          
     // destructeur de la partie
         ~Partie();
 
     /**
      * @brief fait défiler tous les éléments vers la gauche
      * @param vitesse_x vitesse de défilement en X
      */
         void defiler_partie(int vitesse_x);
 
     // affiche les éléments de la partie à l'écran
         void afficher();
 
     // met fin a la partie
         void perdu();
 
     // initialise les éléments de la partie.
         void initilisaliser();
 
     /**
      * @brief renvoie le tableau de Surface, Obstacles, Portail ect...
      * @return pointeur vers Surface, Obstacles, Portail ect...
      */
         Surface* getSurface() const;
         Obstacle* getObstacle() const;
         Portail* getPortail() const;
         SautAuto* getsautauto() const;
         SautClick* getsautclick() const;
 
     /**
      * @brief a jouter dans la boucle pour chaque frame du jeu
      */
         void action_automatique();
        /**
      * @brief version txt pour avoir des sauts plus petit
      */    
         void action_automatique_txt();
 
     /**
      * @brief gere les actions du clavier
      * @param touche touche pressee (ex: 'a' pour sauter)
      */
         void action_clavier(const char touche);
         void action_clavier_txt(const char touche);
     

             /**
      * @brief detecte et traite les collisions entre le joueur et les éléments de la partie
      */ 
         void colision();
           /**
      * @brief vu que dans txt des objets se colle sans se toucher, modification pour txt
      */ 

         void colision_txt();
 
     
     /**
      * @brief verifie si le joueur a atteint la fin de la partie
      * @return true si le niveau est gagné
      */
         bool gagner();
 
     /**
      * @brief renvoie la vitesse actuelle du joueur
      * @return vitesse du joueur.
      */
         const int getvitesseee() { return j.getvitesse();};
 
     // renvoie le nombre de surfaces, obstacles,portail ect... dans la partie.
         int getnb_surface() {return nb_surface;};
         int getnb_obstacle() {return nb_obs;};
         int getnb_portail() {return nb_portail;};   
         int getnb_sautauto() {return nb_sautauto;};
         int getnb_sautclick() {return nb_sautclick;};
 
     /**
      * @brief verifie si le joueur a perdu
      * @return true si le joueur est mort
      */
         bool aPerdu(){return !(j.est_vivantf());};
         Joueur getjoueur() const {return j;};
         bool chevauche(const vector<int>& a, const vector<int>& b) const;
         void testRegression()const;
         void modifjoueur(Joueur J1){j = J1;};


 
 };


 #endif
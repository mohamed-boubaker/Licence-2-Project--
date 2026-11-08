/**
 * @file Partie.cpp
 * @brief Implémentation des méthodes de la classe Partie pour le jeu Geometry Shark
 */

#include "Partie.h"
#include <iostream>

using namespace std;
const int MAXSURFACE = 250;

/**
 * @brief constructeur principal de partie où on initialise directe les éléments
 */
Partie::Partie(Surface* sur,int nb_surface,Obstacle* obs,int nb_obs,Portail* po,int nb_portail,SautAuto* saA, SautClick* scA,int nb_sautauto, int nb_sautclick, int the_end_){
  
  the_end=the_end_;
  the_end__=the_end_;
  j = Joueur();
  

/// initialisation des tailles
  this->nb_portail = nb_portail;
  this->nb_surface = nb_surface;
  this->nb_obs = nb_obs;
  this->nb_sautauto = nb_sautauto;
  this->nb_sautclick = nb_sautclick;


/// recherche si nb sont bien nul ou positif
    assert(nb_sautauto>=0); /// vérifie que le nombre soit positif ou nul
    assert(nb_sautclick>=0); /// vérifie que le nombre soit positif ou nul
    assert(nb_obs>=0); /// vérifie que le nombre soit positif ou nul
    assert(nb_surface>=0); /// vérifie que le nombre soit positif ou nul
    assert(nb_portail>=0); /// vérifie que le nombre soit positif ou nul
    assert(the_end>=0); /// vérifie que le nombre soit positif ou nul

/// allocation dynamique des tableaux de jeu
  portail_initiales = new Portail[nb_portail];
  surfaces_initiales = new Surface[nb_surface];
  o_initiales = new Obstacle[nb_obs];
  sa_initiales = new SautAuto[nb_sautauto];
  sc_initiales = new SautClick[nb_sautclick];

  p = new Portail[nb_portail];
  s = new Surface[nb_surface];
  o = new Obstacle[nb_obs];
  sa = new SautAuto[nb_sautauto];
  sc = new SautClick[nb_sautclick];

/// copie des données dans les tableaux
  for(int i = 0; i < nb_surface; i++){
        surfaces_initiales[i] = sur[i];
        s[i] = sur[i];
    }
    for(int i = 0; i < nb_portail; i++){
        portail_initiales[i] = po[i];
        p[i] = po[i];
    }
    for(int i = 0; i < nb_obs; i++){
        o[i] = obs[i];
        o_initiales[i] = obs[i];
    }
    for(int i = 0; i < nb_sautauto; i++){
        sa[i] = saA[i];
        sa_initiales[i] = saA[i];
    }
    for(int i = 0; i < nb_sautclick; i++){
        sc[i] = scA[i];
        sc_initiales[i] = scA[i];
    }


    {
        /// Rassembler tous les vecteurs dans un tableau commun
        vector<vector<int>> objets;
    
        for (int i = 0; i < nb_surface; i++) objets.push_back(s[i].getV1());
        for (int i = 0; i < nb_obs; i++) objets.push_back(o[i].getv1());
        for (int i = 0; i < nb_portail; i++) objets.push_back(p[i].getv1());
        for (int i = 0; i < nb_sautauto; i++) objets.push_back(sa[i].getv1());
        for (int i = 0; i < nb_sautclick; i++) objets.push_back(sc[i].getv1());
        objets.push_back(j.getV1());
    
        for (size_t i = 0; i < objets.size(); ++i) {
            for (size_t j = i + 1; j < objets.size(); ++j) {
                if (chevauche(objets[i], objets[j])) {
                    cerr << "Erreur : Des objets se chevauchent lors de l'initialisation de Partie." << endl;
                    assert(false); 
                }
            }
        }
    }




}


/**
 * @brief constructeur à partir d'un fichier .txt
 */
Partie::Partie(const string& filepath) {
    ifstream file(filepath);  /// Ouvre le fichier
    if (!file.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filepath << endl;
        return;
    }

    string line;
    int nb_surface, nb_obs, nb_portail, the_end_;

    /// Lecture du nombre de surfaces
    file >> line >> nb_surface;
    assert(file); /// vérifie si la lecture a bien marché

    this->nb_surface = nb_surface;
    assert(nb_surface>=0); /// vérifie que le nombre soit positif ou nul

    surfaces_initiales = new Surface[nb_surface];
    s = new Surface[nb_surface];

    /// Lecture des surfaces
    for (int i = 0; i < nb_surface; i++) {
        int x1, y1, x2, y2;
        file >> line >> x1 >> y1 >> x2 >> y2;
        assert(file); /// vérifie si la lecture a bien marché

        vector<int> v = {x1, y1, x2, y2};
        surfaces_initiales[i] = Surface(v);  
        s[i] = surfaces_initiales[i];
    }

    /// Lecture du nombre d'obstacles
    file >> line >> nb_obs;
    assert(file); /// vérifie si la lecture a bien marché
    assert(nb_obs>=0); /// vérifie que le nombre soit positif ou nul


    this->nb_obs = nb_obs;
    o_initiales = new Obstacle[nb_obs];
    o = new Obstacle[nb_obs];

    /// Lecture des obstacles
    for (int i = 0; i < nb_obs; i++) {
        int x1, y1, x2, y2;
        file >> line >> x1 >> y1 >> x2 >> y2;
        assert(file); /// vérifie si la lecture a bien marché

        vector<int> v = {x1, y1, x2, y2};
        o_initiales[i] = Obstacle(v);
        o[i] = o_initiales[i];
    }

    /// Lecture du nombre de portails
    file >> line >> nb_portail;
    assert(file); /// vérifie si la lecture a bien marché
    assert(nb_portail>=0); /// vérifie que le nombre soit positif ou nul


    this->nb_portail = nb_portail;
    portail_initiales = new Portail[nb_portail];
    p = new Portail[nb_portail];



     /// Lecture des portails
     for (int i = 0; i < nb_portail; i++) {
        int x1, y1, x2, y2, mode;
        file >> line >> x1 >> y1 >> x2 >> y2 >> mode;
        assert(file); /// vérifie si la lecture a bien marché
        vector<int> v = {x1, y1, x2, y2};
        portail_initiales[i] = Portail(v,mode);
        p[i] = portail_initiales[i];
    }


    /// Lecture du nombre de sautauto
    file >> line >> nb_sautauto;
    assert(file); /// vérifie si la lecture a bien marché    
    assert(nb_sautauto>=0); /// vérifie que le nombre soit positif ou nul

    this->nb_sautauto = nb_sautauto;
    sa_initiales = new SautAuto[nb_sautauto];
    sa = new SautAuto[nb_sautauto];

    /// Lecture des sautauto
    for (int i = 0; i < nb_sautauto; i++) {
        int x1, y1, x2, y2;
        file >> line >> x1 >> y1 >> x2 >> y2;
        assert(file); /// vérifie si la lecture a bien marché
        
        vector<int> v = {x1, y1, x2, y2};
        sa_initiales[i] = SautAuto(v);
        sa[i] = sa_initiales[i];
    }


        /// Lecture du nombre de sautclick
        file >> line >> nb_sautclick;
        assert(file); /// vérifie si la lecture a bien marché
        assert(nb_sautclick>=0); /// vérifie que le nombre soit positif ou nul

        this->nb_sautclick = nb_sautclick;
        sc_initiales = new SautClick[nb_sautclick];
        sc = new SautClick[nb_sautclick];
    
        /// Lecture des sautclick
        for (int i = 0; i < nb_sautclick; i++) {
            int x1, y1, x2, y2;
            file >> line >> x1 >> y1 >> x2 >> y2;
            assert(file); /// vérifie si la lecture a bien marché
            vector<int> v = {x1, y1, x2, y2};
            sc_initiales[i] = SautClick(v);
            sc[i] = sc_initiales[i];
        }

    // Lecture de la fin du jeu
    file >> line >> the_end_;
    assert(file); /// vérifie si la lecture a bien marché
    assert(the_end_>0); /// vérifie que la fin soit positif
    
    the_end = the_end_;
    the_end__ = the_end_;

    /// Création du joueur
    j = Joueur();

    /// fermeture du fichier
    file.close(); 
    {
        /// Rassembler tous les vecteurs dans un tableau commun
        vector<vector<int>> objets;
    
        for (int i = 0; i < nb_surface; i++) objets.push_back(s[i].getV1());
        for (int i = 0; i < nb_obs; i++) objets.push_back(o[i].getv1());
        for (int i = 0; i < nb_portail; i++) objets.push_back(p[i].getv1());
        for (int i = 0; i < nb_sautauto; i++) objets.push_back(sa[i].getv1());
        for (int i = 0; i < nb_sautclick; i++) objets.push_back(sc[i].getv1());
        objets.push_back(j.getV1());
    
        for (size_t i = 0; i < objets.size(); ++i) {
            for (size_t j = i + 1; j < objets.size(); ++j) {
                if (chevauche(objets[i], objets[j])) {
                    cerr << "Erreur : Des objets se chevauchent lors de l'initialisation de Partie." << endl;
                    assert(false); 
                }
            }
        }
    }



}


/**
 * @brief destructeur de partie pour libère la mémoire allouée dynamiquement
 */
Partie::~Partie(){
    delete[] surfaces_initiales;
    delete[] s;
    delete[] o_initiales;
    delete[] o;
    delete[] p;
    delete[] portail_initiales;
    delete[] sa_initiales;
    delete[] sa;
    delete[] sc_initiales;
    delete[] sc;
}

bool Partie::chevauche(const vector<int>& h1, const vector<int>& h2) const {
    // h1 = {x1, y1, x2, y2}
    if(!(h1[2] <= h2[0] || h1[0] >= h2[2] || h1[3] <= h2[1] || h1[1] >= h2[3])){
        cout << "Chevauchement détecté entre : "
     << h1[0] << "," << h1[1] << "," << h1[2] << "," << h1[3]
     << " ET "
     << h2[0] << "," << h2[1] << "," << h2[2] << "," << h2[3] << endl;
    }
    
    return !(h1[2] <= h2[0] || h1[0] >= h2[2] || h1[3] <= h2[1] || h1[1] >= h2[3]);
}

/**
 * @brief fait défiler tous les objets de la partie vers la gauche.
 * @param vitesse_x vitesse du défilement
 */
void Partie::defiler_partie(int vitesse_x){
for(int i=0;i<nb_surface;i++){
    s[i].defiler_surface(vitesse_x);
}
for(int i=0;i<nb_obs;i++){
    o[i].defiler_obstacle(vitesse_x);
}
for(int i=0;i<nb_portail;i++){
    p[i].defiler_portail(vitesse_x);
}
for(int i=0;i<nb_sautauto;i++){
    sa[i].defiler_sautAuto(vitesse_x);
}
for(int i=0;i<nb_sautclick;i++){
    sc[i].defiler_sautClick(vitesse_x);
}
the_end -=vitesse_x;

}

void Partie::afficher(){


}

/**
 * @brief retourne le tableau de surfaces, obstacles, portails ect...
 * @return pointeur vers les surfaces, obstacles, portails ect...
 */
Surface* Partie::getSurface() const{
    return s;
    }
Obstacle* Partie::getObstacle() const{
    return o;
    }
Portail* Partie::getPortail() const{
    return p;
    }
SautAuto* Partie::getsautauto() const{
    return sa;  
    }
    SautClick* Partie::getsautclick() const{
        return sc;  
    }


/**
 * @brief execute les actions automatiques de la partie : affichage, défilement, chute du joueur
 */
void Partie::action_automatique(){
    afficher();
    defiler_partie(3); /// vitesse x modifiable
    
    bool est_dans_portail = false;
    j.descendre(s,nb_surface,est_dans_portail);
   
}
void Partie::action_automatique_txt(){
    afficher();
    defiler_partie(1); /// vitesse x modifiable
    
    bool est_dans_portail = false;
    j.descendre(s,nb_surface,est_dans_portail);
   
}

/**
 * @brief marque la partie comme perdue en declarant le joueur mort
 */
void Partie::perdu(){

    j.set_est_vivant();
     
}


/**
 * @brief reinitialise tous les éléments du jeu aux états initiaux.
 */
void Partie::initilisaliser(){
   for (int i = 0; i < nb_surface; i++) {
       s[i] = surfaces_initiales[i]; /// copie simple
   }
   for (int i = 0; i < nb_obs; i++) {
       o[i] = o_initiales[i]; /// copie simple
   }
   for (int i = 0; i < nb_portail; i++) {
       p[i] = portail_initiales[i]; /// copie simple
   }

   for (int i = 0; i < nb_sautauto; i++) {
       sa[i] = sa_initiales[i]; /// copie simple
   }
   for (int i = 0; i < nb_sautclick; i++) {
        sc[i] = sc_initiales[i]; /// copie simple
    }
   
   j.initi();
   the_end=the_end__;
     
}


/**
 * @brief gere les actions clavier
 * @param touche caractère pressé
 */
void Partie::action_clavier(const char touche){

    
    for(int i =0;i<nb_sautclick;i++){
        if(j.getV1()[2] > sc[i].getv1()[0] && j.getV1()[0] < sc[i].getv1()[2] && j.getV1()[3] > sc[i].getv1()[1] && j.getV1()[1] < sc[i].getv1()[3] && touche=='a'){
            j.saute(15); /// si joueur appuie a et qu'il touche saut_click
            break;
        }
    }


    // Utilisation de j.getModeJeu() pour accéder à mode_jeu depuis l'objet Joueur.
    if(j.getModeJeu() == 0){
        if(touche == 'a' && j.surface_bas(s, nb_surface) && j.getdirection() == 1){
            j.saute(20); /// si joueur touche a sans qu'il soit en saut
        }
        if(touche == 'a' && j.surface_haut(s, nb_surface) && j.getdirection() == 2){
            j.saute(20); /// si joueur touche a sans qu'il soit en saut
        }
    } else { // Si mode_jeu != 0
        if(touche == 'a'){
            j.saute(10); ///si on a saut sans condition
        }
    }
}
void Partie::action_clavier_txt(const char touche){

    
    for(int i =0;i<nb_sautclick;i++){
        if(j.getV1()[2] > sc[i].getv1()[0] && j.getV1()[0] < sc[i].getv1()[2] && j.getV1()[3] > sc[i].getv1()[1] && j.getV1()[1] < sc[i].getv1()[3] && touche=='a'){
            j.saute(1); /// si joueur appuie a et qu'il touche saut_click
            break;
        }
    }


    // Utilisation de j.getModeJeu() pour accéder à mode_jeu depuis l'objet Joueur.
    if(j.getModeJeu() == 0){
        if(touche == 'a' && j.surface_bas(s, nb_surface) && j.getdirection() == 1){
            j.saute(2); /// si joueur touche a sans qu'il soit en saut
        }
        if(touche == 'a' && j.surface_haut(s, nb_surface) && j.getdirection() == 2){
            j.saute(2); /// si joueur touche a sans qu'il soit en saut
        }
    } else { // Si mode_jeu != 0
        if(touche == 'a'){
            j.saute(1); ///si on a saut sans condition
        }
    }
}




/**
 * @brief gere toutes les collisions du joueur avec les éléments de la partie
 */

void Partie::colision(){

    bool est_dans_portail = false;

    for(int i = 0; i < nb_portail; i++) {
            if((p[i].getMode() == 0) && (j.getV1()[2] >= p[i].getv1()[2] && j.getV1()[0] <= p[i].getv1()[2] && j.getV1()[1] >= p[i].getv1()[1] && j.getV1()[3] <= p[i].getv1()[3] && p[i].getportail())){
                j.changedirection(); /// change direction si joueur touche portail
                j.setvitesse(0);  /// vitesse y à 0 pour pas avoir de probleme de colision
                p[i].portailtoucher(); /// portail se désactive
                est_dans_portail = true; ///invisible pendant une courte période
                j.descendre(s,nb_surface,true); ///un descendre pour pas avec de colision avec surface

            }
            else if((p[i].getMode() == 1) && (j.getV1()[2] >= p[i].getv1()[2] && j.getV1()[0] <= p[i].getv1()[2] && j.getV1()[1] >= p[i].getv1()[1] && j.getV1()[3] <= p[i].getv1()[3] && p[i].getportail())){
                j.changemode();
                j.setvitesse(0);
                p[i].portailtoucher();
                est_dans_portail = true;
                j.descendre(s,nb_surface,true); ///descendre pour pas avec de colision avec surface
                
            }
        
    }


    
    for(int i =0;i<nb_obs;i++){
        if(j.getV1()[2] > o[i].getv1()[0] && j.getV1()[0] < o[i].getv1()[2] && j.getV1()[3] > o[i].getv1()[1] && j.getV1()[1] < o[i].getv1()[3]){
            perdu(); ///si joueur touche obstacle alors perdu
            break;
        }
    }



    /// si le joueur touche SautAuto il fait un sautauto
    for(int i =0;i<nb_sautauto;i++){
        if(j.getV1()[2] > sa[i].getv1()[0] && j.getV1()[0] < sa[i].getv1()[2] && j.getV1()[3] > sa[i].getv1()[1] && j.getV1()[1] < sa[i].getv1()[3]){
            j.saute(25); /// saut automatique si joueur touche plateforme saut automatique
            break;
        }
    }
    

    

    if(!est_dans_portail){
    for(int i=0;i<nb_surface;i++){
        if((j.surface_haut(s,nb_surface) && (j.getdirection()==1)) || (j.surface_bas(s,nb_surface) && (j.getdirection()==2))){
            perdu(); ///si joueur touche haut avec gravité noral  ou vas avec gravité inversé alors il perd
            break;
        }
        if(j.surface_cote(s,nb_surface)){
            perdu(); /// si le cote droit d'une surface toucher alors perdu
            break;
        }
    
        if(j.getV1()[1] < 0 || j.getV1()[3] > 600){
            perdu(); /// si joueur sort du cadre du jeu
            break;
        }
    }
}

}

void Partie::colision_txt(){


    for (int i = 0; i < nb_portail; i++) {
        if (j.getV1()[2] >= p[i].getv1()[2] && j.getV1()[0] <= p[i].getv1()[2] && j.getV1()[1] >= p[i].getv1()[1] && j.getV1()[3] <= p[i].getv1()[3] && p[i].getportail()) {

    
            // Change la direction du joueur
            j.changedirection();
            j.descendre(s,nb_surface,true);
            p[i].portailtoucher(); /// portail se désactive

    
            // Optionnel : sortir de la boucle pour éviter conflit
            break;
        }
    }


    for(int i =0;i<nb_obs;i++){
        if(j.getV1()[2] > o[i].getv1()[0] && j.getV1()[0] < o[i].getv1()[2] && j.getV1()[3] > o[i].getv1()[1] && j.getV1()[1] < o[i].getv1()[3]){
            perdu();
            break;
        }
    }

    for(int i=0;i<nb_surface;i++){
        if(s[i].getV1()[0]<=j.getV1()[0] && s[i].getV1()[2]>=j.getV1()[2] && s[i].getV1()[1]<=j.getV1()[1] && s[i].getV1()[3]>=j.getV1()[3]){
            perdu();
            break;
    
        }
    }
}


/**
 * @brief verifie si le joueur a atteint la fin du niveau
 * @return true si la victoire est atteinte
 */
bool Partie::gagner(){
    if(j.getV1()[0]>= the_end){
        return true;

    }
    return false;
}


/**
 * @brief Il vérifiera que les valeurs et comportements de base restent stables, comme l'initialisation correcte, le défilement, la réinitialisation, et que le joueur ne gagne pas immédiatement ni ne perd dès le début sans raison.
 */
void Partie::testRegression()const {

        cout << "Début des tests de régression pour Partie..." << endl;
    
        /// Création d’objets pour test
        Surface surfaces[] = { Surface({0, 500, 100, 520}) };
        Obstacle obstacles[] = { Obstacle({150, 480, 170, 520}) };
        Portail portails[] = { Portail({200, 480, 220, 520}, 0) };
        SautAuto sautauto[] = { SautAuto({250, 480, 270, 520}) };
        SautClick sautclick[] = { SautClick({300, 480, 320, 520}) };
    
        int nb_surface = 1, nb_obs = 1, nb_portail = 1, nb_sautauto = 1, nb_sautclick = 1, the_end = 1000;
    
        Partie partie(surfaces, nb_surface, obstacles, nb_obs, portails, nb_portail,
                      sautauto, sautclick, nb_sautauto, nb_sautclick, the_end);
    
        /// Test: Vérification des dimensions de début
        assert(partie.getSurface()[0].getV1()[0] == 0);
        assert(partie.getObstacle()[0].getv1()[0] == 150);
        assert(partie.getPortail()[0].getv1()[0] == 200);
        assert(partie.getsautauto()[0].getv1()[0] == 250);
        assert(partie.getsautclick()[0].getv1()[0] == 300);
    
        /// Sauvegarde de position initiale du joueur
        int pos_initiale = partie.getSurface()[0].getV1()[0];
    
        /// Test: defilement
        partie.defiler_partie(10);
        assert(partie.getSurface()[0].getV1()[0] == pos_initiale - 10);
    
        /// Test: initilisaliser()
        partie.initilisaliser();
        assert(partie.getSurface()[0].getV1()[0] == 0);  // Revenu à la position d'origine
    
        /// Test: le joueur n’a pas encore gagné
        assert(partie.gagner() == false);
    
        /// Test: le joueur n’a pas perdu (vivant au départ)
        partie.colision(); // pas censé perdre ici
    
        cout << "Tous les tests de régression pour Partie sont passés avec succès." << endl;
    }
    
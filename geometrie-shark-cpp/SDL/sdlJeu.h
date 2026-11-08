#ifndef SDLJEU_H
#define SDLJEU_H
#include "Partie.h"
#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


using namespace std;

class SDLJeu 
{
private:
    bool victoire = false;
    Uint32 tempsVictoire = 0;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
    Partie* partie;
    Joueur j;
    
    Mix_Music* musique = nullptr;
    Mix_Music* musiqueMort = nullptr;
    bool musiqueMortJouee = false;
    bool audio = false;
    // Déclare une variable pour l'opacité du joueur
    Uint8 alphaJoueur = 255;  // Opacité initiale (255 = complètement opaque)
    SDL_Rect joueurRect;
    SDL_Rect backRect;
    SDL_Rect picRect;
    SDL_Rect portailRect;

    SDL_Rect sautAutoRect;
    SDL_Rect sautClickRect;




    SDL_Rect joueur;
    vector<SDL_Rect> obstacles;

    SDL_Texture* textureJoueur; 
    SDL_Texture* textureJoueurvole;
    SDL_Texture* texturePic;
    SDL_Texture* textureBack;
    SDL_Texture* texturePortail;

    SDL_Texture* textureSautauto;
    SDL_Texture* textureSautclick;

    SDL_Texture* retourTexture;
    SDL_Rect retourBtn;

    int vitesse;
    int gravite;
    int vitesseSaut;
    bool enSaut;

public:

/**
 * @brief constructeur de base
 */
     SDLJeu(Partie& partie,SDL_Window* win, SDL_Renderer* rend);
 /**
 * @brief constructeur avec l'ajout de musique
 */    
     SDLJeu(Partie &partie,SDL_Window* win, SDL_Renderer* rend, const string& cheminMusique);  // Avec musique
/**
 * @brief destructeur
 */
    ~SDLJeu();
 /**
 * @brief boucle 
 */
   
    void sdlBoucle();
 /**
 * @brief changement prochain frame
 */   
    void sdlAff();
    /**
 * @brief si joueur quitte ou appuie sur a
 */
    void gererEvenements();
    /**
 * @brief changement si joueur perd ou gagne
 */
    void update();
 /**
 * @brief lance musique jeu de base
 */   
    void jouerMusiqueJeu();




};

#endif

#ifndef SDLMENU_H
#define SDLMENU_H

#include "sdlJeu.h"
#include <vector>

class SDLMenu {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Texture* boutonTextures[3]; /// bouton pour acceder niveau
    Mix_Music* musiqueMenu = nullptr;
    Partie** parties; /// tableau de partie
    int nbJeux;
    int jeuSelectionne = 0;

public:
/**
 * @brief constructeur de base
 */
    SDLMenu(Partie** lesJeux,int nbp);
/**
 * @brief destructeur
 */
    ~SDLMenu();


    /**
 * @brief si personne à choisis un niveau alors lancer le jeu en fonction de l'index qu'il a indiqué
 */
    void lancerJeu(int index);
    /**
 * @brief affiche la page de menu 
 */
    int afficherMenu(); /// -1: menu 0: niveau 1, 1: niveau 2, 2: niveau 3 
};

#endif

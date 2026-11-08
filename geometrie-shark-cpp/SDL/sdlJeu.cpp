#include "sdlJeu.h"
#include "Partie.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>
const int DIMY = 600; /// on utilise cette variable pour faire -600 à y dans le rendu 

using namespace std;

/**
 * @brief constructeur de base
 */
SDLJeu::SDLJeu(Partie& partie,SDL_Window* win, SDL_Renderer* rend)
    : window(win), renderer(rend) {

    this->partie = &partie;


    retourBtn = {10, 10, 50, 50}; /// Position et taille du bouton retour

    SDL_Surface* surface = IMG_Load("data/image/retour.png");
    if (!surface) {
        std::cerr << "Erreur chargement image retour : " << IMG_GetError() << std::endl;
    } else {
        retourTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

/// si texte marche pas
    if (TTF_Init() < 0) {
        cerr << "Erreur TTF_Init : " << TTF_GetError() << endl;
    }
///texture joueur
    SDL_Surface* joueurSurf = IMG_Load("data/image/joueur.png");  // image joueur 
    if (!joueurSurf) cerr << "Erreur IMG_Load: " << IMG_GetError() << endl;
    textureJoueur = SDL_CreateTextureFromSurface(renderer, joueurSurf);
    SDL_FreeSurface(joueurSurf);
///texture joueur vole
    SDL_Surface* joueurvoleSurf = IMG_Load("data/image/joueurvole.png");  // image joueur 
    if (!joueurvoleSurf) cerr << "Erreur IMG_Load: " << IMG_GetError() << endl;
    textureJoueurvole = SDL_CreateTextureFromSurface(renderer, joueurvoleSurf);
    SDL_FreeSurface(joueurvoleSurf);   

///texture background 

    SDL_Surface* backSurf = IMG_Load("data/image/background.jpg");  // image back
    if (!backSurf) cerr << "Erreur IMG_Load: " << IMG_GetError() << endl;
    textureBack = SDL_CreateTextureFromSurface(renderer, backSurf);
    SDL_FreeSurface(backSurf);
///texture obstacle
    SDL_Surface* pickSurf = IMG_Load("data/image/pic.png");  // image pic
    if (!pickSurf) cerr << "Erreur IMG_Load: " << IMG_GetError() << endl;
    texturePic = SDL_CreateTextureFromSurface(renderer, pickSurf);
    SDL_FreeSurface(pickSurf);

///texture portail

    SDL_Surface* portailSurf = IMG_Load("data/image/portail.png");  // image portail
    if (!portailSurf) cerr << "Erreur IMG_Load: " << IMG_GetError() << endl;
    texturePortail = SDL_CreateTextureFromSurface(renderer, portailSurf);
    SDL_FreeSurface(portailSurf);

///texture saut_auto    
    SDL_Surface* sautautoSurf = IMG_Load("data/image/sautauto.png");  // image sautauto
    if (!sautautoSurf) cerr << "Erreur IMG_Load: " << IMG_GetError() << endl;
    textureSautauto = SDL_CreateTextureFromSurface(renderer, sautautoSurf);
    SDL_FreeSurface(sautautoSurf);
///texture saut_click

    SDL_Surface* sautclickSurf = IMG_Load("data/image/sautclick.png");  // image sautclick
    if (!sautclickSurf) cerr << "Erreur IMG_Load: " << IMG_GetError() << endl;
    textureSautclick = SDL_CreateTextureFromSurface(renderer, sautclickSurf);
    SDL_FreeSurface(sautclickSurf);
    

    running = true;
}

/**
 * @brief constructeur avec l'ajout de musique
 */


SDLJeu::SDLJeu(Partie &partie, SDL_Window* win, SDL_Renderer* rend, const string& cheminMusique)
    : SDLJeu(partie, win, rend) // Appelle le constructeur de base pour éviter la redondance
{
    audio = true;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) < 0) {
        cerr << "Erreur Mix_OpenAudio: " << Mix_GetError() << endl;
    }

    musique = Mix_LoadMUS(cheminMusique.c_str());
    if (!musique) {
        cerr << "Erreur Mix_LoadMUS: " << Mix_GetError() << endl;
    } 
    // Musique de la partie terminée
    musiqueMort = Mix_LoadMUS("data/musique/gameover.mp3");
    if (!musiqueMort) {
        cerr << "Erreur chargement musique mort : " << Mix_GetError() << endl;
    }

    // Lance immédiatement la musique principale dès l'initialisation
    jouerMusiqueJeu();
}

/**
 * @brief lance musique jeu de base
 */
void SDLJeu::jouerMusiqueJeu() {
    if (musique) {
        Mix_HaltMusic(); // au cas où une autre musique est en cours
        Mix_PlayMusic(musique, -1); // on lance la vraie musique de jeu
    }
}

/**
 * @brief destructeur
 */

SDLJeu::~SDLJeu()
{
    TTF_Quit(); /// destructeur text

    if (musique) {
        Mix_HaltMusic();       /// Stopper proprement la musique
        Mix_FreeMusic(musique); /// destructeur musique
    }

    if (musiqueMort) {
        Mix_FreeMusic(musiqueMort);
    }

    Mix_CloseAudio(); // Fermer le système audio
    IMG_Quit();
    SDL_Quit();
}

/**
 * @brief boucle 
 */

void SDLJeu::sdlBoucle()
{
    while (running)
    {
        gererEvenements();  /// Gestion des événements
        update();  /// Mise à jour de l'état du jeu
        sdlAff();  /// Affichage du jeu

        SDL_Delay(18);  /// Pause pour obtenir un taux de rafraîchissement stable
    }
}


/**
 * @brief changement prochain frame
 */
void SDLJeu::sdlAff()
{


    /// Affiche le joueur avec la texture au lieu d’un rectangle blanc
    backRect.x = 0;
    backRect.y = 0;
    backRect.w = 900;
    backRect.h = DIMY;

    SDL_RenderCopy(renderer, textureBack, NULL, &backRect);



    /// Met à jour la position du joueur 
    int x = partie->getV1J()[0];
    int y = partie->getV1J()[3];
    joueurRect.x = x;
    joueurRect.y = DIMY - y;
    joueurRect.w = 50;
    joueurRect.h = 50;
    SDL_SetTextureAlphaMod(textureJoueur, alphaJoueur);
    /// Affiche le joueur avec la texture au lieu d’un rectangle blanc
    if(partie->getjoueur().getModeJeu()==0){
    SDL_RenderCopy(renderer, textureJoueur, NULL, &joueurRect);
    } else {
    SDL_RenderCopy(renderer,textureJoueurvole, NULL, &joueurRect);
    }


      
    /// Affichage des obstacles
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < partie->getnb_obstacle(); i++)
    {
        SDL_Rect obsRect;
        obsRect.x = partie->getObstacle()[i].getv1()[0];  /// Échelle de la position, ajuster pour correspondre à la logique sdl
        obsRect.y = DIMY-partie->getObstacle()[i].getv1()[3];  /// Idem pour Y
        obsRect.w = partie->getObstacle()[i].getv1()[2]-partie->getObstacle()[i].getv1()[0];      /// Largeur du joueur
        obsRect.h = (partie->getObstacle()[i].getv1()[3]-partie->getObstacle()[i].getv1()[1]);      
        SDL_RenderCopy(renderer, texturePic, NULL, &obsRect);    }


///pour les sautauto


SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < partie->getnb_sautauto(); i++)
    {
        SDL_Rect sautAutoRect;
        sautAutoRect.x = partie->getsautauto()[i].getv1()[0];  // Échelle de la position, ajuster pour correspondre à la logique sdl
        sautAutoRect.y = DIMY-partie->getsautauto()[i].getv1()[3];  /// Idem pour Y
        sautAutoRect.w = partie->getsautauto()[i].getv1()[2]-partie->getsautauto()[i].getv1()[0];      /// Largeur du joueur
        sautAutoRect.h = (partie->getsautauto()[i].getv1()[3]-partie->getsautauto()[i].getv1()[1]);      
        SDL_RenderCopy(renderer, textureSautauto, NULL, &sautAutoRect);    
    }

///fin sautauto


///pour les sautclick


SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < partie->getnb_sautclick(); i++)
    {
        SDL_Rect sautClickRect;
        sautClickRect.x = partie->getsautclick()[i].getv1()[0];  /// Échelle de la position, ajuster pour correspondre à la logique sdl
        sautClickRect.y = DIMY-partie->getsautclick()[i].getv1()[3];  /// Idem pour Y
        sautClickRect.w = partie->getsautclick()[i].getv1()[2]-partie->getsautclick()[i].getv1()[0];      /// Largeur du joueur
        sautClickRect.h = (partie->getsautclick()[i].getv1()[3]-partie->getsautclick()[i].getv1()[1]);      
        SDL_RenderCopy(renderer, textureSautclick, NULL, &sautClickRect);    
    }

///fin sautclick
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < partie->getnb_surface(); i++)
    {
        SDL_Rect surfaceRect;
        surfaceRect.x = partie->getSurface()[i].getV1()[0];  /// Échelle de la position, ajuster pour correspondre à la logique sdl
        surfaceRect.y = DIMY-partie->getSurface()[i].getV1()[3];  /// Idem pour Y
        surfaceRect.w = partie->getSurface()[i].getV1()[2]-partie->getSurface()[i].getV1()[0];      /// Largeur du joueur
        surfaceRect.h = (partie->getSurface()[i].getV1()[3]-partie->getSurface()[i].getV1()[1]);      
        SDL_RenderFillRect(renderer, &surfaceRect);  /// Dessiner chaque obstacle
    }


    SDL_SetRenderDrawColor(renderer, 0, 255, 100, 255);
    for (int i = 0; i < partie->getnb_portail(); i++)
    {
        SDL_Rect portailRect;
        portailRect.x = partie->getPortail()[i].getv1()[0];  /// Échelle de la position, ajuster pour correspondre à la logique sdl
        portailRect.y = DIMY-partie->getPortail()[i].getv1()[3];  /// Idem pour Y
        portailRect.w = partie->getPortail()[i].getv1()[2]-partie->getPortail()[i].getv1()[0];      /// Largeur du joueur
        portailRect.h = (partie->getPortail()[i].getv1()[3]-partie->getPortail()[i].getv1()[1]);      
        SDL_RenderCopy(renderer, texturePortail, NULL, &portailRect);    }

        if (retourTexture) {
            SDL_RenderCopy(renderer, retourTexture, NULL, &retourBtn);
        }    

        if (victoire) {
            /// si victoire afficher "tu as gagne !"
            SDL_Color couleurBlanche = {255, 255, 255, 255}; 
            TTF_Font* font = TTF_OpenFont("data/arial.ttf", 48);
            if (font) {
                SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Tu as gagne !", couleurBlanche);
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_Rect textRect = {300, 250, textSurface->w, textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
                TTF_CloseFont(font);
            } else {
                cerr << "Erreur chargement police : " << TTF_GetError() << endl;
            }
        }    
     
    SDL_RenderPresent(renderer);  /// Mettre à jour l'écran

}

/**
 * @brief si joueur quitte ou appuie sur a
 */

void SDLJeu::gererEvenements()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            
                partie->initilisaliser(); /// si il quitte ça initialise
            
            running = false;  /// Arrêter la boucle si l'utilisateur ferme la fenêtre
 
        }
        else if (event.type == SDL_KEYDOWN)
        {
            /// Si la touche 'a' est pressée, on appelle action_clavier avec 'a' comme paramètre
            if (event.key.keysym.sym == SDLK_a && musiqueMortJouee==false && !victoire)
            {
                partie->action_clavier('a');  // Appeler action_clavier avec 'a' comme argument
    
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                
                
            int x = event.button.x;
            int y = event.button.y;
            if (x >= retourBtn.x && x <= retourBtn.x + retourBtn.w &&
                y >= retourBtn.y && y <= retourBtn.y + retourBtn.h) {
                /// Quitter la boucle du jeu si joueur appuie sur le bouton quitter
                partie->initilisaliser(); /// si il quitte ça initialise
                running = false;
            }
        }
    }
}
/**
 * @brief changement si joueur perd ou gagne
 */


void SDLJeu::update()
{
    if (victoire) {
        if (SDL_GetTicks() - tempsVictoire >= 5000) {
            partie->initilisaliser();

            running = false; /// Revenir au menu après 5 sec
        }
        return;
    }

    if (partie->gagner()) {
        victoire = true;
        tempsVictoire = SDL_GetTicks();
        Mix_HaltMusic(); /// Stoppe la musique si tu veux
        return;
    }

    if (partie->aPerdu()) {
        ///si perdu alors mettre musique de mort et bloquer tout le jeu
        if (audio && !musiqueMortJouee) {
            Mix_HaltMusic();                      
            Mix_PlayMusic(musiqueMort, 1);        
            musiqueMortJouee = true;
        }
        /// animation joueur qui disparait
        if (alphaJoueur > 5 ) {
            alphaJoueur -= 5;  
        }
        /// quand musique mort terminé la partie recommance
        if (musiqueMortJouee && !Mix_PlayingMusic()) {
            partie->initilisaliser();  
            alphaJoueur = 255;         
            musiqueMortJouee = false;  
            Mix_PlayMusic(musique, -1); 
        }
    } else {
        if (musiqueMortJouee && audio && !Mix_PlayingMusic()) {
            Mix_PlayMusic(musique, -1);  
            partie->initilisaliser();    
            musiqueMortJouee = false;   
            alphaJoueur = 255;          
        }
    }

    if (!musiqueMortJouee && !victoire) {
        partie->action_automatique();
        partie->colision();
    }

}

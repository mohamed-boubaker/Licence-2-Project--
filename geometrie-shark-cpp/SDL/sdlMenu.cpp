#include "sdlMenu.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

using namespace std;

SDLMenu::SDLMenu(Partie** lesJeuxx, int nbp) :
    window(nullptr),
    renderer(nullptr),
    backgroundTexture(nullptr),
    musiqueMenu(nullptr),
    parties(lesJeuxx),
    nbJeux(nbp)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cerr << "Erreur SDL_Init : " << SDL_GetError() << endl;
    }

    window = SDL_CreateWindow("Geometry Shark", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Erreur Mix_OpenAudio : " << Mix_GetError() << endl;
    }

    musiqueMenu = Mix_LoadMUS("data/musique/menu.mp3");
    if (!musiqueMenu) {
        cerr << "Erreur chargement musique menu : " << Mix_GetError() << endl;
    }

    SDL_Surface* bg = IMG_Load("data/image/menu_background.png");
    if (!bg) cerr << "Erreur chargement fond : " << IMG_GetError() << endl;
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);
}

SDLMenu::~SDLMenu() {
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (musiqueMenu) Mix_FreeMusic(musiqueMenu);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    Mix_CloseAudio();
    SDL_Quit();
}

int SDLMenu::afficherMenu() {
    bool terminer = false;
    int selection = -1;

    if (musiqueMenu) {
        Mix_HaltMusic();
        Mix_PlayMusic(musiqueMenu, -1);
    }

    SDL_Rect* boutons = new SDL_Rect[nbJeux];
    SDL_Texture** textures = new SDL_Texture*[nbJeux];
    for (int i = 0; i < nbJeux; ++i) textures[i] = nullptr;

    const int largeur = 420, hauteur = 80, espacement = 35;

    for (int i = 0; i < nbJeux; ++i) {
        boutons[i] = {180, 230 + i * (hauteur + espacement), largeur, hauteur};
        std::string chemin = "data/image/level" + std::to_string(i + 1) + ".png";
        SDL_Surface* surf = IMG_Load(chemin.c_str());
        if (!surf) cerr << "Erreur chargement bouton : " << chemin << ": " << IMG_GetError() << endl;
        else {
            textures[i] = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
        }
    }

    SDL_Event event;
    while (!terminer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                terminer = true;
                selection = -1;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                for (int i = 0; i < nbJeux; ++i) {
                    if (x >= boutons[i].x && x <= boutons[i].x + boutons[i].w &&
                        y >= boutons[i].y && y <= boutons[i].y + boutons[i].h) {
                        selection = i;
                        terminer = true;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        if (backgroundTexture) {
            SDL_Rect bgRect = {0, 0, 800, 600};
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect);
        }

        for (int i = 0; i < nbJeux; ++i) {
            if (textures[i]) SDL_RenderCopy(renderer, textures[i], NULL, &boutons[i]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    for (int i = 0; i < nbJeux; ++i)
        if (textures[i]) SDL_DestroyTexture(textures[i]);

    delete[] boutons;
    delete[] textures;

    Mix_HaltMusic();

    return selection;
}

void SDLMenu::lancerJeu(int index) {
    if (musiqueMenu) Mix_HaltMusic();

    std::string musiqueJeu;
    switch(index) {
        case 0: musiqueJeu = "data/musique/music1.mp3"; break;
        case 1: musiqueJeu = "data/musique/Space_Pirates.mp3"; break;
        case 2: musiqueJeu = "data/musique/Press_Start.mp3"; break;
        default: musiqueJeu = "data/musique/music1.mp3"; break;
    }

    SDLJeu jeu(*parties[index], window, renderer, musiqueJeu.c_str());
    jeu.sdlBoucle();

    if (musiqueMenu) Mix_PlayMusic(musiqueMenu, -1);

    int newIndex = afficherMenu();
    if (newIndex >= 0) lancerJeu(newIndex);
}

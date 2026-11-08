#include "sdlMenu.h"
#include "Partie.h"
#include <string>

int main(int argc, char* argv[]) {
    Partie* lesParties[3];
    lesParties[0] = new Partie("data/niveau/partie1.txt");
    lesParties[1] = new Partie("data/niveau/partie2.txt");
    lesParties[2] = new Partie("data/niveau/partie3.txt");

    SDLMenu menu(lesParties, 3);
    int index = menu.afficherMenu();

    if (index >= 0) {
        menu.lancerJeu(index);
    }

    // Nettoyage global
    for (int i = 0; i < 3; ++i) delete lesParties[i];
    SDL_Quit(); // Maintenant on peut quitter proprement SDL

    
    return 0;
}


# Géométrie Shark — Jeu de plateforme C++ / SDL2

**Projet universitaire de Licence 2 Informatique — réalisé en équipe.**

Jeu 2D dont l'objectif est de survivre le plus longtemps possible en franchissant des obstacles, en sautant et en utilisant les portails qui modifient certaines règles du jeu.

## Fonctionnalités
- Contrôle d'un personnage avec mécanismes de saut.
- Gestion d'obstacles, de collisions, de portails et de niveaux.
- Menu et affichage graphique avec **SDL2**.
- Version texte présente dans le projet.

## Technologies
**C++11**, **SDL2**, SDL2_image, SDL2_mixer, SDL2_ttf, Make et programmation orientée objet.

## Structure
- `src/` : logique de jeu.
- `SDL/` : interface graphique.
- `txt/` : version console.
- `data/niveau/` : données des niveaux.
- `Makefile` : compilation.

## Compilation et lancement
Sous une distribution Linux disposant de `g++`, `make`, `sdl2-config` et des bibliothèques de développement SDL2 (`SDL2_image`, `SDL2_mixer`, `SDL2_ttf`) :
```bash
make
./bin/game_sdl
```
Pour la version texte : `./bin/game_txt`.

**Important :** les musiques et certains fichiers multimédias de l'archive de départ ont été retirés de cette version afin de ne pas redistribuer de médias dont les droits n'ont pas été vérifiés. Le jeu graphique peut donc demander des médias supplémentaires et son fonctionnement complet n'a pas été vérifié ici. Les fichiers graphiques restants sont également à vérifier avant publication publique.

## Travail en équipe
Projet développé avec d'autres étudiants. Ajouter, si possible, une phrase indiquant précisément les classes ou fonctionnalités réalisées personnellement.

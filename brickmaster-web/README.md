# BrickMaster — Application web avec grille et statistiques

**Projet universitaire en informatique — application web et base de données.**

BrickMaster est un projet autour de pièces de construction sur une grille. L'interface présente des statistiques liées aux joueurs et aux pièces, une sélection de pièces et une grille visualisable ou initialisée aléatoirement.

## Fonctionnalités visibles dans le projet
- Interface web avec affichage d'une grille et de pièces.
- Sélection de pièces et pages de consultation.
- Affichage de statistiques sur les données du projet.
- Base **PostgreSQL** et requêtes SQL.

## Technologies
**Python**, **HTML/CSS**, **SQL/PostgreSQL**, templates Jinja et serveur pédagogique BDW.

## Structure
- `site/controleurs/` : logique des pages.
- `site/model/` : fonctions d'accès à la base PostgreSQL.
- `site/templates/` : vues HTML.
- `site/static/` : styles et images.
- `site/bd-projet.sql` : schéma et données du projet.

## Lancement
Le code repose sur le serveur pédagogique **bdw-server** utilisé pendant le cours. Il **ne s'agit pas d'une application web autonome**.

1. Préparer une base PostgreSQL de test et examiner `site/bd-projet.sql` **avant exécution** : il contient des instructions pouvant supprimer et recréer un schéma de base.
2. Récupérer le serveur de cours `bdw-server` auprès de l'enseignement.
3. Placer `site/` dans son répertoire `websites/` et le renommer `serial_critique` si nécessaire.
4. Renseigner les identifiants de base de données dans une configuration locale **hors GitHub**.
5. Lancer le serveur depuis son dossier :
```bash
python server.py serial_critique
```

## Confidentialité et crédits
Les configurations personnelles et environnements virtuels ont été exclus. Certaines ressources pédagogiques et images peuvent provenir du matériel de cours ; vérifier l'autorisation de publication. Préciser les contributions individuelles si le projet a été réalisé en équipe.

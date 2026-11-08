# Pingouin Morpion — Jeu web et base de données

**Projet universitaire de Licence 2 Informatique.**

Application web de jeu inspirée du morpion, avec équipes, personnages aux caractéristiques différentes, configuration de parties, historique d'actions et statistiques.

## Fonctionnalités documentées dans le code
- Gestion des équipes et des personnages (« morpions »).
- Configuration du plateau et des parties.
- Actions sur la grille, historique et statistiques.
- Stockage relationnel en **PostgreSQL**.
- Pages web utilisant **Python**, **HTML/CSS** et des templates **Jinja**.

## Structure
- `site/` : pages, contrôleurs et modèle PostgreSQL.
- `database/schema.sql` : schéma et données SQL du projet (attention : ce fichier peut réinitialiser les tables du schéma ciblé).

## Mise en route
Le site s'appuie sur le **serveur pédagogique `bdw-server`** de l'UE BDW et **ne constitue pas une application Flask/Django autonome**.

1. Préparer une base PostgreSQL de test et examiner `database/schema.sql` avant toute exécution.
2. Installer le serveur pédagogique `bdw-server` fourni par l'enseignement.
3. Placer le dossier `site/` dans le répertoire `websites/` de ce serveur, sous le nom `serial_critique`.
4. Configurer localement l'accès PostgreSQL dans **un fichier de configuration personnel non publié**.
5. Depuis le répertoire du serveur pédagogique, activer son environnement Python et lancer :
```bash
python server.py serial_critique
```

## Compétences mises en pratique
Python, SQL, PostgreSQL, HTML/CSS, architecture MVC simplifiée, requêtes et manipulation de données.

## Note de confidentialité
Les fichiers de configuration contenant des identifiants et des mots de passe ont été **exclus** de cette copie. Ne les ajoutez jamais à GitHub. Des éléments du serveur de cours ont également été exclus ; l'application nécessite donc le serveur pédagogique séparément.

## Crédits
Projet universitaire. L'application s'appuie sur l'infrastructure pédagogique de l'Université Claude Bernard Lyon 1 ; préciser les contributions des autres membres si le projet a été réalisé en groupe.

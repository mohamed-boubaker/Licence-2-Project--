import psycopg
from psycopg import sql
from logzero import logger

# --- FONCTIONS GÉNÉRIQUES ---

def execute_select_query(connexion, query, params=[]):
    """
    Méthode générique pour exécuter une requête SELECT.
    """
    with connexion.cursor() as cursor:
        try:
            cursor.execute(query, params)
            result = cursor.fetchall()
            return result
        except psycopg.Error as e:
            logger.error(f"Erreur SQL (Select): {e}")
    return None

def execute_other_query(connexion, query, params=[]):
    """
    Méthode générique pour exécuter INSERT, UPDATE, DELETE.
    """
    with connexion.cursor() as cursor:
        try:
            cursor.execute(query, params)
            result = cursor.rowcount
            return result 
        except psycopg.Error as e:
            logger.error(f"Erreur SQL (Action): {e}")
    return None

def get_instances(connexion, nom_table):
    """
    Retourne les instances de la table en forçant le schéma 'jeu'
    """
    # Ajout de 'jeu.' pour être sûr de trouver la table
    query = sql.SQL('SELECT * FROM jeu.{}').format(sql.Identifier(nom_table))
    return execute_select_query(connexion, query)

def count_instances(connexion, nom_table):
    """
    Compte les instances en forçant le schéma 'jeu'
    """
    query = sql.SQL('SELECT COUNT(*) AS nb FROM jeu.{}').format(sql.Identifier(nom_table))
    return execute_select_query(connexion, query)

# --- FONCTIONS SPÉCIFIQUES AU JEU ---

def get_configs(connexion):
    """
    Récupère toutes les configurations.
    """
    # On précise 'jeu.config'
    query = 'SELECT * FROM jeu.config'
    return execute_select_query(connexion, query)

def insert_config(connexion, id_config, taille, maxtour):
    """
    Insère une config dans jeu.config.
    """
    query = 'INSERT INTO jeu.config (id_config, taille_de_grille, maxtour) VALUES(%s, %s, %s)'
    return execute_other_query(connexion, query, [id_config, taille, maxtour])

def insert_equipe(connexion, couleur, nom):
    """
    Insère une équipe dans jeu.equipe.
    """
    query = 'INSERT INTO jeu.equipe (couleur, nom, date_creation) VALUES(%s, %s, CURRENT_DATE)'
    return execute_other_query(connexion, query, [couleur, nom])

def get_equipe_by_couleur(connexion, couleur):
    """
    Récupère une équipe par sa couleur.
    """
    query = 'SELECT * FROM jeu.equipe where couleur=%s'
    return execute_select_query(connexion, query, [couleur])

def create_partie_avec_config(connexion, equipe1, equipe2, id_config):
    """
    Crée une partie en utilisant l'ID d'une configuration EXISTANTE.
    """
    import uuid
    id_partie = str(uuid.uuid4())[:8] 

    with connexion.cursor() as cursor:
        try:
            # 1. Créer la partie (Lien vers jeu.partie)
            cursor.execute(
                "INSERT INTO jeu.partie (idpartie, datedebut, id_config) VALUES (%s, CURRENT_TIMESTAMP, %s)", 
                [id_partie, id_config]
            )
            
            # 2. Faire jouer les équipes (Lien vers jeu.jouer)
            cursor.execute("INSERT INTO jeu.jouer (couleur, idpartie) VALUES (%s, %s)", [equipe1, id_partie])
            cursor.execute("INSERT INTO jeu.jouer (couleur, idpartie) VALUES (%s, %s)", [equipe2, id_partie])
            
            return id_partie
        except Exception as e:
            print(f"Erreur SQL lors de la création de la partie : {e}")
            return None

def create_game_setup(connexion, equipe1, equipe2, taille, tours):
    """
    Crée tout d'un coup : config + partie + joueurs (optionnel, si vous utilisez encore l'ancien système).
    """
    import uuid
    id_partie = str(uuid.uuid4())[:8]
    id_config = f"conf_{id_partie}"

    with connexion.cursor() as cursor:
        try:
            cursor.execute("INSERT INTO jeu.config (id_config, taille_de_grille, maxtour) VALUES (%s, %s, %s)", [id_config, taille, tours])
            cursor.execute("INSERT INTO jeu.partie (idpartie, datedebut, id_config) VALUES (%s, CURRENT_TIMESTAMP, %s)", [id_partie, id_config])
            cursor.execute("INSERT INTO jeu.jouer (couleur, idpartie) VALUES (%s, %s)", [equipe1, id_partie])
            cursor.execute("INSERT INTO jeu.jouer (couleur, idpartie) VALUES (%s, %s)", [equipe2, id_partie])
            return id_partie
        except Exception as e:
            print(f"Erreur création setup complet : {e}")
            return None

# --- FONCTIONS POUR L'ACCUEIL (Statistiques) ---

def get_top3_equipes_victoires(connexion):
    query = """
        SELECT e.nom, COUNT(*) AS victoires
        FROM jeu.partie p
        JOIN jeu.equipe e ON p.gagnant = e.couleur
        WHERE p.gagnant IS NOT NULL
        GROUP BY e.nom
        ORDER BY victoires DESC
        LIMIT 3
    """
    return execute_select_query(connexion, query)

def get_partie_plus_rapide(connexion):
    query = """
        SELECT p.idpartie, COUNT(j.numligne) as nb_coups
        FROM jeu.partie p
        JOIN jeu.journal j ON p.idpartie = j.idpartie
        GROUP BY p.idpartie
        ORDER BY nb_coups ASC
        LIMIT 1
    """
    return execute_select_query(connexion, query)

def get_partie_plus_longue(connexion):
    query = """
        SELECT p.idpartie, COUNT(j.numligne) as nb_coups
        FROM jeu.partie p
        JOIN jeu.journal j ON p.idpartie = j.idpartie
        GROUP BY p.idpartie
        ORDER BY nb_coups DESC
        LIMIT 1
    """
    return execute_select_query(connexion, query)

def get_activite_par_mois(connexion):
    """
    Compte le nombre de lignes dans le journal, groupées par mois et année.
    Affiche du plus récent au plus vieux.
    """
    query = """
        SELECT TO_CHAR(date_, 'MM/YYYY') as mois_annee, COUNT(*) as volume
        FROM jeu.journal
        GROUP BY mois_annee, EXTRACT(YEAR FROM date_), EXTRACT(MONTH FROM date_)
        ORDER BY EXTRACT(YEAR FROM date_) DESC, EXTRACT(MONTH FROM date_) DESC
    """
    return execute_select_query(connexion, query)
    
# --- FONCTIONS "FANTÔMES" (Laissées pour éviter les erreurs d'import des vieux fichiers) ---
def get_episodes_for_num(connexion, n): return []
def get_serie_by_name(connexion, n): return []
def insert_serie(connexion, n): return None
def get_table_like(connexion, t, p): return []  



def insert_possede(connexion, nom_morpion, couleur_equipe):
    """
    Lie un morpion à une équipe dans la table 'possede'.
    """
    # On utilise jeu.possede pour être sûr
    query = "INSERT INTO jeu.possede (nom, couleur) VALUES (%s, %s)"
    return execute_other_query(connexion, query, [nom_morpion, couleur_equipe])




def delete_equipe(connexion, couleur_equipe):
    """
    Supprime une équipe et toutes ses dépendances.
    Gère le nettoyage complet pour éviter les erreurs de Clés Étrangères.
    """
    with connexion.cursor() as cursor:
        try:
            print(f"--- DEBUG: Suppression de l'équipe {couleur_equipe} ---")
            
            # 1. Supprimer les pions sur le plateau (si la table existe)
            try:
                cursor.execute("DELETE FROM jeu.morpion_actif WHERE couleur = %s", [couleur_equipe])
            except Exception as e:
                print(f"DEBUG: Pas de table morpion_actif ou erreur mineure : {e}")
                # On continue quand même

            # 2. Supprimer les possessions (table possede)
            cursor.execute("DELETE FROM jeu.possede WHERE couleur = %s", [couleur_equipe])
            
            # 3. Supprimer la participation aux parties (table jouer)
            cursor.execute("DELETE FROM jeu.jouer WHERE couleur = %s", [couleur_equipe])
            
            # 4. IMPORTANT : Si l'équipe a gagné des parties, on met gagnant à NULL
            # Sinon, la base de données bloque la suppression de l'équipe
            cursor.execute("UPDATE jeu.partie SET gagnant = NULL WHERE gagnant = %s", [couleur_equipe])
            
            # 5. Supprimer l'équipe
            cursor.execute("DELETE FROM jeu.equipe WHERE couleur = %s", [couleur_equipe])
            
            print("--- DEBUG: Suppression réussie ---")
            return True
            
        except Exception as e:
            # Regardez ce message dans votre terminal noir si ça plante encore !
            print(f"--- DEBUG ERREUR CRITIQUE SUPPRESSION --- : {e}")
            return False
        

def get_morpions_equipe(connexion, couleur_equipe):
    """
    Récupère la liste des morpions (nom + image) que possède une équipe.
    """
    # On fait une jointure entre POSSEDE et MORPION pour avoir l'image
    query = """
        SELECT m.nom, m.image 
        FROM jeu.possede p
        JOIN jeu.morpion m ON p.nom = m.nom
        WHERE p.couleur = %s
    """
    return execute_select_query(connexion, query, [couleur_equipe])


# --- FONCTIONS Pour les stat du morpion pendant le jeu---
# récup les stat du morpion
def get_stats_morpion(connexion, nom_morpion):
    """ Récupère les stats de base (PV, Mana...) depuis le catalogue """
    query = "SELECT point_de_vie, mana, attaque, reussite FROM jeu.morpion WHERE nom = %s"
    return execute_select_query(connexion, query, [nom_morpion])
# insere le morpion dans la table morpion_actif
def insert_morpion_actif(connexion, id_partie, x, y, couleur, nom_morpion, pv, mana, atk, reussite):
    """ Crée le pion 'vivant' dans la table morpion_actif """
    query = """
        INSERT INTO jeu.morpion_actif 
        (idpartie, x, y, couleur, nom_morpion, pv_actuel, mana_actuel, attaque, reussite)
        VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s)
    """
    return execute_other_query(connexion, query, [id_partie, x, y, couleur, nom_morpion, pv, mana, atk, reussite])
#ajout l'action dans le journal
def insert_action_journal(connexion, id_partie, action):
    """ Ajoute une ligne dans l'historique """
    query = "INSERT INTO jeu.journal (numligne, date_, action, idpartie) VALUES (DEFAULT, CURRENT_TIMESTAMP, %s, %s)"
    return execute_other_query(connexion, query, [action, id_partie])
# récup l'état actuel du plateau

# récup les infos de la partie (taille de la grille et équipes)
def get_infos_partie(connexion, id_partie):
    """
    Récupère la taille de la grille et les infos des équipes (Couleur, Nom)
    pour une partie donnée.
    """
    query = """
        SELECT c.taille_de_grille, j.couleur, e.nom
        FROM jeu.config c
        JOIN jeu.partie p ON p.id_config = c.id_config
        JOIN jeu.jouer j ON j.idpartie = p.idpartie
        JOIN jeu.equipe e ON j.couleur = e.couleur
        WHERE p.idpartie = %s
        ORDER BY j.couleur
    """
    return execute_select_query(connexion, query, [id_partie])
#new de plateau.py

def get_nb_coups_partie(connexion, id_partie):
    """
    Compte le nombre de coups jouÃ©s dans une partie (pour dÃ©terminer le tour).
    """
    query = "SELECT COUNT(*) FROM jeu.journal WHERE idpartie = %s"
    result = execute_select_query(connexion, query, [id_partie])
    return result[0][0] if result else 0


def verifier_victoire(connexion, id_partie, couleur):
    """
    Vérifie si une équipe a gagné.
    MODIFICATION : On ignore les cases détruites (mana_actuel = -9999).
    """
    # 1. Récupérer la taille
    query_taille = """
        SELECT c.taille_de_grille 
        FROM jeu.partie p 
        JOIN jeu.config c ON p.id_config = c.id_config 
        WHERE p.idpartie = %s
    """
    res_taille = execute_select_query(connexion, query_taille, [id_partie])
    if not res_taille:
        return False
    taille = res_taille[0][0]
    
    # 2. Récupérer les positions (IGNORE LES CRATÈRES via mana_actuel != -9999)
    query_positions = """
        SELECT x, y 
        FROM jeu.morpion_actif 
        WHERE idpartie = %s AND couleur = %s AND mana_actuel != -9999
    """
    positions = execute_select_query(connexion, query_positions, [id_partie, couleur])
    
    if not positions or len(positions) < taille:
        return False 
    
    # Vérification des alignements (Lignes, Colonnes, Diagonales)
    coords = set((x, y) for x, y in positions)
    
    for i in range(taille):
        if all((i, j) in coords for j in range(taille)): return True
    for j in range(taille):
        if all((i, j) in coords for i in range(taille)): return True
    if all((i, i) in coords for i in range(taille)): return True
    if all((i, taille-1-i) in coords for i in range(taille)): return True
    
    return False



# --- AJOUTS OBLIGATOIRES POUR LES COMBATS ---

def get_morpion_par_position(connexion, id_partie, x, y):
    """ 
    Trouve le pion et renvoie SES INFOS.
    """
    query = """
        SELECT idpartie, x, y, couleur, nom_morpion, pv_actuel, mana_actuel, attaque, reussite 
        FROM jeu.morpion_actif 
        WHERE idpartie=%s AND x=%s AND y=%s
    """
    return execute_select_query(connexion, query, [id_partie, x, y])

def modifier_stats_morpion(connexion, id_partie, x, y, chgt_pv, chgt_mana, chgt_reussite):
    """ 
    Modifie les stats (+ ou -). 
    Exemple: chgt_pv = -3 pour enlever 3 PV.
    """
    query = """
        UPDATE jeu.morpion_actif 
        SET pv_actuel = pv_actuel + %s, 
            mana_actuel = mana_actuel + %s,
            reussite = reussite + %s
        WHERE idpartie = %s AND x = %s AND y = %s
    """
    return execute_other_query(connexion, query, [chgt_pv, chgt_mana, chgt_reussite, id_partie, x, y])

def nettoyer_les_morts(connexion, id_partie):
    """ SUPPRIME tous les pions qui ont 0 ou moins de PV """
    query = "DELETE FROM jeu.morpion_actif WHERE idpartie = %s AND pv_actuel <= 0"
    return execute_other_query(connexion, query, [id_partie])





def set_gagnant(connexion, id_partie, couleur_gagnant):
    """
    Enregistre le gagnant dans la table partie et met la date de fin à maintenant.
    """
    query = """
        UPDATE jeu.partie 
        SET gagnant = %s, datefin = CURRENT_TIMESTAMP 
        WHERE idpartie = %s
    """
    return execute_other_query(connexion, query, [couleur_gagnant, id_partie])


def detruire_case_definitivement(connexion, id_partie, x, y):
    """
    Transforme le pion en cratère (sans le supprimer pour éviter les erreurs SQL).
    On lui donne 9999 PV pour qu'il reste sur le plateau (bloquant la case).
    On lui donne -9999 Mana pour que le Template le reconnaisse comme un trou noir.
    """
    query = """
        UPDATE jeu.morpion_actif 
        SET pv_actuel = 9999, 
            mana_actuel = -9999,
            attaque = 0,
            reussite = 0
        WHERE idpartie = %s AND x = %s AND y = %s
    """
    return execute_other_query(connexion, query, [id_partie, x, y])

def get_etat_plateau_actif(connexion, id_partie):
    """ Récupère les infos complètes des pions (8 colonnes !) """
    # On s'assure d'avoir : x, y, couleur, image, pv, mana, reussite, nom
    query = """
        SELECT ma.x, ma.y, ma.couleur, m.image, ma.pv_actuel, ma.mana_actuel, ma.reussite, ma.nom_morpion
        FROM jeu.morpion_actif ma
        JOIN jeu.morpion m ON ma.nom_morpion = m.nom
        WHERE ma.idpartie = %s
    """
    return execute_select_query(connexion, query, [id_partie])

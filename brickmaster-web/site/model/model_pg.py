import psycopg
from psycopg import sql
from logzero import logger

def execute_select_query(connexion, query, params=[]):
    """
    Méthode générique pour exécuter une requête SELECT (qui peut retourner plusieurs instances).
    Utilisée par des fonctions plus spécifiques.
    """
    with connexion.cursor() as cursor:
        try:
            cursor.execute(query, params)
            result = cursor.fetchall()
            return result 
        except psycopg.Error as e:
            logger.error(e)
    return None

def execute_other_query(connexion, query, params=[]):
    """
    Méthode générique pour exécuter une requête INSERT, UPDATE, DELETE.
    Utilisée par des fonctions plus spécifiques.
    """
    with connexion.cursor() as cursor:
        try:
            cursor.execute(query, params)
            result = cursor.rowcount
            return result 
        except psycopg.Error as e:
            logger.error(e)
    return None

def get_instances(connexion, nom_table):
    """
    Retourne les instances de la table nom_table
    String nom_table : nom de la table
    """
    query = sql.SQL('SELECT * FROM {table}').format(table=sql.Identifier(nom_table), )
    return execute_select_query(connexion, query)

def count_instances(connexion, nom_table):
    """
    Retourne le nombre d'instances de la table nom_table
    String nom_table : nom de la table
    """
    query = sql.SQL('SELECT COUNT(*) AS nb FROM {table}').format(table=sql.Identifier(nom_table))
    return execute_select_query(connexion, query)

def count_couleurs(connexion, nom_table):
    """
    Retourne le nombre de pièces par couleurs
    """
    query = sql.SQL('SELECT couleur, count(couleur) FROM {table} GROUP BY couleur ORDER BY count(couleur) DESC').format(table=sql.Identifier(nom_table))
    return execute_select_query(connexion, query)

def min_max_score(connexion):
    """
    Retourne l'id du joueur puis le min puis le max du score
    """
    query = sql.SQL('SELECT prenom, MIN(score_g), MAX(score_g) FROM joueur INNER JOIN score ON idj=id_joueur GROUP BY prenom')
    return execute_select_query(connexion, query)

def count_partie_defausse(connexion):
    """
    Retourne le nombre de défausse par partie
    """
    query = sql.SQL("SELECT idP, COUNT(idP) FROM tour WHERE strpos(action, 'défaussé') > 0 GROUP BY idP ORDER BY COUNT DESC")
    return execute_select_query(connexion, query)

def random_bd(connexion, nom_table):
    """
    Retourne de manière aléatoire toute la table
    """
    query = sql.SQL("SELECT * FROM {table} WHERE longueur<=2 OR largeur<=2 ORDER BY random() LIMIT 1").format(table=sql.Identifier(nom_table))
    return execute_select_query(connexion, query)

def user_import(connexion, name, avatar):
    """
    Importe de la BD le nom d'utilisateur
    """
    q1 = ("SELECT id_joueur FROM joueur ORDER BY id_joueur DESC")
    e1 = int(execute_select_query(connexion, q1)[0][0]+1)
    print(e1)
    query = 'INSERT INTO joueur (id_joueur, prenom, date_inscription, avatar) VALUES (%s, %s, NOW(), %s)'
    print("a")
    return execute_other_query(connexion, query, [e1, name, avatar])

def user_in(connexion, name):
    """
    Vérifie si lenom rentré est dans la BD
    """
    query = sql.SQL('SELECT prenom FROM joueur')
    l = execute_select_query(connexion, query)
    print(l)
    if name in l:
        return True
    return False
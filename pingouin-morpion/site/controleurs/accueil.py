"""
ce fichier est vide, il faudra y mettre du code (question TP5)
"""

from model.model_pg import count_instances, get_episodes_for_num , get_top3_equipes_victoires, get_partie_plus_rapide, get_partie_plus_longue
from controleurs.includes import add_activity

add_activity(SESSION['HISTORIQUE'], "affichage des données")

# récupérer le nombre d'équipe equipe
REQUEST_VARS['equipe'] = count_instances(SESSION['CONNEXION'], 'equipe')
# récuperer le nombre de partie 
REQUEST_VARS['partie'] = count_instances(SESSION['CONNEXION'], 'partie')

# récuperer le nombre de morpion
REQUEST_VARS['morpion'] = count_instances(SESSION['CONNEXION'], 'morpion')

#top 3 des équipes avec le plus de victoires
REQUEST_VARS['top3'] = get_top3_equipes_victoires(SESSION['CONNEXION'])

#partie la plus rapide et la plus longue
REQUEST_VARS['partie_rapide'] = get_partie_plus_rapide(SESSION['CONNEXION'])
REQUEST_VARS['partie_longue'] = get_partie_plus_longue(SESSION['CONNEXION'])
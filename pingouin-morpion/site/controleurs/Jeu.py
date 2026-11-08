from model.model_pg import get_instances, get_configs, create_partie_avec_config
from controleurs.includes import add_activity

add_activity(SESSION['HISTORIQUE'], "page de lancement de partie")

# 1. Traitement du formulaire quand on clique sur "JOUER"
if POST and 'bouton_lancer' in POST:
    try:
        # On récupère les choix
        eq1 = POST['choix_equipe1'][0]
        eq2 = POST['choix_equipe2'][0]
        choix_config = POST['choix_config'][0] # L'ID de la config (ex: 'CONF_RAPIDE')

        if eq1 == eq2:
            REQUEST_VARS['message'] = "Erreur : Il faut deux équipes différentes !"
            REQUEST_VARS['message_class'] = "alert-error"
        else:
            # On crée la partie avec la config choisie
            id_partie = create_partie_avec_config(SESSION['CONNEXION'], eq1, eq2, choix_config)
            
            if id_partie:
                # Succès : on sauvegarde l'ID et on prépare la redirection
                SESSION['game_id'] = id_partie
                REQUEST_VARS['partie_creee_id'] = id_partie
            else:
                REQUEST_VARS['message'] = "Erreur technique SQL (voir terminal)."
                REQUEST_VARS['message_class'] = "alert-error"

    except Exception as e:
        REQUEST_VARS['message'] = f"Erreur : Avez-vous bien sélectionné une config ? ({e})"
        REQUEST_VARS['message_class'] = "alert-error"

# 2. Chargement des données pour l'affichage (GET)
REQUEST_VARS['equipes'] = get_instances(SESSION['CONNEXION'], 'equipe')
# C'est ici qu'on récupère tes configs créées dans la page Config
REQUEST_VARS['configs'] = get_configs(SESSION['CONNEXION'])
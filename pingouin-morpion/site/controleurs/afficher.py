from model.model_pg import get_instances, delete_equipe
from controleurs.includes import add_activity

add_activity(SESSION['HISTORIQUE'], "affichage équipes")

# GESTION DE LA SUPPRESSION
if POST and 'bouton_supprimer' in POST:
    try:
        couleur_a_supprimer = POST['couleur_a_supprimer'][0]
        
        # Appel de la fonction de suppression
        succes = delete_equipe(SESSION['CONNEXION'], couleur_a_supprimer)
        
        if succes:
            REQUEST_VARS['message'] = "L'équipe a été supprimée avec succès."
            REQUEST_VARS['message_class'] = "alert-success"
        else:
            REQUEST_VARS['message'] = "Erreur lors de la suppression."
            REQUEST_VARS['message_class'] = "alert-error"
    except Exception as e:
        REQUEST_VARS['message'] = f"Erreur technique : {e}"
        REQUEST_VARS['message_class'] = "alert-error"

# Chargement de la liste (mise à jour après suppression éventuelle)
REQUEST_VARS['equipes'] = get_instances(SESSION['CONNEXION'], 'equipe')
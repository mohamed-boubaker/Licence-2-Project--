from model.model_pg import get_equipe_by_couleur, insert_equipe, get_instances, insert_possede
from controleurs.includes import add_activity
import random

add_activity(SESSION['HISTORIQUE'], "page ajouter équipe")

if POST and 'bouton_valider' in POST:
    try:
        nom_equipe = POST['nom_equipe'][0]
        
        # --- CHANGEMENT ICI : Récupération de la couleur choisie ---
        # On récupère la valeur du formulaire et on la met en majuscule pour la base de données
        couleur_equipe = POST['couleur_equipe'][0].upper()
        
        # (On a supprimé les lignes avec random.randint)
        
        choix_morpions = POST.get('choix_morpions', [])

        if len(choix_morpions) < 6 or len(choix_morpions) > 8:
            REQUEST_VARS['message'] = f"Erreur : Choisissez entre 6 et 8 morpions (actuel: {len(choix_morpions)})."
            REQUEST_VARS['message_class'] = "alert-warning"
        else:
            # Le Contrôleur demande au Modèle si l'équipe existe déjà
            equipe_existe = get_equipe_by_couleur(SESSION['CONNEXION'], couleur_equipe)
            
            if not equipe_existe:
                # Le Modèle insère les données
                insert_equipe(SESSION['CONNEXION'], couleur_equipe, nom_equipe)
                
                for nom_morpion in choix_morpions:
                    insert_possede(SESSION['CONNEXION'], nom_morpion, couleur_equipe)
                
                REQUEST_VARS['message'] = f"Équipe {nom_equipe} créée ! (Couleur : {couleur_equipe})"
                REQUEST_VARS['message_class'] = "alert-success"
            else:
                # Gestion de l'erreur d'unicité
                REQUEST_VARS['message'] = "Cette couleur est déjà utilisée par une autre équipe. Veuillez en choisir une autre."
                REQUEST_VARS['message_class'] = "alert-error"

    except Exception as e:
        REQUEST_VARS['message'] = f"Erreur : {e}"
        REQUEST_VARS['message_class'] = "alert-error"

REQUEST_VARS['morpions_dispo'] = get_instances(SESSION['CONNEXION'], 'morpion')
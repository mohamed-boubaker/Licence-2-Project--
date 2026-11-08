from model.model_pg import insert_config 
from controleurs.includes import add_activity

add_activity(SESSION['HISTORIQUE'], "consultation de la page ajouter configuration")

if POST and 'bouton_ajouter_config' in POST:
    try:
        print("DEBUG: Bouton configuration cliqué !")
        
        # 1. Récupération des données
        id_config = POST['id_config'][0]
        
        # Gestion de la taille (qui peut être "3" ou "3x3")
        taille_raw = POST['taille_grille'][0] 
        if 'x' in taille_raw:
            taille_de_grille = int(taille_raw.split('x')[0]) # Garde le '3' de '3x3'
        else:
            taille_de_grille = int(taille_raw)
            
        maxtour = int(POST['nb_tours'][0])

        print(f"DEBUG: Envoi à la BD -> ID: {id_config}, Taille: {taille_de_grille}, Tours: {maxtour}")

        # 2. Insertion
        # On appelle la fonction de votre model_pg.py (qui doit être à jour !)
        succes = insert_config(SESSION['CONNEXION'], id_config, taille_de_grille, maxtour)
        
        if succes:
            REQUEST_VARS['message'] = f"La configuration '{id_config}' a bien été ajoutée !"
            REQUEST_VARS['message_class'] = "alert-success"
        else:
            REQUEST_VARS['message'] = "Erreur SQL : Impossible d'ajouter (Vérifiez si l'ID existe déjà)."
            REQUEST_VARS['message_class'] = "alert-error"
            
    except Exception as e:
        print(f"DEBUG ERREUR: {e}")
        if "duplicate key" in str(e):
             REQUEST_VARS['message'] = f"L'ID '{id_config}' existe déjà."
        else:
            REQUEST_VARS['message'] = f"Erreur technique : {e}"
        REQUEST_VARS['message_class'] = "alert-error"
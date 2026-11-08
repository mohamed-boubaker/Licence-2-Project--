from model.model_pg import execute_select_query, get_morpions_equipe, get_infos_partie, get_stats_morpion, insert_morpion_actif, insert_action_journal, get_etat_plateau_actif, verifier_victoire, get_nb_coups_partie
from model.model_pg import get_morpion_par_position, modifier_stats_morpion, nettoyer_les_morts , set_gagnant
from controleurs.includes import add_activity
import random 

add_activity(SESSION['HISTORIQUE'], "plateau de jeu")

if 'game_id' not in SESSION:
    REQUEST_VARS['message'] = "Pas de partie en cours."
else:
    id_partie = SESSION['game_id']
    REQUEST_VARS['id_partie'] = id_partie

    # --- 1. CLIC UTILISATEUR (Récupération des coordonnées) ---
    case_cliquee = None
    if POST and 'btn_select_pion' in POST:
        case_cliquee = POST['btn_select_pion'][0] 
    elif POST and 'btn_jouer_case' in POST:
        case_cliquee = POST['btn_jouer_case'][0] 

    # --- 2. RÉSOLUTION ACTION (Si on avait cliqué sur un sort juste avant) ---
    if case_cliquee and 'action_en_cours' in SESSION:
        action = SESSION['action_en_cours']
        sort = action['sort']   
        x_lanceur, y_lanceur = action['x'], action['y']
        
        # On vide la mémoire
        del SESSION['action_en_cours']

        if ',' in case_cliquee:
            x_cible, y_cible = map(int, case_cliquee.split(','))
            
            lanceur = get_morpion_par_position(SESSION['CONNEXION'], id_partie, x_lanceur, y_lanceur)
            cible = get_morpion_par_position(SESSION['CONNEXION'], id_partie, x_cible, y_cible)
            
            distance = abs(x_lanceur - x_cible) + abs(y_lanceur - y_cible)

            # Logique de portée : Soin (0 ou 1 case), Attaque/Feu (1 case)
            portee_valide = False
            if sort == 'soin':
                portee_valide = (distance <= 1) # Soi-même ou voisin
            else:
                portee_valide = (distance == 1) # Voisin uniquement

            if not lanceur:
                REQUEST_VARS['message'] = "Erreur : le lanceur a disparu."
            elif not portee_valide:
                if sort == 'soin':
                    REQUEST_VARS['message'] = "Pour soigner : cliquez sur vous-même ou un voisin."
                else:
                    REQUEST_VARS['message'] = "Trop loin ! Visez une case juste à côté."
                REQUEST_VARS['message_class'] = "alert-warning"
            else:
          # --- CALCUL DU RESULTAT ---
                stats = lanceur[0]
                try:
                    couleur = stats[3]
                    attaque = stats[7]
                    reussite = float(stats[8])
                except:
                    couleur, attaque, reussite = stats[3], 1, 5.0

                # 1. D'ABORD : ON VÉRIFIE SI LA CIBLE EST VALIDE
                cible_valide = False
                
                if sort in ['attaque', 'boule_feu']:
                    # Il faut un ennemi
                    if cible and cible[0][3] != couleur:
                        cible_valide = True
                    else:
                        REQUEST_VARS['message'] = "Cible invalide."

                elif sort == 'soin':
                    # Il faut un ami
                    if cible and cible[0][3] == couleur:
                        cible_valide = True
                    else:
                        REQUEST_VARS['message'] = "Cible invalide."

                elif sort == 'armageddon':
                    cible_valide = True

                # 2. SI LA CIBLE EST BONNE, ON JOUE LE COUP
                if cible_valide:
                    # Définition des coûts
                    cout, degats, soin = 0, 0, 0
                    if sort == 'attaque': degats = attaque
                    elif sort == 'boule_feu': cout, degats = 2, 3
                    elif sort == 'armageddon': cout, degats = 5, 999
                    elif sort == 'soin': cout, soin = 1, 2 

                    # On paye le coût du sort (MANA PERDU QUOI QU'IL ARRIVE)
                    modifier_stats_morpion(SESSION['CONNEXION'], id_partie, x_lanceur, y_lanceur, 0, -cout, 0)

                    # ON LANCE LE DÉ
                    chance = reussite 
                    jet_de = random.randint(-10, 100)
                    reussi = jet_de > chance

                    if reussi:
                        # --- SUCCÈS : APPLICATION DES BONUS (+1 Mana, +0.5 XP) ---
                        modifier_stats_morpion(SESSION['CONNEXION'], id_partie, x_lanceur, y_lanceur, 0, 1, 0.5)

                        if sort in ['attaque', 'boule_feu']:
                            modifier_stats_morpion(SESSION['CONNEXION'], id_partie, x_cible, y_cible, -degats, 0, 0)

                        elif sort == 'armageddon':
                             from model.model_pg import detruire_case_definitivement
                             detruire_case_definitivement(SESSION['CONNEXION'], id_partie, x_cible, y_cible)
                        
                        elif sort == 'soin':
                            modifier_stats_morpion(SESSION['CONNEXION'], id_partie, x_cible, y_cible, soin, 0, 0)
                    
                    # (Si échec, on ne fait rien de plus, le mana est déjà perdu)

                    # Le tour ne passe QUE si une action valide a été tentée
                    insert_action_journal(SESSION['CONNEXION'], id_partie, f"{sort} sur {x_cible},{y_cible}")
                    nettoyer_les_morts(SESSION['CONNEXION'], id_partie)
                    
                    # On réactive le refresh automatique car il n'y a plus de message à lire
                    REQUEST_VARS['refresh'] = True

    # --- 3. CHARGEMENT PLATEAU ---
    infos = get_infos_partie(SESSION['CONNEXION'], id_partie)
    if infos:
        taille = infos[0][0]
        coul1, nom1 = infos[0][1], infos[0][2]
        coul2, nom2 = infos[1][1], infos[1][2] if len(infos) > 1 else (coul1, nom1)

        REQUEST_VARS['taille_grille'] = taille
        REQUEST_VARS['nom_equipe1'] = nom1; REQUEST_VARS['coul_equipe1'] = coul1
        REQUEST_VARS['nom_equipe2'] = nom2; REQUEST_VARS['coul_equipe2'] = coul2

        donnees_actifs = get_etat_plateau_actif(SESSION['CONNEXION'], id_partie)
        grille = [[None for _ in range(taille)] for _ in range(taille)]
        images_utilisees = [] 
        
        # Liste pour filtrer les pions déjà posés (vivants)
        noms_sur_plateau = set()

        if donnees_actifs:
            for ligne in donnees_actifs:
                # On déballe les 8 valeurs envoyées par le modèle
                x, y, c, img, pv, mana, reuss, nom_p = ligne
                
                grille[x][y] = {
                    'couleur': c, 
                    'image': img, 
                    'pv': pv, 
                    'mana': mana, 
                    'reussite': reuss, 
                    'nom': nom_p
                }
                # On note que ce pion est sur le plateau
                noms_sur_plateau.add(nom_p)

        nb_coups = get_nb_coups_partie(SESSION['CONNEXION'], id_partie)
        tour_couleur = coul1 if nb_coups % 2 == 0 else coul2
        tour_nom = nom1 if nb_coups % 2 == 0 else nom2

        REQUEST_VARS['grille'] = grille
        REQUEST_VARS['tour_nom'] = tour_nom
        REQUEST_VARS['tour_couleur'] = tour_couleur
        
       # VÉRIFICATION VICTOIRE ÉQUIPE 1
        if verifier_victoire(SESSION['CONNEXION'], id_partie, coul1):
            REQUEST_VARS['gagnant_nom'] = nom1
            # C'est ici qu'on sauvegarde en Base de Données !
            set_gagnant(SESSION['CONNEXION'], id_partie, coul1)

        # VÉRIFICATION VICTOIRE ÉQUIPE 2
        elif verifier_victoire(SESSION['CONNEXION'], id_partie, coul2):
            REQUEST_VARS['gagnant_nom'] = nom2
            # Sauvegarde en Base de Données
            set_gagnant(SESSION['CONNEXION'], id_partie, coul2)

        # --- 4. CLIC BOUTON ACTION ---
        if POST and 'btn_action' in POST:
            SESSION['action_en_cours'] = {
                'sort': POST['btn_action'][0], 
                'x': int(POST['src_x'][0]), 
                'y': int(POST['src_y'][0])
            }
            if POST['btn_action'][0] == 'soin':
                REQUEST_VARS['message'] = "Soin activé : Cliquez sur VOUS-MÊME ou un VOISIN."
            else:
                REQUEST_VARS['message'] = f"Action {POST['btn_action'][0]} : Cliquez sur une case voisine."
            REQUEST_VARS['message_class'] = "alert-warning"

        # --- 5. SELECTION PION ---
        coord_select = None
        if POST and 'btn_select_pion' in POST and 'action_en_cours' not in SESSION:
            coord_select = POST['btn_select_pion'][0]

        if coord_select and ',' in coord_select:
            sx, sy = map(int, coord_select.split(','))
            if grille[sx][sy] and grille[sx][sy]['couleur'] == tour_couleur:
                pion = grille[sx][sy]
                REQUEST_VARS['selection_pion'] = {'x': sx, 'y': sy, 'nom': pion['image']}
                mana = pion['mana']
                REQUEST_VARS['actions_possibles'] = {
                    'attaque': True,
                    'soin': mana >= 1,
                    'boule_feu': mana >= 2,
                    'armageddon': mana >= 5
                }
            elif POST and 'btn_select_pion' in POST:
                 REQUEST_VARS['message'] = "Ce n'est pas votre pion !"

       # --- 6. POSE PION ---
        if not REQUEST_VARS.get('gagnant_nom') and 'action_en_cours' not in SESSION:
            tous = get_morpions_equipe(SESSION['CONNEXION'], tour_couleur)
            
            # --- LOGIQUE DE FILTRAGE MISE À JOUR ---
            # On veut exclure les pions qui sont :
            # 1. Sur le plateau (vivants)
            # 2. Dans le cimetière (morts mais déjà joués, trouvés via le journal)
            
            pions_deja_joues = set()

            # 1. Ajouter ceux qui sont VIVANTS sur le plateau
            if donnees_actifs:
                for pion in donnees_actifs:
                    # Structure : x, y, couleur, image, pv, mana, NOM
                    if pion[2] == tour_couleur:
                        pions_deja_joues.add(pion[6]) # On ajoute le NOM

            # 2. Ajouter ceux qui sont MORTS (via le journal)
            # On lit l'historique pour voir ce qui a été joué
            query_journal = "SELECT action FROM jeu.journal WHERE idpartie = %s"
            logs = execute_select_query(SESSION['CONNEXION'], query_journal, [id_partie])
            
            if logs:
                for row in logs:
                    act = row[0]
                    # On cherche les lignes du type "PLACE:x:y:NOM:COULEUR"
                    parts = act.split(':')
                    if len(parts) >= 5 and parts[0] == 'PLACE':
                        nom_joue = parts[3]
                        coul_joue = parts[4]
                        if coul_joue == tour_couleur:
                            pions_deja_joues.add(nom_joue)

            # On filtre la liste 'tous' en excluant ceux dont le NOM est dans 'pions_deja_joues'
            REQUEST_VARS['mes_morpions'] = [m for m in tous if m[0] not in pions_deja_joues]
            # ---------------------------------------------------

            if POST and 'btn_jouer_case' in POST:
                coord = POST['btn_jouer_case'][0].split(',')
                cx, cy = int(coord[0]), int(coord[1])
                choix = POST.get('choix_img') # Note: choix[0] est le NOM du morpion
                
                if choix and grille[cx][cy] is None:
                    res = get_stats_morpion(SESSION['CONNEXION'], choix[0])
                    if res:
                        row = res[0]
                        if len(row) >= 4:
                            pv, mana, atk, reus = row[0], row[1], row[2], row[3]
                            insert_morpion_actif(SESSION['CONNEXION'], id_partie, cx, cy, tour_couleur, choix[0], pv, mana, atk, reus)
                            
                            # --- IMPORTANT : On enregistre le NOM et la COULEUR dans le journal ---
                            # Cela permet de s'en souvenir même si le pion meurt plus tard
                            insert_action_journal(SESSION['CONNEXION'], id_partie, f"PLACE:{cx}:{cy}:{choix[0]}:{tour_couleur}")
                            
                            REQUEST_VARS['refresh'] = True
                        else:
                            REQUEST_VARS['message'] = "Erreur données morpion."
                elif not choix:
                    REQUEST_VARS['message'] = "Sélectionnez un pion à gauche !"
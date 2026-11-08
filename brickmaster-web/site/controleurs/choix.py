from model.model_pg import user_import, user_in

if POST and 'valider' in POST:
    nom = POST['nom_utilisateur'][0] #récupèration du nom saisis dans al méthode
    avatar = POST['avatar'][0] #avatar choisi
    print(nom) #différents tests dans la console
    print(avatar)
    print(user_in(SESSION['CONNEXION'], nom))
    if user_in(SESSION['CONNEXION'], nom) == False: #vérifie que l'utilisateur n'est aps déjà présents
        user_import(SESSION['CONNEXION'], nom, avatar)
        SESSION['UTILISATEUR'] = nom
        REQUEST_VARS['UTILISATEUR'] = nom
        REQUEST_VARS['message_usr_import'] = "Tu t'es bien connecté et a été importé dans la base de donnée"
    else:
        REQUEST_VARS['message_usr_import'] = "Il y a déjà quelqu'un avec ce nom, si ce n'est pas toi alors change de nom :D"
        SESSION['UTLISATEUR'] = nom
        REQUEST_VARS['UTILISATEUR'] = nom



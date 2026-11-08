from model.model_pg import get_instances, random_bd
from random import randint

def init_grille(longueur=10, largeur=10):
    #init à 0 de toutes les cases = vides
    grille = []
    for i in range(longueur):
        print(i)
        grille.append([])
        for j in range(largeur):
            grille[i].append(0)
    return grille

def trouve_vide(grille, i, j):
    from random import randint
    directions = [(0,1), (1,0), (0,-1), (-1,0)] #les directions possibles pour trouver une case vide
    k = randint(0,3)
    while(grille[i+directions[k][0]][j+directions[k][1]] != 0): #tests des différentes directions
        k = randint(0,3)
        print(directions[k])
    print("sorti du while ici")
    return directions[k]

def danslagrille(longueur, largeur, i, j):
    return (i<longueur-1 and j<largeur-1) #retroune si les indices de la grille sont bien dans la grille

def aleatoire_grille(grille, longueur, largeur, danslagrille = danslagrille):
    from random import randint
    directions = [(0,1), (1,0), (0,-1), (-1,0)]
    ibase = randint(0, longueur-1)
    jbase = randint(0, largeur-1) #choix aléatoire du début
    nbcible = randint(int(0.1*(longueur*largeur)),int(0.2*(largeur*longueur))) #nombre de cible de 10 à 20% de la grille
    nbcasetraite = 0
    while(nbcasetraite<=nbcible):
        if(grille[ibase][jbase]==0 and danslagrille(longueur, largeur, ibase, jbase)):
            grille[ibase][jbase] = 1 #0 vide, 1 cible, couleur #XXXXX remplis
            nbcasetraite+=1
        else:
            choix = randint(0,3)
            while(grille[ibase+directions[choix][0]][jbase+directions[choix][1]]==1 or danslagrille(longueur, largeur, ibase+directions[choix][0], jbase+directions[choix][1]) == False):
                choix = randint(0,3)
            ibase = ibase+directions[choix][0]
            jbase = jbase+directions[choix][1]
            grille[ibase][jbase] = 1
            nbcasetraite+=1
    return grille



"""def aleatoire_grille(grille, longueur, largeur, trouve_vide = trouve_vide):
    from random import randint
    ibase = randint(0, longueur)
    jbase = randint(0, largeur)
    for i in range(0, randint(int(0.1*(longueur*largeur)),int(0.2*(largeur*longueur)))):
        if(grille[ibase][jbase] == 0):
            grille[ibase][jbase] = 1
        else:
            l, j = trouve_vide(grille, ibase, jbase)
            grille[l][j] = 1
            ibase = l
            jbase = j
            print(ibase, jbase)
    return grille"""

def changement(grille, largeur, longueur, posx, posy, lcase, lacase, colcase, danslagrille=danslagrille):
    copy_grille = grille #créer une grille temporaire pour ne pas créer de problèmes
    cond = True #condition de sortie
    while(cond and danslagrille(longueur, largeur, posx, posy)):
        for i in range(lcase):
            for j in range(lacase):
                if(grille[posx+i][posy+j]==0 and danslagrille(longueur, largeur, posx+i, posy+j)):
                    copy_grille[posx+i][posy+j]=colcase #remplace la case par la couleur
                elif(danslagrille(longueur, largeur, posx+i, posy+j) == False):
                    return "erreur" #ici si la brique sort de la grille
                else:
                    return "déjà remplis" #ici si la brique se supperposent à une autre grille
    return "cc"


if 'grille_creer' in POST: #vérifie si la grille est créée
    SESSION['longueur'] = int(POST['longueur'][0])
    SESSION['largeur'] = int(POST['largeur'][0])
    print(SESSION['longueur'])
    print(SESSION['largeur'])
    SESSION["grille"] = init_grille(SESSION['longueur'], SESSION['largeur'])
    print(SESSION["grille"])
    SESSION["grille"] = aleatoire_grille(SESSION['grille'], SESSION['longueur'], SESSION['largeur'])


if 'pioche' not in SESSION: #si la pioche n'est pas créée
    SESSION['pioche'] = []
    SESSION['couleur'] = []
    res = random_bd(SESSION['CONNEXION'], 'piece') #retourne toute une ligne avce toutes les infos sur la brique trouvée de manière aléatoire
    SESSION['pioche'].append(res[0][0]) #append uniquement le numéro de la pièce
    SESSION['couleur'].append(res[0]) #append toute la ligne, pour de bas ey utilisé pour les couleurs mais aussi sa taille ect
    res1 = random_bd(SESSION['CONNEXION'], 'piece')
    SESSION['pioche'].append(res1[0][0])
    SESSION['couleur'].append(res1[0])
    res2 = random_bd(SESSION['CONNEXION'], 'piece')
    SESSION['pioche'].append(res2[0][0])
    SESSION['couleur'].append(res2[0])
    res3 = random_bd(SESSION['CONNEXION'], 'piece')
    SESSION['pioche'].append(res3[0][0])
    SESSION['couleur'].append(res3[0])
print(SESSION['couleur'])
if 'c' in POST:
    print(POST)
    print(POST['c'][0])
    #SESSION['pioche'].remove(int(POST['c'][0]))
    #SESSION['pioche'].append(random_bd(SESSION['CONNEXION'], 'piece')[0][0])
""" for i in range(4):
        print(POST['c'][0])
        print(SESSION['pioche'][i])
        if SESSION['pioche'][i] == POST['c'][0]:
            print("bonjour in")
            SESSION['pioche'][i] = random_bd(SESSION['CONNEXION'], 'piece')[0][0]"""
    
if 'place_brique' in POST:
    #SESSION['place_brique'] = "cc"
    #print(POST)
    #print("AAAH")
    #print(POST['brique'])
    print(POST['position_x'])
    if(changement(SESSION["grille"], SESSION['largeur'], SESSION['longueur'], int(POST['position_x'][0]), int(POST['position_y'][0]),1, 1, '#000000') == "cc"):
        SESSION['message'] = "cc"
    else:
        SESSION['message'] = "dd"
    SESSION['pioche'].remove(int(POST['brique'][0]))
    elt = [elt for elt in SESSION['couleur'] if elt[0] == int(POST['brique'][0])][0]
    print(elt)
    SESSION['couleur'].remove(elt)
    SESSION['pioche'].append(random_bd(SESSION['CONNEXION'], 'piece')[0][0])
    SESSION['couleur'].append(random_bd(SESSION['CONNEXION'], 'piece')[0]) #enleve la ligne et en haut la numero de la pice piochée et la remplace


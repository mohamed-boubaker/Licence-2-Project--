
from model.model_pg import count_instances, count_couleurs, min_max_score, count_partie_defausse

#compter les instances pour joueur
res = count_instances(SESSION['CONNEXION'], 'joueur')
REQUEST_VARS["joueur"] = res[0][0]
if REQUEST_VARS["joueur"] == 1:
    REQUEST_VARS["message"] = f"Actuellement {REQUEST_VARS["joueur"]} seul joueur dans la base."
elif REQUEST_VARS["joueur"] > 1:
    REQUEST_VARS["message"] = f"Actuellement {REQUEST_VARS["joueur"]} joueurs dans la base."
else:
    REQUEST_VARS["message"] = "Aucune joueurs dans la base"

#compter les instances pour les legos
res1 = count_instances(SESSION['CONNEXION'], 'piece')
REQUEST_VARS["piece"] = res1[0][0]
if REQUEST_VARS["piece"] > 0:
    REQUEST_VARS["message1"] = f"Actuellement {REQUEST_VARS["piece"]} pièces dans la base."
else:
    REQUEST_VARS["message1"] = "Aucune pièces dans la base"

#compter les instances pour les parties
res2 = count_instances(SESSION['CONNEXION'], 'partie')
REQUEST_VARS["partie"] = res2[0][0]
if REQUEST_VARS["piece"] > 0:
    REQUEST_VARS["message2"] = f"Actuellement {REQUEST_VARS["partie"]} parties dans la base."
else:
    REQUEST_VARS["message2"] = "Aucune partie dans la base"

#compter les couleurs et le top 5
res3 = count_couleurs(SESSION['CONNEXION'], 'piece')
REQUEST_VARS["p"] = " "
for i in range(5):
    REQUEST_VARS["p"] = REQUEST_VARS["p"] + res3[i][0] + " : " + str(res3[i][1]) + ", "
REQUEST_VARS["message3"] = f"LE TOP 5 des couleurs le plus représentées est : {REQUEST_VARS["p"]}"

#chaque joueur son score min et max
res4 = min_max_score(SESSION['CONNEXION'])
REQUEST_VARS["p1"] = " "
for i in range(len(res4)):
    REQUEST_VARS["p1"] = res4[i][0] + " : MIN -> " + str(res4[i][1]) + " - MAX -> " + str(res4[i][2]) + ", "
REQUEST_VARS["message4"] = f"Les scores minimum et maximum de chaque joueur sont : {REQUEST_VARS["p1"]}"

# Parties avec le plus petit et plus grand nombre de pièces défaussées, de pièces piochées
res5 = count_partie_defausse(SESSION['CONNEXION'])
REQUEST_VARS["p2"] = "MAX -> partie n°" + str(res5[0][0]) + " avec " + str(res5[0][1]) + ", MAX -> partie n°" + str(res5[(len(res5)-1)][0]) + " avec " + str(res5[(len(res5)-1)][1])
REQUEST_VARS["message5"] = f"Les parties avec minimum et maximum de défausses sont : {REQUEST_VARS["p2"]}"




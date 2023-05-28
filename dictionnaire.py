fichier = open("dico2", "r")
liste = fichier.readlines()
fichier2 = open("dico", "w")
for elmt in liste:
    if not "è" in elmt:
        fichier2.write(elmt)
fichier.close()
fichier2.close()
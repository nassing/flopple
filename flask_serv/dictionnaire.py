fichier = open("dico.txt", "r")
liste = fichier.readlines()
fichier2 = open("dico2.txt", "w")
for elmt in liste:
    if len(elmt)>3:
        fichier2.write(elmt)
fichier.close()
fichier2.close()
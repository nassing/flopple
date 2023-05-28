def table():
    import string
#    fichier = open('/home/eleve/project2-E9/solveur_anna/dico.txt','r')
    fichier = open('solveur_anna\\pli07.txt','r')
    table=[['AA',0] for i in range (26**2)]
    alphabet=list(string.ascii_uppercase)
    for i in range (len(alphabet)):
        for j in range(len(alphabet)):
            table[26*i+j]=[alphabet[i]+alphabet[j],0]

    liste=fichier.readlines()
    for i in range (len(liste)):
        liste[i]=liste[i].strip('\n')
        for k in range (len(liste[i])-1):
            big=liste[i][k]+liste[i][k+1]
            for index in range(len(table)):
                if table[index][0]==big:
                    table[index][1]+=1
    for i in range(len(table)):
        table[i][1]=table[i][1]/len(liste)

    fichier.close()
    return table

def createDoc():
    tableau = table()
    with open('bibi.txt', 'w') as fichier:
        for i in range(len(tableau)):
            fichier.write( '\n'+str(tableau[i][0])+'\n'+str(tableau[i][1]) )
    return 'finito'

print(createDoc())
#table=table()
#print(table)
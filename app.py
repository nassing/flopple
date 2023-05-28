from inspect import getframeinfo
from flask import Flask, render_template, session, request, redirect, url_for, flash, json
from datetime import timedelta
import random

app = Flask(__name__)
app.secret_key = "floppaislovefloppaislife" #flopple est une clé de cryptage
app.permanent_session_lifetime = timedelta(minutes=15) #faudrait expliquer cette ligne vite fait

#======================================================================================================================
#
#                                                    Database
#
#======================================================================================================================

import sqlite3

def createTables():

    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute('''  CREATE TABLE IF NOT EXISTS userInfo (id INTEGER PRIMARY KEY AUTOINCREMENT, 
                                                            username TEXT NOT NULL UNIQUE,
                                                            password TEXT NOT NULL,
                                                            maxStreak INTEGER DEFAULT 0,
                                                            currentStreak INTEGER DEFAULT 0,
                                                            bingus_fragments INTEGER CHECK(0<=bingus_fragments) DEFAULT 0,
                                                            floppa_coins INTEGER CHECK(0<=floppa_coins) DEFAULT 0,
                                                            nb_win INTEGER DEFAULT 0,
                                                            nb_loss INTEGER DEFAULT 0)''')
                                                            
    cursor.execute('''  CREATE TABLE IF NOT EXISTS words (id_word INTEGER PRIMARY KEY AUTOINCREMENT, 
                                                        word TEXT NOT NULL UNIQUE,
                                                        length INTEGER NOT NULL)''')

    cursor.execute('''  CREATE TABLE IF NOT EXISTS completedGame (id_word_completed INTEGER REFERENCES words(id_word), 
                                                                id_player INTEGER NOT NULL REFERENCES userInfo(id),
                                                                PRIMARY KEY(id_word_completed, id_player))''')

    cursor.execute('''  CREATE TABLE IF NOT EXISTS games (id_game INTEGER PRIMARY KEY AUTOINCREMENT,
                                                        tries INTEGER NOT NULL DEFAULT 6,
                                                        guesses TEXT DEFAULT "",
                                                        results TEXT DEFAULT "",
                                                        status INTEGER CHECK (status = 0 OR status = 1 OR status = 2),
                                                        leftT INTEGER CHECK (0 <= leftT AND leftT <= tries),
                                                        id_word INTEGER REFERENCES words(id_word),
                                                        id_user INTEGER REFERENCES userInfo(id))''')

    cursor.execute('''  CREATE TABLE IF NOT EXISTS images (id_img INTEGER PRIMARY KEY,
                                                           image_rarity TEXT NOT NULL DEFAULT 10)''')

    cursor.execute(''' CREATE TABLE IF NOT EXISTS earnedImage (id_image_earned INTEGER REFERENCES words(id_word), 
                                                               id_player INTEGER NOT NULL REFERENCES userInfo(id),
                                                               PRIMARY KEY(id_image_earned, id_player))''')

createTables()


#======================================================================================================================
#
#                                                    Modifications DB
#
#======================================================================================================================

def addNewUser( username, password):
    #Fonction premettant de rajouter un nouvel utilisateur
    if not credentialsAlreadyExists(username): #Si le bool est vérifié, on a un alert_message
        con = sqlite3.connect("flopple.db")
        cursor = con.cursor()
        command = "INSERT INTO userInfo (username, password) VALUES (?, ?)"
        cursor.execute( command, (username, password))
        con.commit()
        con.close

def addWords():
    #ajouter les mots du dico dans la DB
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    try:
        fichier = open("dico2.txt", "r", encoding="utf-8")
    except:
        fichier = open("/home/eleve/project2-E9/flask_serv/dico2.txt", "r", encoding="utf-8")
    liste=fichier.readlines()
    try:
        for word in liste:
            if len(word) >= 3:
                word = word.strip().lower()
                command = "INSERT INTO words (word, length) VALUES (?, ?)"
                wordSize = len(word)
                cursor.execute(command, (word, wordSize))
    except:
        e = "error during the process"
    con.commit()
    fichier.close()
    con.close

def addImage(id_img, image_rarity):
    #ajouter une image dans la DB
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    command = "INSERT INTO images(id_img, image_rarity) VALUES (?, ?)"
    cursor.execute(command, (id_img, image_rarity))
    con.commit()
    con.close

def addNewWord( word):
    #Fonction premettant de rajouter un nouveau mot
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    command = "INSERT INTO words (word, length) VALUES (?, ?)"
    wordSize = len(word)
    cursor.execute( command, ( word, wordSize))
    con.commit()
    con.close

def earnedImage(img_id, user_id):
    #ajoute une image dans la collection d'un utilisateur
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    command = "INSERT INTO earnedImage(id_image_earned, id_player) VALUES (?, ?)"
    cursor.execute(command, (img_id, user_id))
    con.commit()
    con.close

def addImages():
    #ajoute toutes les images dans la DB
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    flops = [ "flopp"+str(u) for u in range(1, 24)]
    for address in flops:
        id = address[5]
        try:
            id += address[6]
        except:
            su = "suii"
        rarity = "commun"
        id = int(id)
        if id > 8:
            rarity = "rare"
        if id > 15:
            rarity = "epique"
        if id > 20:
            rarity = "legendaire"
        cursor.execute("INSERT INTO images (id_img, image_rarity) VALUES (?, ?)", (id, rarity,))
    con.commit()
    con.close

def changeFragments(number, id_user):
    #permet d'enlever à un utilisateur un certain nombre de fragments de Bingus
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    fragment_number=getFragments(id_user)
    cursor.execute("UPDATE userInfo SET bingus_fragments=? WHERE id=?", (fragment_number+number, id_user,))
    con.commit()
    con.close

def changeCoins(number, id_user):
    #permet d'ajouter à un utilisateur un certain nombre de floppa coins
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    coins_number=getCoins(id_user)
    cursor.execute("UPDATE userInfo SET floppa_coins=? WHERE id=?", (coins_number+number, id_user,))
    con.commit()
    con.close

def cleanTables():
    #permet de réinitialiser les tables words et images
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("DROP TABLE words")
    cursor.execute("DROP TABLE images")
    createTables()
    addImages()
    addWords()
    con.commit()
    con.close

def deleteUser( id_user):
    #supprime le profil du joueur avec pour id id_user
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("DELETE FROM userInfo WHERE id = ?", (id_user,))
    con.commit()
    con.close


#======================================================================================================================
#
#                                                    Verify
#
#======================================================================================================================

def wordExists(word):
    #vérifie si un mot existe
    return word in getWords(len(word))

def isLoggedIn():
    #Renvoie "true" si l'utilisateur connecté sinon "false"
    if "username" in session:
        return "true"
    return "false"

def credentialsAlreadyExists(username):
    #Fonction permettant de vérifier que les paramètres en entrée
    #sont bien compatibles avec les contraintes de la table
     con = sqlite3.connect("flopple.db")
     cursor = con.cursor()
     cursor.execute("SELECT username FROM userInfo")
     logInfo = cursor.fetchall()
     listVerif_username = []
     for info in logInfo:
        listVerif_username.append(info[0])
     if username in  listVerif_username:
         session["alert_message"]="Ce nom d'utilisateur existe déjà"
         return  True
         #On stocke les messages d'alertes dans session
     else:
        return False

def isLogInfoCorrect(username, password):
    #Fonction permettant de vérifier que les paramètres en entrer
    #correspondent bien à un utilisateur via les données de la db
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT username,password FROM userInfo")
    logInfo = cursor.fetchall()
    listVerif = []
    for info in logInfo:
        listVerif.append((info[0],info[1]))
    if (username, password) in listVerif:
        return True
    return False

def isAdmin(username):
    #vérifie si un utilisateur est administrateur
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT is_admin FROM userInfo WHERE username=?",(username,))
    isAdmin = cursor.fetchall()
    return isAdmin[0][0]


#======================================================================================================================
#
#                                                    Get
#
#======================================================================================================================

def getImageRarity(img_id):
    #permet de récupérer la valeur d'une image avec son id
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT image_rarity FROM images WHERE id_img=?", (img_id, ))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getCoins(user_id):
    #get number of floppa coins from user id
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT floppa_coins FROM userInfo WHERE id=?", (user_id, ))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getFragments(user_id):
    #get number of bingus fragments from user id
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT bingus_fragments FROM userInfo WHERE id=?", (user_id, ))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getWord(idW):
    #get word from its id
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT lower(word) FROM words WHERE id_word=?", (idW, ))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getWordID(word):
    #get word from its id
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_word FROM words WHERE word=?", (word, ))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getWords(length):
    #retourne la liste des mots en bd
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT word FROM words WHERE length=?", (length,))
    words = cursor.fetchall()
    words = [ u[0].strip() for u in words ] 
    con.close()
    return words

def getUserID(username):
    # fonction permettant de récupérer l'ID d'un user à partir de son username
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id FROM userInfo WHERE username=?", (username,)) 
    data = cursor.fetchall()[0][0]
    return data

def getUsername(id):
    # fonction permettant de récupérer l'username d'un user à partir de son id
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id,username FROM userInfo")
    list = cursor.fetchall()
    for u in list:
        if id in u:
            return u[1]


def getSucess(id_player):
    #permet de récupérer le nombre de succès d'un utilisateur
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_word_completed FROM completedGame WHERE id_player = ?", (id_player,))
    data = cursor.fetchall()
    if data != []:
        data = [u[0] for u in data]
    con.close()
    return data

def getEarnedImages(id_player):
    #renvoie les images gagnées par un utilisateur
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_image_earned FROM earnedImage WHERE id_player = ?", (id_player,))
    data = cursor.fetchall()
    if data != []:
        data = [u[0] for u in data]
    con.close()
    return data

def getStreak(id_player):
    #renvoie la série de victoires actuelle
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT currentStreak FROM userInfo WHERE id = ?", (id_player,))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getMaxStreak(id_player):
    #renvoie la série de victoires maximale
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT maxStreak FROM userInfo WHERE id = ?", (id_player,))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getNbLoss(id_player):
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT nb_loss FROM userInfo WHERE id = ?", (id_player,))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getNbWin(id_player):
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT nb_win FROM userInfo WHERE id = ?", (id_player,))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getIdWord(id_game):
    #renvoie l'id du mot cible d'une partie à partir de id_game
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_word FROM games WHERE id_game = ?", (id_game,))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getGameId(id_user, id_word):
    #renvoie l'id d'une partie à partir de l'id du joueur et du mot cible
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_game FROM games WHERE id_user = ? AND id_word = ?", (id_user, id_word))
    data = cursor.fetchall()[0][0]
    con.close()
    return data

def getLeftTries( id_game):
    #renvoie le nombre d'essais restant à partir de l'id de la partie
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT LeftT FROM games WHERE id_game = ?", (id_game,))
    data = cursor.fetchall()[0][0]
    con.close
    return data

def getGuessesConcatenated( id_game):
    #renvoie tous les mots entrés au cours d'une partie, dans une seule chaine de caractères concaténés
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT guesses FROM games WHERE id_game = ?", (id_game,))
    data = cursor.fetchall()[0][0]
    con.close
    return data

def getGuesses( id_game):
    #renvoie une liste des mots entrés au cours d'une partie
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT guesses FROM games WHERE id_game = ?", (id_game,))
    data = cursor.fetchall()[0][0]
    cursor.execute("SELECT length FROM words w JOIN games g ON w.id_word=g.id_word WHERE g.id_game = ?", (id_game,))
    wordSize = cursor.fetchall()[0][0]
    con.close
    guesses = guessesDataToList(data,wordSize)
    return guesses

def guessesDataToList(data,wordSize):
    #divise la chaine de caractère data en une liste de sous-chaine de caractère de taille wordSize
    guesses = []
    for i in range(len(data)//wordSize):
        guess = ""
        for j in range(wordSize):
            guess+=data[i*wordSize+j]
        guesses.append(guess)
    return guesses

def getResults( id_game):
    #renvoie les codes couleur associés aux mots entrés au cours de la partie
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT results FROM games WHERE id_game = ?", (id_game,))
    data = cursor.fetchall()
    con.close
    if data == []:
        return ""
    data = data[0][0]
    return data

def getResult( id_game):
    #renvoie le mot cible de la partie
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_word FROM games WHERE id_game = ?", (id_game,))
    result = getWord(cursor.fetchall()[0][0])
    con.close
    return str(result)

def getMaxTries( id_game):
    #renvoie le nombre d'essais maximum de la partie
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT tries FROM games WHERE id_game = ?", (id_game,))
    data = cursor.fetchall()[0][0]
    con.close
    return data

def getColors( id_game, tryWord):
    #renvoie le code couleur associé à un mot dans la partie
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    letters = len(tryWord)
    code = ""
    done = []
    word = getResult(id_game)
    if tryWord == None:
        for j in range( letters):
            code += "B"
    if not tryWord == None:
        for i in range( letters):
            color = "B"
            if word[i]==tryWord[i]:
                color = "G"
            code += color
        for k in range( letters):
            if tryWord[k] in word and code[k] != "G" :
                l = repetitions(tryWord[k], word)
                g = getGreens(code, tryWord[k], tryWord)
                l -= g
                for u in range( letters):
                    if tryWord[u] == tryWord[k] and code[k] == "B" and l > 0 and tryWord[u] not in done:
                        code = changeToOrange(k, code)
                        done.append(tryWord[u])
                        l -= 1
        con.commit()
        con.close
    return code

## --- Début des ajouts pour l'affichage des statistiques ---

def getNbPlayed(id_player):
    nb_loss, nb_win = getNbLoss(id_player), getNbWin(id_player)
    nb_played = nb_loss + nb_win
    return nb_played

def getListTries(id_player):
    # Prend en argument un joueur id_player pour renvoyer la liste croissante des tries de ses parties jouées
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    command = "SELECT DISTINCT tries FROM games WHERE status = 1 AND id_user = ? ORDER BY tries"
    cursor.execute(command, (id_player,))
    list_tries = cursor.fetchall()
    list_tries = [ u[0] for u in list_tries ]
    con.close()
    return list_tries

def getListlengthsTries(id_player):
    # Prend en argument un joueur id_player pour envoyer la liste des couples (length, tries) de ses parties triée par lengths droissants
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    command = "SELECT DISTINCT length, tries FROM words, games WHERE status = 1 AND games.id_word=words.id_word AND games.id_user = ? ORDER BY length"
    cursor.execute(command, (id_player,))
    list_lengthsTries = cursor.fetchall()
    con.close()

    return list_lengthsTries

def getListLeftT(id_player, tries, length):
    # Prend en argument un joueur id_player pour renvoyer la liste décroissante des leftT de ses différentes parties
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    command = "SELECT DISTINCT leftT FROM games, words WHERE words.id_word = games.id_word AND games.status = 1 AND games.id_user = ? AND games.tries = ? AND words.length = ? ORDER BY leftT DESC"
    cursor.execute(command, (id_player, tries, length))
    list_leftT = cursor.fetchall()
    con.close()

    nb_leftT = len(list_leftT)
    for i in range(nb_leftT):
        list_leftT[i] = int(list_leftT[i][0])

    return list_leftT

def guessDistribution(id_player, tries, length):
    # Prend en argument un joueur id_player pour renvoyer la liste D telle que D[i] = le nombre de parties de mots avec length lettres et gagnées après tries - list_leftT[i] essais
    list_leftT = getListLeftT(id_player, tries, length)
    nb_leftT = len(list_leftT)

    if list_leftT is None :
        return [[], []]

    distribution = []

    for i in range(nb_leftT) :
        leftT = list_leftT[i]
        con = sqlite3.connect("flopple.db")
        cursor = con.cursor()
        command = "SELECT COUNT(id_game) FROM games WHERE (status = 1 AND leftT = ? AND id_user = ?)"
        cursor.execute(command, (leftT, id_player))
        nb_win_withLeftT = cursor.fetchone()[0]
        distribution.append(nb_win_withLeftT)
        con.close()
        
    xAxis = [i+1 for i in range(tries)]
    yAxis = [0 for i in range(tries)]

    for i in range(nb_leftT):
        yAxis[tries-list_leftT[i]-1] = distribution[i]
    
    return [xAxis, yAxis]

# --- Fin des ajouts pour l'affichage des statistiques ---

def getReplays( id_user):
    # Prend en argument un joueur id_player pour renvoyer des infos sur les parties finies
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_game, id_word, leftT, tries FROM games WHERE status = 1 AND id_user = ?", (id_user,))
    fetch = cursor.fetchall()
    data = []
    info = []
    if fetch == []:
        return data, info
    for u in fetch:
        data.append((u[0], getWord(u[1]), u[3]-u[2]))
        info.append((u[0], getLeftTries(u[0]), len(getResult(u[0])), getMaxTries(u[0]), getResults(u[0]), getGuesses(u[0]), getNbPlayed(id_user), int(100*getNbWin(id_user)/getNbPlayed(id_user)), getStreak(id_user), getMaxStreak(id_user), getListTries(id_user), len(getListTries(id_user)), guessDistribution(id_user, u[3], len(getWord(u[1]))), getListlengthsTries(id_user), len(getListlengthsTries(id_user))))
    con.close()
    return data

#======================================================================================================================
#
#                                                    Get random
#
#======================================================================================================================

def randomId(wordSize):
    #renvoie aléatoirement un id d'un mot de taille wordSize
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_word FROM words WHERE length = ?", (wordSize,))
    data = cursor.fetchall()
    data = [u[0] for u in data]
    u = random.choice(data)
    con.close()
    return u

def tirageLoterie( coins):
    #renvoie aléatoirement l'id d'une image selon des règles particulières
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("SELECT id_img FROM images WHERE image_rarity = ?", ("commun",))
    commun = cursor.fetchall()
    commun = [u[0] for u in commun]
    cursor.execute("SELECT id_img FROM images WHERE image_rarity = ?", ("rare",))
    rare = cursor.fetchall()
    rare = [u[0] for u in rare]
    cursor.execute("SELECT id_img FROM images WHERE image_rarity = ?", ("epique",))
    epique = cursor.fetchall()
    epique = [u[0] for u in epique]
    cursor.execute("SELECT id_img FROM images WHERE image_rarity = ?", ("legendaire",))
    legendaire = cursor.fetchall()
    legendaire = [u[0] for u in legendaire]
    con.close
    lotterie1 = commun + commun + commun + commun + rare + rare + epique + legendaire
    lotterie2 = commun + commun + rare + rare + epique + epique + legendaire + legendaire
    lotterie3 = commun + rare + rare + epique + epique + epique + legendaire + legendaire + legendaire
    if coins == 1:
        return random.choice(lotterie1)
    if coins == 3:
        return random.choice(lotterie2)
    if coins == 5:
        return random.choice(lotterie3)


#======================================================================================================================
#
#                                                    Initialisation/update du jeu
#
#======================================================================================================================

def completeGame(id_user, id_game):
    #Fonction premettant de completer une partie
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    id_word = getIdWord(id_game)
    currentStreak = getStreak(id_user)+1
    maxStreak = getMaxStreak(id_user)
    if currentStreak > maxStreak:
        cursor.execute("UPDATE userInfo SET maxStreak=? WHERE id=?",(currentStreak, id_user,))
    command = "INSERT INTO completedGame (id_word_completed, id_player) VALUES (?, ?)"
    cursor.execute( command, ( id_word, id_user))
    cursor.execute("UPDATE games SET status=1 WHERE id_game=?",(id_game,))
    cursor.execute("UPDATE userInfo SET currentStreak=? WHERE id=?",(currentStreak, id_user,))
    cursor.execute("SELECT nb_win FROM userInfo WHERE id = ?", ( id_user,))
    nb = cursor.fetchall()[0][0]
    cursor.execute("UPDATE userInfo SET nb_win=? WHERE id=?",( nb+1, id_user))
    con.commit()
    con.close
    changeCoins(1,id_user)

def looseGame(id_user, id_game):
    #Fonction premettant de completer une partie
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("UPDATE userInfo SET currentStreak=0 WHERE id=?", (id_user,))
    cursor.execute("DELETE FROM games WHERE id_game=?", (id_game,))
    cursor.execute("SELECT nb_loss FROM userInfo WHERE id = ?", ( id_user,))
    nb = cursor.fetchall()[0][0]
    cursor.execute("UPDATE userInfo SET nb_loss=? WHERE id=?",( nb+1, id_user))
    con.commit()
    con.close
    changeFragments(1,id_user)

def createNewGame(id_user, wordSize, tries):
    #créer une nouvelle partie avec les paramètres donnés en entrée
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    sucess = getSucess(id_user )
    cursor.execute("SELECT id_word FROM words WHERE length = ?", (wordSize,))
    data = cursor.fetchall()
    avaibl = []
    for u in data:
        if u[0] not in sucess:
            avaibl.append(u[0])
    if avaibl == []:
        return "error"
    id_word = random.choice(avaibl)
    command = "INSERT INTO games (  tries, status, leftT, id_word, id_user ) VALUES (?, ?, ?, ?, ?)"
    cursor.execute( command, ( tries, 2, tries, id_word, id_user ))
    con.commit()
    con.close
    return id_word

def createNewSpecificGame(id_user, wordSize, tries, word):
    #créer une nouvelle partie avec les paramètres détaillés donnés en entrée
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    sucess = getSucess(id_user)
    id_word =  getWordID( word)
    if id_word not in sucess:
        command = "INSERT INTO games (  tries, status, leftT, id_word, id_user ) VALUES (?, ?, ?, ?, ?)"
        cursor.execute( command, ( tries, 2, tries, id_word, id_user ))
        con.commit()
        con.close
        return id_word
    return "error"

def wordPart(k, word):
    data = []
    for u in range(k, len(word)):
        data.append( word[u])
    return data

def changeToOrange(k, code):
    #change le k-ième caractère de code par "O"
    l = len(code)
    code2 = ""
    for i in range(k):
        code2 += code[i]
    code2 += "O"
    for j in range(k+1, l):
        code2 += code[j]
    return code2

def changeToGreen(k, code):
    #change le k-ième caractère de code par "O"
    l = len(code)
    code2 = ""
    for i in range(k):
        code2 += code[i]
    code2 += "G"
    for j in range(k+1, l):
        code2 += code[j]
    return code2

def repetitions(q, word):
#renvoie le nombre de répéptitions de q dans word
    sui = 0
    for u in word:
        if q == u:
            sui += 1
    return sui

def getGreens(code, q, tryWord):
#renvoie le nombre de fois où q dans tryWord est vert dans code
    siu = 0
    rep = repetitions(q, tryWord)
    for u in range(len(code)):
        if code[u] == "G" and q == tryWord[u]:
            siu += 1
    return siu

def getOranges(code, word, tryWord):
#renvoie le nombre de fois où q dans tryWord est orange dans code
    siu = 0
    rep = repetitions(q, tryWord)
    for u in range(len(code)):
        if code[u] == "O" and q == tryWord[u]:
            siu += 1
    return siu

def testWord(tryWord, id_game):
#teste tryWord (existence et correction) dans la partie id_game
    List = []
    code = ""
    result = False
    exists = False
    word = getResult(id_game)
    code = getColors( id_game, tryWord)
    exists = wordExists(tryWord)
    if word == tryWord:
        result = True
    List = [ tryWord, code]
    return List, result, exists


def updateGame( tryWord, id_game, code):
#rajoute le nouvel essai (code couleur, mot, nombre d'essais réduit) dans la DB
    triesLeft = getLeftTries(id_game) - 1
    guesses = getGuessesConcatenated(id_game) + tryWord
    results = getResults(id_game) + code
    con = sqlite3.connect("flopple.db")
    cursor = con.cursor()
    cursor.execute("UPDATE games SET leftT=? WHERE id_game=?", (triesLeft, id_game,))
    cursor.execute("UPDATE games SET guesses=? WHERE id_game=?", (guesses, id_game,))
    cursor.execute("UPDATE games SET results=? WHERE id_game=?", (results, id_game,))
    con.commit()
    con.close

def anyOnGoingGame(id_user, length):
#vérifie si une partie est en cours avec un mot de longueur demandé, renvoie l'id si oui
    con = sqlite3.connect("flopple.db")
    onGoin = False
    cursor = con.cursor()
    cursor.execute("SELECT id_game FROM games WHERE id_user = ? AND status = 2", (id_user,))
    data = cursor.fetchall()
    con.close
    gSize = []
    if data != []:
        data = [ u[0] for u in data ]
        for u in data:
            if len(getResult(u)) == length:
                gSize.append(u)
                onGoin = True
    if gSize != []:
        return onGoin, random.choice(gSize)
    return onGoin, 'none'

#======================================================================================================================
#
#                                                    Route Flask
#
#======================================================================================================================

@app.route("/")
#page d'acceuil, page principale du site
#La page s'affiche avec deux paramètres : Le message d'alerte
#Et une bool pour savoir si l'utilisateur est connecté
def index():
    floppaCoinsAmount=0
    bingusFragments=0
    if "username" in session:
            user_id=getUserID(session["username"])
            floppaCoinsAmount=getCoins(user_id)
            bingusFragments=getFragments(user_id)
    if "alert_message" in session:  #Si y'a un message d'alerte quelconque
        alert_message=session["alert_message"]
        session.pop("alert_message",None) #On le supprime, pour pas avoir à le ré-afficher la prochaine fois
        return render_template("index.html",alert_message=alert_message,isLoggedIn=isLoggedIn(),bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)
        #On affiche la page avec les paramètres correspondants
    return render_template("index.html",isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)

@app.route("/login")
#doit toujours avoir le "connexion register" dans le header, d'où le isLoggedIn="false"
def login():
    if "username" in session:
    #vérifie si l'utilisateur est connecté, sinon renvoie vers la page connexion
        session["alert_message"]="Vous êtes déjà conecté"
        return redirect(url_for("index"))
    if "alert_message" in session:
        alert_message=session["alert_message"]
        session.pop("alert_message",None)
        return render_template('login.html',alert_message=alert_message, isLoggedIn="false")
    return render_template('login.html', isLoggedIn="false")

@app.route("/logUser", methods=["POST", "GET"])
def logUser():
#renvoie vers la page de connexion puis récupère les données récupérées
#ensuite on vérifie que les informations sont correctes puis on connecte l'utilisateur
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        if isLogInfoCorrect(username, password):
            session.pop("alert_message",None)
            session.permanent = True
            session["username"] = username
            session["password"] = password
            return redirect(url_for("user"))
        session["alert_message"]="Nom d'utilisateur ou mot de passe incorrect"
        return redirect(url_for("login"))
    if "username" in session:
        return redirect(url_for("user"))
    session["alert_message"]="Erreur durant la connexion"
    return redirect(url_for("index"))

@app.route("/user")
def user():
#si connecté renvoie vers la page de confirmation
#sinon renvoie vers login pour connexion
    if "username" in session:
        session["alert_message"]="Vous êtes maintenant connecté"
        return redirect(url_for("index"))
    return redirect(url_for("login"))


@app.route("/register")
def register():
#vérifie si l'utilisateur est connecté, sinon renvoie vers la page de création de compte
#doit toujours avoir le "connexion register" dans le header, d'où le isLoggedIn="false"
    if "username" in session:
        session["alert_message"]="Vous êtes déjà connecté"
        return redirect(url_for("index"))
    if "alert_message" in session:
        alert_message=session["alert_message"]
        session.pop("alert_message",None)
        return render_template('register.html',alert_message=alert_message, isLoggedIn="false")
    return render_template('register.html', isLoggedIn="false")

@app.route("/addUser", methods=["POST", "GET"])
#page de création de compte
def addUser():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        confirm_password = request.form["confirm_password"]
        #On récupère les valeurs via un form
        if(password!=confirm_password):
            session["alert_message"]="Les mots de passes ne sont pas les mêmes"
            return redirect(url_for("register"))
        try:
            addNewUser( username, password)  #addNewUser crée un message d'alert si le mail/nom d'utilisateur existe déjà
            if "alert_message" in session :
                return redirect(url_for("register"))
            else:   #Sinon cela créé le compte, donc on informe l'utilisateur
                session["alert_message"]="Compte créé avec succès"
                return redirect(url_for("login"))
        except:
            session["alert_message"]="Erreur durant l'inscription"
            return redirect(url_for("register"))

@app.route("/logout")
def logout():
#Déconnecte l'utilisateur s'il est connecté
    if  "username" in session:
        session.pop("username", None)
        session["alert_message"]="Vous êtes maintenant déconnecté"
    else:
        session["alert_message"]="Vous n'êtes pas connecté"
    return redirect(url_for('index'))

@app.route("/addWord")
def addWord():
    floppaCoinsAmount=0
    bingusFragments=0
    if "username" in session:
            user_id=getUserID(session["username"])
            floppaCoinsAmount=getCoins(user_id)
            bingusFragments=getFragments(user_id)
            return render_template('add_word.html', isLoggedIn="true",bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)
    session["alert_message"] = 'Vous n\'êtes pas connecté'
    return redirect(url_for("index"))


@app.route("/newWord", methods=["POST", "GET"])
#page d'ajout de nouveau mots
def newWord():
    if "username" in session:
        if request.method == "POST":
            new_word = request.form["new_word"]
            #On récupère le mot via un form
            try:
                addNewWord( new_word)
                session["alert_message"]="Mot ajouté"
                return redirect(url_for("index"))
            except:
                session["alert_message"] = "Erreur durant l'ajout"
                return redirect(url_for("index"))
    session["alert_message"] = 'Vous n\'êtes pas connecté'
    return redirect(url_for("index"))

@app.route("/about")
#Page à propos
def about():
    floppaCoinsAmount=0
    bingusFragments=0
    if "username" in session:
            user_id=getUserID(session["username"])
            floppaCoinsAmount=getCoins(user_id)
            bingusFragments=getFragments(user_id)
            return render_template("about.html", isLoggedIn=isLoggedIn(),floppaCoinsAmount=floppaCoinsAmount,bingusFragments=bingusFragments)
    return render_template("about.html", isLoggedIn=isLoggedIn())

@app.route("/gallery")
#Page Galerie
def gallery():
    floppaCoinsAmount=0
    bingusFragments=0
    if "username" in session:
            user_id=getUserID(session["username"])
            floppaCoinsAmount=getCoins(user_id)
            bingusFragments=getFragments(user_id)
            boolean_list=[]
            list=getEarnedImages(user_id)
            images=[i for i in range(1,24)]
            for img in images:
                if img in list:
                    boolean_list.append(True)
                else:
                    boolean_list.append(False)
            return render_template("gallery.html", isLoggedIn=isLoggedIn(),floppaCoinsAmount=floppaCoinsAmount,bingusFragments=bingusFragments, boolean_list=boolean_list)
    return render_template("gallery.html", isLoggedIn=isLoggedIn())

@app.route("/reload")
#Pour télécharger la dernière version du site
def reload():
    if "username" in session:
        if session["username"]=="admin":
            import subprocess
            process = subprocess.Popen(['/usr/local/bin/flopple/flask_serv/gitpull.sh'])
            return redirect(url_for("index"))
    session["alert_message"] = 'Vous n\'êtes pas autorisé à faire cela'
    return redirect(url_for("index"))

@app.route('/joinGame', methods=["POST", "GET"])
#zgeg
def joinGame():
    if "username" in session:
        username = session['username']
        id_user = getUserID(username)

        # Début des ajouts pour l'affichage des statistiques

        nb_played = int(getNbPlayed(id_user))
        nb_win = int(getNbWin(id_user))
        if nb_played == 0 :
            win_rate = 0
        else:
            win_rate = int(100*nb_win/nb_played)
        currentStreak = int(getStreak(id_user))
        maxStreak = int(getMaxStreak(id_user))

        list_tries = getListTries(id_user)
        nb_tries = len(list_tries)
        list_lengthsTries = getListlengthsTries(id_user)
        nb_lengthsTries = len(list_lengthsTries)

        # Fin des ajouts pour l'affichage des statistiques

        if request.method == "POST":
            if request.form['submit'] == "Commencer":
                tries=int(request.form["tries"])
                wordSize=int(request.form["length"])
                onGoin, id_game = anyOnGoingGame(id_user, wordSize)

                # Début des ajouts pour l'affichage des statistiques
                guess_distribution = [[], []]
                # Fin des ajouts pour l'affichage des statistiques

                if onGoin:
                    if getLeftTries(id_game) == 0:
                        session["alert_message_flopp"] = 'Perdu !'
                        triesLeft = 0
                        wordSize = len(getResult( id_game))
                        maxTries = getMaxTries(id_game)
                        colors = getResults(id_game)
                        guesses = getGuesses(id_game)
                        looseGame(id_user, id_game)
                        return render_template("game.html", id_game=id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries , colors = colors, guesses = guesses, alert_message_flopp = session["alert_message_flopp"], finish = True, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, nb_lengthsTries=nb_lengthsTries)
                    colors = getResults(id_game)
                    maxTries = getMaxTries(id_game)
                    triesLeft = getLeftTries(id_game)
                    guesses = getGuesses(id_game)
                    return render_template("game.html",id_game=id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries, colors=colors, guesses=guesses, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
                tries=int(request.form["tries"])
                wordSize=int(request.form["length"])
                colors = []
                id_word = createNewGame(id_user, wordSize, tries)
                if id_word == "error":
                    session["alert_message"] = 'Tous les mots ont été trouvés'
                    return redirect(url_for("index"))
                try:
                    id_game = getGameId(id_user, id_word)
                    maxTries = tries
                    guesses=getGuesses(id_game)
                    return render_template("game.html", triesLeft = tries, wordSize = wordSize, maxTries = maxTries, id_game=id_game, colors=colors, guesses = guesses, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
                except:
                    session["alert_message"] = 'Erreur lors du lancement'
                    return redirect(url_for("index"))
            # Début des ajouts pour l'affichage des statistiques (copié-collé du code au dessus, avec des ajouts)
            elif request.form['submit'] == 'Display':
                tries=int(request.form["tries"])
                wordSize=int(request.form["length"])
                onGoin, id_game = anyOnGoingGame(id_user, wordSize)

                # Début des ajouts pour l'affichage des statistiques
                x = request.form['lengthsTriesDisplay'].split()
                tries_display = int(x[1])
                length_display = int(x[0])
                guess_distribution = guessDistribution(id_user, tries_display, length_display)
                # Fin des ajouts pour l'affichage des statistiques

                if onGoin:
                    if getLeftTries(id_game) == 0:
                        session["alert_message_flopp"] = 'Perdu !'
                        triesLeft = 0
                        wordSize = len(getResult( id_game))
                        maxTries = getMaxTries(id_game)
                        colors = getResults(id_game)
                        guesses = getGuesses(id_game)
                        looseGame(id_user, id_game)
                        return render_template("game.html", id_game=id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries , colors = colors, guesses = guesses, alert_message_flopp = session["alert_message_flopp"], finish = True, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
                    colors = getResults(id_game)
                    maxTries = getMaxTries(id_game)
                    triesLeft = getLeftTries(id_game)
                    guesses = getGuesses(id_game)
                    return render_template("game.html",id_game=id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries, colors=colors, guesses=guesses, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
                tries=int(request.form["tries"])
                wordSize=int(request.form["length"])
                colors = []
                id_word = createNewGame(id_user, wordSize, tries)
                if id_word == "error":
                    session["alert_message"] = 'Tous les mots ont été trouvés'
                    return redirect(url_for("index"))
                try:
                    id_game = getGameId(id_user, id_word)
                    maxTries = tries
                    guesses=getGuesses(id_game)
                    return render_template("game.html", triesLeft = tries, wordSize = wordSize, maxTries = maxTries, id_game=id_game, colors=colors, guesses = guesses, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
                except:
                    session["alert_message"] = 'Erreur lors du lancement'
                    return redirect(url_for("index"))
            # Fin des ajouts pour l'affichage des statistiques    
    session["alert_message"] = 'Vous n\'êtes pas connecté'
    return redirect(url_for("index"))
     

@app.route('/tryWord/<id_game>', methods=["POST", "GET"])
#teste un nouveau mot
def tryWord(id_game):
    if "username" in session:
        username = session['username']
        id_user = getUserID(username)

        # Début des ajouts pour l'affichage des statistiques

        nb_played = getNbPlayed(id_user)
        nb_win = getNbWin(id_user)
        if nb_played == 0 :
            win_rate = 0
        else:
            win_rate = int(100*nb_win/nb_played)
        currentStreak = getStreak(id_user)
        maxStreak = getMaxStreak(id_user)

        list_tries = getListTries(id_user)
        nb_tries = len(list_tries)   
        list_lengthsTries = getListlengthsTries(id_user)
        nb_lengthsTries = len(list_lengthsTries)

        guess_distribution = [[], []]

        # Fin des ajouts pour l'affichage des statistiques
           
        if request.method == "POST":
                word = request.form['tryWord'].lower()
                result = testWord(word, id_game)
                code = result[0][1]
                triesLeft = getLeftTries(id_game)
                answer = getResult(id_game)
                wordSize = len(word)
                maxTries = getMaxTries(id_game)
                guesses = getGuesses(id_game)
                colors = getResults(id_game)
                #vérifie si le mot est dans la DB
                if result[2] == False:
                    session["alert_message_flopp"] = 'Ce mot n\'existe pas'
                    return render_template("game.html",id_game=id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries, colors=colors, guesses = guesses, alert_message_flopp = session["alert_message_flopp"], finish = False, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
                updateGame(word, id_game, code)
                #vérifie si le mot est le bon
                if result[1] == True:
                    session["alert_message_flopp"] = 'Bien joué ! Voilà un Floppa Coin pour toi'
                    guesses = getGuesses(id_game)
                    colors = getResults(id_game)
                    completeGame(id_user, id_game)
                    return render_template("game.html", id_game=id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries , colors = colors, guesses = guesses, alert_message_flopp = session["alert_message_flopp"], finish = True, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
                #vérifie s'il reste des essais
                if getLeftTries(id_game) == 0 :
                    session["alert_message_flopp"] = "Perdu ! Le bon mot était '" + answer + "'"
                    triesLeft = 0
                    colors = getResults(id_game)
                    guesses = getGuesses(id_game)
                    looseGame(id_user, id_game)
                    bingusFragments = getFragments(id_user)
                    floppaCoinsAmount = getCoins(id_user)
                    if bingusFragments > 2 and username != "testSolveur":
                        session.pop("username", None)
                        deleteUser(id_user)
                        return render_template("looser.html", username=username, isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)
                    return render_template("game.html", id_game=id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries , colors = colors, guesses = guesses, alert_message_flopp = session["alert_message_flopp"], finish = True, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
                #continue la partie
                result = testWord(word, id_game)
                code = result[0][1]
                triesLeft = getLeftTries(id_game)
                wordSize = len(word)
                maxTries = getMaxTries(id_game)
                guesses = getGuesses(id_game)
                colors = getResults(id_game)
                return render_template("game.html",id_game = id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries, colors=colors, guesses = guesses, finish = False, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
    session["alert_message"] = 'Vous n\'êtes pas connecté'
    return redirect(url_for("index"))

@app.route('/loterie', methods =["POST","GET"])
def loterie():
    floppaCoinsAmount=0
    bingusFragments=0
    if "username" in session:
        username = session['username']
        id_user = getUserID(username)
        floppaCoinsAmount=getCoins(id_user)
        bingusFragments=getFragments(id_user)
        if request.method == "POST":
            coinCost = int(request.form["Nombre de coins"])
            #vérifie si l'user a assez de coins pour jouer
            if floppaCoinsAmount>=coinCost:
                image_id=tirageLoterie(coinCost)
                rarity=getImageRarity(image_id)
                changeCoins(-coinCost, id_user)
                #vérifie si l'image n'est pas en double
                if image_id not in getEarnedImages(id_user):
                    earnedImage(image_id, id_user)
                    floppaCoinsAmount=getCoins(id_user)
                    return render_template("resultats_loterie.html", msg = "Vous avez gagné une image!", address="floppa"+str(image_id)+".jpg", rarity=rarity, earned="image", isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)
                else :
                    #sinon, si l'user a des fragments, on lui en retire
                    if getFragments(id_user)>0:
                        changeFragments(-1,id_user)
                        bingusFragments=getFragments(id_user)
                        floppaCoinsAmount=getCoins(id_user)
                        return render_template("resultats_loterie.html", msg="Vous avez perdu un fragment de Bingus", address="", rarity=rarity, earned="bingus", isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)
                    #sinon, il gagne des floppa coins
                    else:
                        changeCoins(1,id_user)
                        floppaCoinsAmount=getCoins(id_user)
                        return render_template("resultats_loterie.html", msg="Vous avez gagné un Floppa Coin", address="", rarity=rarity, earned="floppa", isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)
            else :
                return render_template("loterie.html", msg="Vous n'avez pas assez de Floppa Coins :/", isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)
        return render_template("loterie.html", msg="", isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)
    session["alert_message"] = 'Vous n\'êtes pas connecté'
    return render_template("index.html", alert_message=session["alert_message"], isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)

@app.route('/games/<id_game>')
def games(id_game):
    floppaCoinsAmount=0
    bingusFragments=0
    if "username" in session:
        username = session['username']
        id_user = getUserID(username)
        floppaCoinsAmount=getCoins(id_user)
        bingusFragments=getFragments(id_user)
        triesLeft = getLeftTries(id_game)
        answer = getResult(id_game)
        wordSize = len(answer)
        maxTries = getMaxTries(id_game) - triesLeft
        guesses = getGuesses(id_game)
        colors = getResults(id_game)

        nb_played = getNbPlayed(id_user)
        nb_win = getNbWin(id_user)
        if nb_played == 0 :
            win_rate = 0
        else:
            win_rate = int(100*nb_win/nb_played)
        currentStreak = getStreak(id_user)
        maxStreak = getMaxStreak(id_user)

        list_tries = getListTries(id_user)
        nb_tries = len(list_tries)   
        list_lengthsTries = getListlengthsTries(id_user)
        nb_lengthsTries = len(list_lengthsTries)

        guess_distribution = [[], []]
        return render_template("game.html", id_game=id_game, triesLeft = triesLeft, wordSize = wordSize, maxTries = maxTries , colors = colors, guesses = guesses, alert_message_flopp = 'Cette partie est finie', finish = True, nb_played=nb_played, win_rate=win_rate, currentStreak=currentStreak, maxStreak=maxStreak, list_tries=list_tries, nb_tries=nb_tries, guess_distribution=guess_distribution, list_lengthsTries=list_lengthsTries, nb_lengthsTries=nb_lengthsTries)
    session["alert_message"] = 'Vous n\'êtes pas connecté'
    return redirect(url_for("index"))

@app.route('/replays')
def replays():
    floppaCoinsAmount=0
    bingusFragments=0
    if "username" in session:
        username = session['username']
        id_user = getUserID(username)
        floppaCoinsAmount=getCoins(id_user)
        bingusFragments=getFragments(id_user)
        data = getReplays( id_user)
        return render_template("replays.html", id_user=id_user, bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount, long=len(data), data=data)
    session["alert_message"] = 'Vous n\'êtes pas connecté'
    return render_template("index.html", alert_message=session["alert_message"], isLoggedIn=isLoggedIn(), bingusFragments=bingusFragments, floppaCoinsAmount=floppaCoinsAmount)


cleanTables()

#createNewSpecificGame(8, 5, 6, "trois")

if __name__ == "__main__":
    port = 5000 + random.randint(0, 999)
    app.run(use_reloader=False, debug=True, port=port)
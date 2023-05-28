#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "solveur_linked.h"


LinkedWord* MakeLinkedWord()  //fini, testé
{
    //Sert à créer un LinkedWord, rien de particulier ici
    LinkedWord* word  = (LinkedWord*) malloc(sizeof(LinkedWord));
    word -> value = "";
    word -> next = NULL;
    word -> previous = NULL;
    return word;
}

Dictionary* MakeDictionary(unsigned int wordSize, char* dictionaryName) //fini, testé
{
    //Sert à créer un Dictionnaire et le remplis à partir du fichier texte et du nombre de lettres
    Dictionary* dico = (Dictionary*) malloc(sizeof(Dictionary));
    LinkedWord* word = MakeLinkedWord();
    dico -> firstWord = word;
    LinkedWord* previousWord = word;

    FILE* file = fopen(dictionaryName, "r");    //Ouverture du fichier texte
    char line[256];
    
    fgets(line, sizeof(line), file);    //Lecture du Premier mot
    while(strlen(line)!=wordSize+1)	//On ne lit que les mots de taille wordSize (+1 à cause du \n à la fin)
    {
    	fgets(line, sizeof(line), file);
    }
    line[strcspn(line, "\n")] = 0;  //Enlève les caractères \n à la fin s'il y en a
    word -> value = strdup(line);   //Copie de la valeur du mot


    while(fgets(line, sizeof(line), file))  //Cas de base
    {
		if(strlen(line)==wordSize+1)	//+1 à cause du \n à la fin
		{
			word = MakeLinkedWord();
			line[strcspn(line, "\n")] = 0;
			word -> value = strdup(line);
			word -> previous = previousWord;
			previousWord -> next = word;

			previousWord = word;
		}
    }

    if(strlen(line)==wordSize)	//Dernier mot (pas de +1 après wordSize car pas de \n)
    {
        word = MakeLinkedWord();
        line[strcspn(line, "\n")] = 0;
        word -> value = strdup(line);
        word -> previous = previousWord;
		word -> next = NULL;
        previousWord -> next = word;

        previousWord = word;
    }

    return dico;
}

void PrintDictionary(Dictionary* dico) //Fini, testé
{
    //Affiche les mots du dictionnaire, pas grand chose à dire
    if(dico -> firstWord != NULL)
    {
        LinkedWord* current_word = dico -> firstWord;
        while(current_word -> next != NULL)
        {
            printf("%s\n", current_word -> value);
            current_word = current_word -> next;
        }
        printf("%s\n", current_word->value);
    }
}

void RemoveFromDictionary(LinkedWord* removedWord,Dictionary* dictionary) //fini, testé
{
//Supprime un mot du dictionnaire en raccordant le mot suivant au précédent
    
    //Cas du premier mot du dictionnaire
    if(removedWord == dictionary -> firstWord)
    {
        if(removedWord -> next == NULL)
        {
            dictionary -> firstWord = NULL;
        }
        else
        {
        LinkedWord* newFirst = removedWord -> next;
        newFirst -> previous = NULL;

        dictionary -> firstWord = newFirst;
        }
    }


    //Cas du dernier mot du dictionnaire
    else if(removedWord -> next == NULL)
    {
        LinkedWord* newLast = removedWord -> previous;
        newLast -> next = NULL;
    }

    //Case de base
    else
    {
        LinkedWord* previousWord = removedWord -> previous;
        LinkedWord* nextWord = removedWord -> next;
        previousWord -> next = nextWord;
        nextWord -> previous = previousWord;
    }

    free(removedWord);  //On supprime le mot
}

void RefreshDictionary(Dictionary* possibleSolutions, char* input, LinkedWord* bestWord) //Fini, testé
{
//Supprime les mots qui ne conviennent pas du dictionnaire en raccordant les mots suivants aux précédents
    //Pour chaque mot :
    unsigned int i = 0;
    unsigned int n = strlen(input);
    LinkedWord* word = possibleSolutions->firstWord;
    while(word -> next != NULL) //Tant qu'on est pas à la fin du dico :
    {
		i = 0;
        n = strlen(input);
		LinkedWord* nextWord = NULL;
        while(i < strlen(input))    //Pour chaque lettre du mot :
        {
            if( (input[i]=='0' || input[i]=='1') && (bestWord -> value[i] == word -> value[i]) )  //Si on a une lettre qui ne devrait pas être là (grisée ou orangée)
			{
				if(word -> next != NULL)
				{
					nextWord = word -> next;
				}
                RemoveFromDictionary(word,possibleSolutions);   //On supprime
                break;
            }
            else if (input[i] == '2') //Vert
            {
                if(word->value[i]!=bestWord->value[i])  //Si on a une lettre qui devrait être là mais qui l'est pas :
                {
					if(word -> next != NULL)
					{
	                    nextWord = word -> next;
					}
                    RemoveFromDictionary(word,possibleSolutions);   //On supprime
					break;         
				}
            }
            else if(input[i] == '1') //Orange (il suffit de compter les lettres)
            {
                int wordLetterCount = 0;    //Le nombre de fois cette lettre dans le mot du dictionaire qu'on parcourt
                int bestWordLetterCount = 0;    //Le nombre de fois cette lettre dans le mot en paramètre

                char letter = bestWord -> value[i];
                bool flag = false;
                
                for(unsigned int j=0; j<n; j++)  //Est-ce qu'on est dans le cas où il y a la lettre en orange ET en gris ?
                {
                    if(bestWord -> value[j] == letter && input[j] == '0')
                    {
                        flag = true;    //Si oui on lève un flag
                    }
                }

                if(flag) ///Si il y a letter en gris dans le mot
                {
                    for (unsigned int j=0; j<strlen(bestWord -> value); j++)  //On re-parcourt le mot
                    {
                        if(bestWord -> value[j] == letter && input[j] != '0')     //Seulement si l'input est vert ou orange, si c'est la lettre qu'on cherche
                        {
                            bestWordLetterCount+=1;
                        }
                        if(word -> value[j] == letter)  //Dans tous les cas, si c'est la lettre qu'on cherche
                        {
                            wordLetterCount+=1;
                        }
                    }

                    if(bestWordLetterCount != wordLetterCount)  //Si on a pas le même nombre de lettres
                    {
                        RemoveFromDictionary(word,possibleSolutions);   //On supprime
                        break;
                    }

                }
                else
                {
                    for (unsigned int j=0; j<strlen(bestWord -> value); j++)  //On re-parcourt le mot
                    {
                        if(bestWord -> value[j] == letter && input[j] != '0')    //Seulement si l'input est vert ou orange, si c'est la lettre qu'on cherche
                        {
                            bestWordLetterCount+=1;
                        }
                        if(word -> value[j] == letter)  //Dans tous les cas, si c'est la lettre qu'on cherche
                        {
                            wordLetterCount+=1;
                        }
                    }

                    if(bestWordLetterCount > wordLetterCount)   //Dans ce cas il suffit que le compte soit inférieur égal
                    {
                        RemoveFromDictionary(word,possibleSolutions);
                        break;
                    }
                }
            }
			i = i+1;
        }
		if(nextWord == NULL)
		{
			word = word -> next;
		}
		else
		{
			word = nextWord;
		}
    }
    //Cas du dernier mot du dictionnaire
    i = 0;
    n = strlen(input);
    LinkedWord* nextWord = NULL;
    while(i < strlen(input))    //Pour chaque lettre du mot :
    {
        if( (input[i]=='0' || input[i]=='1') && (bestWord -> value[i] == word -> value[i]) )  //Si on a une lettre qui ne devrait pas être là (grisée ou orangée)
        {
            RemoveFromDictionary(word,possibleSolutions);
            break;
        }
        else if (input[i] == '2') //Vert
        {
            if(word->value[i]!=bestWord->value[i])  //Si on a une lettre qui devrait être là mais qui l'est pas :
            {
                RemoveFromDictionary(word,possibleSolutions);
                break;         
            }
        }
        else if(input[i] == '1') //Orange (il suffit de compter les lettres)
        {
            int wordLetterCount = 0;    //Le nombre de fois cette lettre dans le mot du dictionaire qu'on parcourt
            int bestWordLetterCount = 0;    //Le nombre de fois cette lettre dans le mot en paramètre

            char letter = bestWord -> value[i];
            bool flag = false;
            
            for(unsigned int j=0; j<n; j++)  //Est-ce qu'on est dans le cas où il y a une letter grise ou pas
            {
                if(bestWord -> value[j] == letter && input[j] == '0')
                {
                    flag = true;
                }
            }

            if(flag) ///Si il y a letter en gris dans le mot
            {
                for (unsigned int j=0; j<strlen(bestWord -> value); j++)  //On re-parcourt le mot
                {
                    if(bestWord -> value[j] == letter && input[j] != '0')     //Seulement si l'input est vert ou orange, si c'est la lettre qu'on cherche
                    {
                        bestWordLetterCount+=1;
                    }
                    if(word -> value[j] == letter)  //Dans tous les cas, si c'est la lettre qu'on cherche
                    {
                        wordLetterCount+=1;
                    }
                }

                if(bestWordLetterCount != wordLetterCount)
                {
                    RemoveFromDictionary(word,possibleSolutions);
                    break;
                }

            }
            else
            {
                for (unsigned int j=0; j<strlen(bestWord -> value); j++)  //On re-parcourt le mot
                {
                    if(bestWord -> value[j] == letter && input[j] != '0')    //Seulement si l'input est vert ou orange, si c'est la lettre qu'on cherche
                    {
                        bestWordLetterCount+=1;
                    }
                    if(word -> value[j] == letter)  //Dans tous les cas, si c'est la lettre qu'on cherche
                    {
                        wordLetterCount+=1;
                    }
                }

                if(bestWordLetterCount > wordLetterCount)
                {
                    RemoveFromDictionary(word,possibleSolutions);
                    break;
                }
            }
        }
        i = i+1;
    }
}

/*
float getScore(LinkedWord* inputWord, Dictionary* possibleSolutions, unsigned int wordSize, char* greenLetters, char* greenLettersPositions) //Fini, testé
{
 //Récupère le score d'un mot
    
    float score = 0;    //Score du mot  (Il faut diviser par dicoSize pour avoir le vrai score)
    float dicoSize = 0; //Taille du dico
    LinkedWord* possibleWord = possibleSolutions->firstWord;
    printf("\n mot testé : %s\n", inputWord->value);
    while(possibleWord -> next != NULL) //Pour chaque mot de dictionary
    {
        printf("\n mot en cours : %s",possibleWord->value);
        int previousGreens = 0;
        int newGreens = 0;
        for(unsigned int i=0; i<strlen(possibleWord->value); i++)   //Pour chaque lettre
        {
            if(inputWord -> value[i] == possibleWord -> value[i])   //Si inputWord et possibleWord ont la même lettre à la position i
            {
                bool flag = false;  //flag : est-ce qu'il y a déjà une lettre de inputWord dans greenLetters ? Par défaut : non
                for(unsigned int j=0; j<strlen(greenLetters); j++) //On lit greenLetters pour voir si il y avait déjà la lettre ou pas
                {
                    char i_char = i+'0';

                    if(greenLetters[j] == inputWord -> value[i] && greenLettersPositions[j] == i_char)
                    {
                        flag = true; //Il y a déjà cette lettre dans greenLetters
                    }
                }

                if(flag)
                {
                    previousGreens += 1;
                }
                else
                {
                    newGreens += 1;
                }
            }
        }
        printf("\nscore[i] = %f\n", ( (float) ( previousGreens + 2*newGreens ) ) / ( (float) wordSize ));
        score += ( (float) ( previousGreens + 2*newGreens ) ) / ( (float) wordSize );
        dicoSize += 1;

        possibleWord = possibleWord -> next;
    }
    return( (float) score / (float) dicoSize );
}
*/

float getScore(LinkedWord* inputWord, Dictionary* possibleSolutions, unsigned int wordSize, char* greenLetters, char* greenLettersPositions) //Fini, testé
{
 //Récupère le score d'un mot
    
    float score = 0;    //Score du mot  (Il faut diviser par dicoSize pour avoir le vrai score)
    float dicoSize = 0; //Taille du dico
    LinkedWord* possibleWord = possibleSolutions->firstWord;
    while(possibleWord -> next != NULL) //Pour chaque mot de dictionary
    {
        int greens = 0;
        for(unsigned int i=0; i<strlen(possibleWord->value); i++)   //Pour chaque lettre
        {
            if(inputWord -> value[i] == possibleWord -> value[i])   //Si inputWord et possibleWord ont la même lettre à la position i
            {
                for(unsigned int j=0; j<strlen(greenLetters); j++) //On lit greenLetters pour voir si il y avait déjà la lettre ou pas
                {
                    char i_char = i+'0';

                    if(greenLetters[j] == inputWord -> value[i] && greenLettersPositions[j] == i_char)
                    {
                        greens += 1; //Il y a déjà cette lettre dans greenLetters
                    }
                }
            }
        }
        score += ( (float) ( greens ) ) / ( (float) wordSize );
        dicoSize += 1;

        possibleWord = possibleWord -> next;
    }
    //Cas du dernier
    int greens = 0;
    for(unsigned int i=0; i<strlen(possibleWord->value); i++)   //Pour chaque lettre
    {
        if(inputWord -> value[i] == possibleWord -> value[i])   //Si inputWord et possibleWord ont la même lettre à la position i
        {
            for(unsigned int j=0; j<strlen(greenLetters); j++) //On lit greenLetters pour voir si il y avait déjà la lettre ou pas
            {
                char i_char = i+'0';

                if(greenLetters[j] == inputWord -> value[i] && greenLettersPositions[j] == i_char)
                {
                    greens += 1; //Il y a déjà cette lettre dans greenLetters
                }
            }
        }
    }
    score += ( (float) ( greens ) ) / ( (float) wordSize );
    dicoSize += 1;
    return( (float) score / (float) dicoSize );
}



void getGreenLetters(char* greenLetters, char* greenLettersPosition, char* inputWord, char* inputCode)  //Fini, testé
{
    for(int i=0; i<strlen(inputWord); i++)
    {
        if(inputCode[i] == '2') //Si on a une lettre verte
        {
            if(strlen(greenLetters) == 0)   //Si greenLetters est vide, on ajoute la lettre verte
            {
                greenLetters[0] = inputWord[i]; //On l'ajoute à greenLetters
                greenLettersPosition[0] = i+'0';
            }
            else    //Sinon
            {
                bool flag = false;  //flag : est-ce qu'il y a déjà une lettre de inputWord dans greenLetters ? Par défaut : non
                bool flag2 = false; //flag : est-ce qu'il y a une deuxième lettre verte ? Par défaut non
                for(int j=0; j<strlen(greenLetters); j++)
                {
                    if(inputWord[i] == greenLetters[j]) //Si on a déjà cette lettre verte
                    {
                        flag2 = true;   //On active flag2
                        int greenLettersPositionInt = greenLettersPosition[j] - '0';
                        if(i != greenLettersPositionInt )   //Si on avait déjà cette lettre mais à une position différente
                        {
                            flag = true;    //On active flag
                        }
                    }
                }

                if(flag)    //Si on avait la lettre mais c'était pas la même position
                {
                    greenLetters[strlen(greenLetters)] = inputWord[i];  //On ajoute
                    greenLettersPosition[strlen(greenLettersPosition)] = i+'0';
                }
                if(!flag2)  //Si on avait pas déjà cette lettre verte
                {
                    greenLetters[strlen(greenLetters)] = inputWord[i];  //On l'ajoute à greenLetters
                    greenLettersPosition[strlen(greenLettersPosition)] = i+'0';                    
                }

            }
        }
    }
}

LinkedWord* getBestWord(Dictionary* possibleSolutions, Dictionary* possibleInputs,unsigned int wordSize, char* greenLetters, char* greenLettersPositions) //Fini, à tester
{
    //Récupère le meilleur mot
    //Supprimer les mots ayant un score inférieur à un certain seuil ? J'ai mis 0.1 mais faudra tester d'autres valeurs
    float seuil = 0.1; // par exemple
    LinkedWord* bestWord = possibleInputs -> firstWord;   //De base le meilleur c'est le premier, mais ça changera dans la boucle
    float bestScore = getScore(bestWord, possibleSolutions, wordSize, greenLetters, greenLettersPositions);   //Score associé
    LinkedWord* currentWord = bestWord -> next;
    float currentScore;
    while (currentWord -> next != NULL) //Tant qu'on arrive pas à la fin du dictionnaire :
    {
        currentScore = getScore(currentWord, possibleSolutions, wordSize, greenLetters, greenLettersPositions); //On récupère le score du mot en cours
        if(currentScore<seuil)  //Si son score est trop nul on le supprime
        {
            RemoveFromDictionary(currentWord,possibleInputs);
        }
        else if(currentScore>=bestScore) //Si son score est meilleur que le bestWord, ça devient le bestWord
        {
            bestScore = currentScore;
            bestWord = currentWord;
        }
        currentWord=currentWord -> next;  //On passe au mot suivant
    }
    //Il faut encore vérifier le dernier mot du dictionnaire :
    currentScore = getScore(currentWord, possibleSolutions, wordSize, greenLetters, greenLettersPositions);
    // if(currentScore<seuil)
    // {
    //     RemoveFromDictionary(currentWord,possibleInputs);
    // }
    if(currentScore>=bestScore)
    {
        bestWord = currentWord;
    }

    return bestWord;    //On retourne le meilleur mot
}



char* GetFirstBestWord(Dictionary* possibleInputs, int wordSize)  //Fini, à tester
{
    return "TARIE";
    LinkedWord* bestWord = possibleInputs -> firstWord; //Par défaut, le bestWord est le premier mot du dictionnaire
    Dictionary* possibleSolutions;  //Dictionnaire qu'on va parcourir pour chaque mot
    memcpy(possibleSolutions,possibleInputs,sizeof(Dictionary));    //On copie le dictionnaire
    char greenLetters[256]; //Array qui contiendra les lettres vertes
    char greenLettersPosition[256]; //Array qui contiendra les positions des lettres vertes

    int bestScore = getScore(bestWord, possibleSolutions, wordSize, greenLetters, greenLettersPosition);    //On récupère le score du bestWord
    int currentScore = 0;
    LinkedWord* currentWord = bestWord -> next;
    while(currentWord -> next != NULL)  //Pour chaque mot de possibleInputs :
    {
        //On reset tout
        memset(greenLetters, 0, sizeof(greenLetters));    // greenLetters = ""
        memset(greenLettersPosition, 0, sizeof(greenLettersPosition));

        //On calcule le prochain score
        currentScore = getScore(currentWord, possibleSolutions, wordSize, greenLetters, greenLettersPosition);
        if(currentScore>=bestScore) //On change bestScore/bestWord si on trouve un meilleur score;
        {
            bestScore = currentScore;
            bestWord = currentWord;
        }

        currentWord = currentWord -> next;
    }

    // Cas du dernier mot : on reset tout
    memset(greenLetters, 0, sizeof(greenLetters));    // greenLetters = ""
    memset(greenLettersPosition, 0, sizeof(greenLettersPosition));
    
    //rebelotte
    currentScore = getScore(currentWord, possibleSolutions, wordSize, greenLetters, greenLettersPosition);
    if(currentScore>=bestScore)
    {
        bestScore = currentScore;
        bestWord = currentWord;
    }

    return bestWord;
}


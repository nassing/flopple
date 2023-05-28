#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include "solveur_linked.c"

int wsolf() //Fini, testé
{
    char line[4];
    FILE* file = fopen("wsolf.txt", "r");
    fgets(line, sizeof(line), file);
    fclose(file);
    int lineInt = atoi(line);
    return lineInt;
}

bool isInputCorrect(char* input, int wordleSize)
{
    bool flag = true;   //Par défaut c'est correct
    
    int size = strlen(input);

    if(size!=wordleSize)    //Si c'est pas la bonne taille, c'est pas correct
    {
        flag = false;
    }


    for(int i=0;i<size;i++)
    {
        if(input[i]!='0' && input[i]!='1' && input[i]!='2') //Si le chiffre c'est pas 1,2,3
        {
            flag = false;   //C'est pas correct
        }
    }

    return flag;
}


int main()
{
    char input[256]; //On va supposer qu'il y a aucun mot plus grand que cette taille
    char** inputHistory;    //Historique des inputs
    char* wordleWord;
    int wordleSize;
    wordleSize = wsolf();
    printf("%d",wordleSize);
    Dictionary* possibleInputs = MakeDictionary(wordleSize, "dico.txt");
    Dictionary* possibleSolutions = MakeDictionary(wordleSize, "dico.txt");
    wordleWord = GetFirstBestWord(possibleInputs, wordleSize);
    char greenLetters[256];
    char greenLettersPosition[256];
    printf("\nImportation du fichier 'wsolf.txt' ...");
    printf("\nDictionnaire fran%cais import%c !",135,130);
    printf("\nPr%ct pour r%csoudre votre Wordle du jour ?",136,130);
    printf("\nPour commencer, entrez le mot %s, puis donnez moi les couleurs du Wordle",wordleWord);
    printf("\nRappel: -1 pour quitter.");
    printf("\n> ");
    while(1)
    {
        scanf("%s",input);

        if(strcmp(input,"0") == 0) //Reset
        {
            //memset(inputHistory,0,sizeof(inputHistory))
            printf("\nSolveur remis %c z%cro !",133,130);
            printf("\nPour commencer, entrez le mot %s, puis donnez moi les couleurs du Wordle",wordleWord);
        }

        else if(strcmp(input,"-1") == 0) //Exit
        {
            break;
        }
        else if(isInputCorrect(input,wordleSize))   //Si c'est un input valide
        {   
            //Ajoute les greenLetters
            getGreenLetters(greenLetters, greenLettersPosition, wordleWord, input);
            //ToDo : wordleWord = guessWordleWord(dictionary,input,previousInput);
            wordleWord = getBestWord(possibleSolutions, possibleInputs, wordleSize, greenLetters, greenLettersPosition);
            printf("\nOK, maintenant entrez %s",wordleWord);

        }
        
        else    //Si c'est un input invalide
        {
            printf("\nInput incorrect, veuillez r%cessayer",130);
        }
        
        printf("\nRappel: 0 pour recommencer, -1 pour quitter.");
        printf("\n> ");

    }
    return 0;
}
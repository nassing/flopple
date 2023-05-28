#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include "global.c"

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

char* get_firsrt_best_word(int size, char* file_name)
{
    FILE* file = fopen(file_name, "r");
    char* chaine = malloc(12);
    if (file != NULL)
    {
        while (fgets(chaine, 12, file) != NULL)
        {
            chaine[strcspn(chaine, "\n")] = 0;
            int len = strlen(chaine);
            if (len == size)
            {
                return chaine;
            }
        }
    }
    return "error during process";
}

int main()
{
    char input[256]; //On va supposer qu'il y a aucun mot plus grand que cette taille
    char* wordleWord;
    char* wordleWord1;
    char* wordleWord2;
    History* histo;    //Historique des inputs
    int wordleSize;
    wordleSize = wsolf();
    First_word* dico = createDico("pli07.txt", wordleSize);
    printf("%d",wordleSize);
    wordleWord1 = get_first_best_word(wordleSize, "first_words.txt");
    wordleWord2 = get_first_best_word(wordleSize, "second_words.txt");
    printf("\nImportation du fichier 'wsolf.txt' ...");
    printf("\nDictionnaire fran%cais import%c !",135,130);
    printf("\nPr%ct pour r%csoudre votre Wordle du jour ?",136,130);
    printf("\nPour commencer, entrez le mot %s, puis donnez moi les couleurs du Wordle",wordleWord1);
    printf("\nRappel: -1 pour quitter");
    printf("\n> ");
    while(1)
    {
        int i=0;
        scanf("%s",input);

        if(strcmp(input,"0") == 0) //Reset
        {
            //memset(inputHistory,0,sizeof(inputHistory))
            i = -1;
            printf("\nSolveur remis %c z%cro !",133,130);
            printf("\nPour commencer, entrez le mot %s, puis donnez moi les couleurs du Wordle",wordleWord);
        }

        else if(strcmp(input,"-1") == 0) //Exit
        {
            break;
        }

        else if(isInputCorrect(input,wordleSize) && i==0)   //Si c'est le premier input valide
        {   
            new_entry(histo, wordleWord1, input);
            printf("\nOK, maintenant entrez %s",wordleWord2);
        }

        else if(isInputCorrect(input,wordleSize) && i==1)   //Si c'est le deuxième input valide
        {   
            new_entry(histo, wordleWord2, input);
            wordleWord = bestWord(dico, histo);
            printf("\nOK, maintenant entrez %s",wordleWord);
        }

        else if(isInputCorrect(input,wordleSize) && i>1)   //Si c'est un autre input valide
        {   
            new_entry(histo, wordleWord, input);
            wordleWord = bestWord(dico, histo);
            printf("\nOK, maintenant entrez %s",wordleWord);
        }
        
        else    //Si c'est un input invalide
        {
            printf("\nInput incorrect, veuillez r%cessayer",130);
        }
        
        printf("\nRappel: 0 pour recommencer, -1 pour quitter, -2 pour savoir comment utiliser ce programme");
        printf("\n> ");
        i++;
    }
    return 0;
}
#include "solver.h"

int main()
{
    char input[256]; //On va supposer qu'il y a aucun mot plus grand que cette taille

    dictionary* one_dictionary = begin_game("dico.txt") ;
    printf("\nPrêt pour résoudre votre Wordle du jour ?");

    char* wordleWord = get_patterns_and_openingWord(one_dictionary) ;
    printf("\nPour commencer, entrez le mot %s, puis donnez moi les couleurs du Wordle", wordleWord) ;

    printf("\nRappel: -1 pour quitter, -2 pour savoir comment utiliser ce programme");

    printf("\n> ") ;
    while(1)
    {
        scanf("%s",input);

        if(strcmp(input,"0") == 0) //Reset
        {
            reset_game(one_dictionary) ;
            next_step(one_dictionary, NULL, wordleWord) ;
        }

        else if(strcmp(input,"-1") == 0) //Exit
        {
            quit_game(wordleWord, one_dictionary) ;
            break;
        }

        else if (strcmp(input,"-2") == 0)   //Explications
        {
            printf("\nFlemme d'expliquer un peu");
        }
        
        else if(isInputCorrect(input,one_dictionary->length)) //Si c'est un input valide
        {
            next_step(one_dictionary, input, wordleWord) ;           
        }
        
        else    //Si c'est un input invalide
        {
            printf("\nInput incorrect, veuillez r%cessayer",130);
        }
        
        printf("\nRappel: 0 pour recommencer, -1 pour quitter, -2 pour savoir comment utiliser ce programme");
        printf("\n> ");

    }
    return 0;
}

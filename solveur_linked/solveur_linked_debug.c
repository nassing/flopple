#include <stdlib.h>
#include <stdio.h>
#include "solveur_linked.c"

int main()    //fini mais pas sûr de 2-3 trucs
{
    //Initialisation
    int wordSize = 5;   //Taille des mots, à changer
    Dictionary* possibleInputs = MakeDictionary(wordSize, "dico_test.txt");  //Liste qu'on touchera pas ou peu
    Dictionary* possibleSolutions = (Dictionary*) malloc(sizeof(Dictionary));    //Liste qu'on raccourcit tout le temps
    memcpy(possibleSolutions,possibleInputs,sizeof(Dictionary));
    
    printf("\ndebut");
	printf("(%s) :\n\n",possibleSolutions -> firstWord -> next -> next -> value);
    RefreshDictionary(possibleSolutions, "00100", possibleSolutions -> firstWord -> next -> next);
    printf("fini !\n\n");
    PrintDictionary(possibleSolutions);


    //LinkedWord* bestWord; //Meilleur mot à proposer qu'on change à chaque tour;
    //char** inputHistory; // : liste des inputs joueurs (0,1,2) (On ne le considérera que dans une deuxième version de ce programme)
    //bestWordsHistory : liste des mots proposés par l'algo (On ne le considérera que dans une deuxième version de ce programme)



   return 0;
}

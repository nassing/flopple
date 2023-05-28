#include "solver.h"

bool isInputCorrect(char* input, int wordleSize)
{
    bool flag = true;   //Par défaut c'est correct
    
    int size = strlen(input);

    if(size!=wordleSize)  //Si c'est pas la bonne taille, c'est pas correct
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

dictionary* begin_game(char* fileName)
{
    printf("\nLecture du fichier 'wsolf.txt' et importation du dictionnaire ...") ;
    dictionary* one_dictionary = dictionary_create() ;
    one_dictionary->length = read_wsolf() ;
    one_dictionary->nb_words = get_words_and_nb_words(fileName, one_dictionary->length, one_dictionary->list_words) ;
    one_dictionary->nb_patterns = pow(3, one_dictionary->length) ;

    printf("\nDictionnaire français importé !") ;

    return one_dictionary ;
}

void next_step(dictionary* one_dictionary, char* pattern, char* word)
{
    printf("\nRecherche du mot suivant...") ;
    compute_compatible(one_dictionary, pattern, word) ;
    compute_bestGuess(one_dictionary, word) ;
    printf("\nOk, maintenant entrez %s", word) ; 
}

void quit_game(char* wordleWord, dictionary* one_dictionary)
{
    free(wordleWord) ;
    dictionary_destroy(one_dictionary) ;
}

void reset_game(dictionary* one_dictionary)
{
    list_destroy(one_dictionary->list_words) ;
    one_dictionary->list_words = list_create() ;
    get_words_and_nb_words("dico.txt", one_dictionary->length, one_dictionary->list_words) ;

    printf("\nSolveur remis %c z%cro !",133,130) ;
}

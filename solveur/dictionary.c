#include "dictionary.h"

dictionary* dictionary_create()
{
    dictionary* new_dictionary = calloc(1, sizeof(dictionary)) ;
    new_dictionary->list_words = list_create() ;
    return new_dictionary ;
}

void dictionary_destroy(dictionary* one_dictionary)
{
    list_destroy(one_dictionary->list_words) ;
    list_destroy(one_dictionary->list_patterns) ;
    free(one_dictionary) ;
}

void dictionary_print(dictionary* one_dictionary)
{
    printf("La liste des mots du dictionnaire est : ") ;
    list_print(one_dictionary->list_words) ;
}

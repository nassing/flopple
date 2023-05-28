#ifndef dictionary_H
#define dictionary_H

#include "list_str.h"

typedef struct dictionary dictionary ;
struct dictionary
{
    int length ;

    int nb_words ;
    list_str* list_words ;

    int nb_patterns ;
    list_str* list_patterns ;
} ;

// Une fonction pour initialiser un dictionnaire
dictionary* dictionary_create() ;

// Une fonction pour libérer la mémoire utilisée par un dictionnaire
void dictionary_destroy(dictionary* one_dictionary) ;

// Une fonction pour afficher un dictionaire
void dictionary_print(dictionary* one_dictionary) ;

#endif

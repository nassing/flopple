#ifndef COMPATIBLE_H
#define COMPATIBLE_H

#include "dictionary.h"

// Détermine si le mot otherWord est compatible avec le motif pattern du mot word
int is_compatible(char* pattern, char* word, char* otherWord, int length) ;

// Compte le nombre de mots compatibles avec le motif pattern du mot word parmi les mots utilisés du dictionnaire dictionary
int get_nb_compatible_words(dictionary* one_dictionary, char* pattern, char* word) ;

// Supprime les mots non compatibles du dictionnaire
void compute_compatible(dictionary* one_dictionary, char* pattern, char* word) ;

#endif

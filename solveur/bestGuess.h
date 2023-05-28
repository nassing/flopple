#ifndef BESTWORD_H
#define BESTWORD_H

#include "compatible.h"
#include <math.h>

// Calcule l'entropie E du mot word dans list_words relativement au dictionnaire dictionary, on considère que le mot 
double compute_entropy(dictionary* one_dictionary, char* word) ;

// On renvoie le mot à jouer, ne pas oublier de mettre à jour le dictionnaire pour le tour suivant (avec compatible)
void compute_bestGuess(dictionary* one_dictionary, char* bestWord) ;

#endif

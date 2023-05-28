#ifndef PATTERNS_H
#define PATTERNS_H

#include "list_str.h"
#include <math.h>

// Une fonction auxiliaire pour engendrer les motifs
void aux_compute_patterns(list_str* list_patterns, int n, int nb_patterns, int length) ;

// Une fonction prenant pour renvoyer les 3^length motifs possibles d'un mot de longueur length (attention, list_patterns doit avoir suffisemment de place)
list_str* compute_patterns(int nb_patterns, int length) ;

#endif

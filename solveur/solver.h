#ifndef SOLVER_H
#define SOLVER_H

#include "files.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// Une fonction pour vérifier le format de l'entrée
bool isInputCorrect(char* input, int wordleSize) ;

// Une fonction pour débuter une partie
dictionary* begin_game(char* fileName) ;

// Une fonction pour avancer d'une étape
void next_step(dictionary* one_dictionary, char* pattern, char* word) ;

// Une fonction pour quitter une partie (libérer l'espace)
void quit_game(char* wordleWord, dictionary* one_dictionary) ;

// Une fonction pour recommencer une partie de même longueur de mots
void reset_game(dictionary* one_dictionary) ;

#endif

#ifndef READFILES_H
#define READFILES_H

#include "patterns.h"
#include "bestGuess.h"

// Une fonction pour lire dans wsolf.txt la longueur length des mots à jouer
int read_wsolf() ;

// Une fonction pour trouver le nombre de mots nb_words et la liste des mots de longueur length
int get_words_and_nb_words(char fileName[256], int length, list_str* list_words) ;

// Une fonction pour renvoyer les différentes longueurs de mots
int get_lengths(char fileName[256]) ;

// Une fonction pour changer le contenu de wsolf en length
void update_wsolf(int length) ;

// Une fonction pour insérer la liste des patterns possibles dans un fichier texte
void compute_patterns_and_openingWord_into_txt(dictionary* one_dictionary) ;

// Une fonction pour récupérer la liste des patterns depuis un fichier texte
char* get_patterns_and_openingWord(dictionary* one_dictionary) ;

#endif

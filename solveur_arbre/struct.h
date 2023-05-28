#ifndef __ARCH__H__
#define __ARCH__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//==========================================================================================================================================
//
//                                                    Implémentation des struct
//
//==========================================================================================================================================

typedef struct Dictionary Dictionary ;
struct Dictionary
{
    // La longueur des mots du dictionnaire
    char* word;
    // Un pointeur vers le mot suivant
    Dictionary* next ;
    // Un pointeur vers le mot précédent
    Dictionary* previous ;
} ;

typedef struct First_word First_word;
struct First_word
{
    Dictionary* dico;
};

typedef struct History History ;
struct History
{
    char* word;
    char* pattern;
    History* next;
    History* prev;
};

//==========================================================================================================================================
//
//                                                    Bouboubou fonctions bouboubou
//
//==========================================================================================================================================


#endif
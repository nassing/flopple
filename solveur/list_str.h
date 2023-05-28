#ifndef LIST_STR_H
#define LIST_STR_H

#include <stdbool.h> // pour les booléens
#include <stdlib.h> // pour NULL
#include <stdio.h> // pour print ?
#include <assert.h> // pour assert
#include <string.h> // pour la gestion des strings

typedef struct element_str element_str ;
struct element_str
{
    char* string_value ;
    element_str* next ;
} ;


typedef struct list_str list_str ;
struct list_str
{
    element_str* head ;
} ;

// Une fonction pour créer une liste vide
list_str* list_create() ;

// Une fonction pour tester si une liste est vide
bool list_is_empty(list_str* one_list) ;

// Une fonction pour libérer la mémoire utilisée par une liste
void list_destroy() ;

// Une fonction pour afficher une liste
void list_print(list_str* one_list) ;

// Une fonction pour ajouter un élement au début de la liste
void list_prepend(list_str* one_list, char* one_string) ;

// Une fonction pour renvoyer le premier élément de la liste
char* list_first(list_str* one_list) ;

// Une fonction ajouter un élément à la fin de la liste
void list_append(list_str* one_list, char* one_string) ;

// Une fonction pour renvoyer le dernier élément de la liste ;
char* list_last(list_str* one_list) ;

// Une fonction pour supprimer la première occurence d'un élément de la liste
void list_remove(list_str* one_list, char* one_string) ;

// Une fonction pour supprimer l'élément d'indice index de la liste (on compt le premier à 0)
void list_remove_of_index(list_str* one_list, int index) ;

// Une fonction pour renvoyer l'élément d'indice index dans la liste
char* list_get(list_str* one_list, int index) ;

// Une fonction pour renvoyer l'indice d'un élément de la liste (on renvoie -1 s'il n'est pas présent)
int list_index_of(list_str* one_list, char* one_string) ;

// Une fonction pour renvoyer le nombre d'éléments dans la liste
int list_len(list_str* one_list) ;

#endif

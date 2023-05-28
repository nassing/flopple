#include "list_str.h"

int main()
{
    list_str* one_list = list_create() ;
    assert(list_is_empty(one_list)) ;

    list_prepend(one_list, "MY") ;
    assert(!(list_is_empty(one_list))) ;
    assert(strcmp(list_first(one_list), "MY") == 0) ;

    list_append(one_list, "OLD") ;
    assert(strcmp(list_first(one_list), "MY") == 0) ;
    assert(strcmp(one_list->head->next->string_value, "OLD") == 0) ;

    assert(strcmp(list_last(one_list), "OLD") == 0) ;

    list_prepend(one_list, "DARKNESS") ;
    assert(strcmp(list_first(one_list), "DARKNESS") == 0) ;
    assert(strcmp(list_last(one_list), "OLD") == 0) ;

    list_prepend(one_list, "HELLO") ;
    assert(strcmp(list_first(one_list), "HELLO") == 0) ;
    assert(strcmp(list_last(one_list), "OLD") == 0) ;

    list_append(one_list, "FRIEND") ;
    assert(strcmp(list_last(one_list), "FRIEND") == 0) ;

    list_str* empty_list = list_create() ;
    printf("Test d'affichage de la liste vide : ") ;
    list_print(empty_list) ;
    printf("\n\n") ;

    list_str* list_with_single_element = list_create() ;
    list_append(list_with_single_element, "AA") ;
    printf("Test d'affichage d'une liste à un seul élément [ AA ] : ") ;
    list_print(list_with_single_element) ;
    printf("\n\n") ;

    list_remove(list_with_single_element, "AA") ;
    assert(list_is_empty(list_with_single_element)) ;

    printf("Test de suppression d'un mot dans une liste, doit avoir [ AA ] : ") ;
    list_append(list_with_single_element, "AA") ;
    list_remove(list_with_single_element, "BB") ;
    list_print(list_with_single_element) ;
    printf("\n\n") ;

    list_remove_of_index(list_with_single_element, 0) ;
    assert(list_is_empty(list_with_single_element)) ;

    printf("Test de suppression d'un mot dans une liste à partir d'un indice, doit avoir [ AA ] : ") ;
    list_append(list_with_single_element, "AA") ;
    list_remove_of_index(list_with_single_element, 1) ;
    list_print(list_with_single_element) ;
    printf("\n\n") ;

    printf("Test d'affichage de one_list = [ HELLO, DARKNESS, MY, OLD, FRIEND ] : ") ;
    list_print(one_list) ;
    printf("\n\n") ;

    printf("Test de suppression d'un mot (le deuxième) dans one_list (hors premier et dernier) : " ) ;
    list_remove(one_list, "DARKNESS") ;
    list_print(one_list) ;
    printf("\n\n") ;

    printf("Test de suppression du premier élément de one_list : ") ;
    list_remove(one_list, "HELLO") ;
    list_remove(one_list, "HI") ;
    list_print(one_list) ;
    printf("\n\n") ;

    printf("Test de suppression du dernier élément de one_list : ") ;
    list_remove(one_list, "FRIEND") ;
    list_print(one_list) ;
    printf("\n\n") ;

    printf("Remise à zéro de one_list : ") ;
    list_prepend(one_list, "DARKNESS") ;
    list_prepend(one_list, "HELLO") ;
    list_append(one_list, "FRIEND") ;
    list_print(one_list) ;
    printf("\n\n") ;

    printf("##----- On recommence mais avec la fonction pour supprimer depuis l'indice :-----##\n\n") ;

    printf("Test de suppression d'un mot (le deuxième) dans one_list (hors premier et dernier) : " ) ;
    list_remove_of_index(one_list, 1) ;
    list_remove_of_index(one_list, 10) ;
    list_print(one_list) ;
    printf("\n\n") ;

    printf("Test de suppression du premier élément de one_list : ") ;
    list_remove_of_index(one_list, 0) ;
    list_print(one_list) ;
    printf("\n\n") ;

    printf("Test de suppression du dernier élément de one_list : ") ;
    list_remove_of_index(one_list, 2) ;
    list_print(one_list) ;
    printf("\n\n") ;
    
    printf("Remise à zéro de one_list : ") ;
    list_prepend(one_list, "DARKNESS") ;
    list_prepend(one_list, "HELLO") ;
    list_append(one_list, "FRIEND") ;
    list_print(one_list) ;
    printf("\n\n") ;

    assert(strcmp(list_get(one_list, 0), "HELLO") == 0) ;
    assert(strcmp(list_get(one_list, 1), "DARKNESS") == 0) ;
    assert(strcmp(list_get(one_list, 2), "MY") == 0) ;
    assert(strcmp(list_get(one_list, 3), "OLD") == 0) ;
    assert(strcmp(list_get(one_list, 4), "FRIEND") == 0) ;
    // assert(strcmp(list_get(one_list, 5), "HELLO") == 0) ; // échec

    assert(list_index_of(one_list, "HELLO") == 0) ;
    assert(list_index_of(one_list, "DARKNESS") == 1) ;
    assert(list_index_of(one_list, "MY") == 2) ;
    assert(list_index_of(one_list, "OLD") == 3) ;
    assert(list_index_of(one_list, "FRIEND") == 4) ;
    assert(list_index_of(one_list, "HI") == -1) ;

    list_destroy(list_with_single_element) ;
    list_destroy(empty_list) ;
    list_destroy(one_list) ;

}

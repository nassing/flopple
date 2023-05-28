#include "compatible.h"


int main(void)
{
    // -------- Début test de is_compatible --------

    int length = 5 ;
    assert(is_compatible("22222", "SPEED", "SPEED", length) == 1) ;
    assert(is_compatible("00101", "SPEED", "ABIDE", length) == 1) ;
    assert(is_compatible("00101", "SPEED", "STEAL", length) == 0) ;
    assert(is_compatible("10110", "SPEED", "ERASE", length) == 1) ;
    assert(is_compatible("10110", "SPEED", "STEAL", length) == 0) ;
    assert(is_compatible("20200", "SPEED", "STEAL", length) == 1) ;
    assert(is_compatible("01210", "SPEED", "CREPE", length) == 1) ;
    assert(is_compatible("20220", "SPEED", "STEEL", length) == 1) ;

    // --------- Fin test de is_compatible ---------



    // -------- Début test de getNbCompatibleWords --------

    dictionary* one_dictionary = dictionary_create() ;
    assert(list_is_empty(one_dictionary->list_words)) ;
    one_dictionary->length = 5 ;
    list_prepend(one_dictionary->list_words, "PLEBE") ;
    list_prepend(one_dictionary->list_words, "CREPE") ;
    list_prepend(one_dictionary->list_words, "HELLO") ;
    list_prepend(one_dictionary->list_words, "SPEED") ;

    assert(get_nb_compatible_words(one_dictionary, "01210", "SPEED") == 2) ;

    list_remove_of_index(one_dictionary->list_words, 0) ;
    list_remove_of_index(one_dictionary->list_words, 0) ;
    list_remove_of_index(one_dictionary->list_words, 1) ;
    assert(get_nb_compatible_words(one_dictionary, "01210", "SPEED") == 1) ;

    assert(get_nb_compatible_words(one_dictionary, "20200", "SPEED") == 0) ;

    dictionary_destroy(one_dictionary) ;

    // --------- Fin test de nbCompatibleWords ---------


/*
    // -------- Début test de compatibleWords --------
    printf("#-------------------------------#\n") ;
    printf("#--- Test de compatibleWords ---#\n") ;
    printf("#-------------------------------#\n\n") ;

    char s1[] = "in" ;
    char* w1 = s1 ;
    char s2[] = "on" ;
    char* w2 = s2 ;
    char s3[] = "it" ;
    char* w3 = s3 ;
    char s4[] = "at" ;
    char* w4 = s4 ;
    char s5[] = "no" ;
    char* w5 = s5 ;
    char* t[] = { w1, w2, w3, w4, w5 } ;
    char** list_w = t ;
    dictionary* d = initdictionary(2, 5, list_w) ;

    int patternBis[] = { 0, 0 } ;
    int* p_patternBis = patternBis ;
    dictionary* d_compatible_it = initdictionary(2, 5, list_w) ;
    computeDictOfCompatibleWords(p_patternBis, w1, d_compatible_it) ;
    printf("Doit avoir at :\n") ;
    displaydictionary(d_compatible_it) ;
    printf("\n\n") ;

    dictionary* d_compatible_at = initdictionary(2, 5, list_w) ;
    computeDictOfCompatibleWords(p_patternBis, w4, d_compatible_at) ;
    printf("Doit avoir in, on, no :\n") ;
    displaydictionary(d_compatible_at) ;
    printf("\n\n") ;

    d_compatible_at->list_used[4] = 0 ;
    printf("Doit avoir in, on :\n") ;
    displaydictionary(d_compatible_at) ;
    printf("\n\n") ;
    d_compatible_at->list_used[4] = 1 ;

    freedictionary(d_compatible_it) ;
    freedictionary(d_compatible_at) ;
    freedictionary(d) ;

    // --------- Fin test de compatibleWords ---------
*/
}

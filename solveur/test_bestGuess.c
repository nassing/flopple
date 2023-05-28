#include "bestGuess.h"
#include "patterns.h"

int main(void)
{
    // -------- Début test de entropy --------

    dictionary* one_dictionary = dictionary_create() ;
    one_dictionary->length = 2 ;
    list_prepend(one_dictionary->list_words, "AT") ;
    list_prepend(one_dictionary->list_words, "IT") ;
    list_prepend(one_dictionary->list_words, "ON") ;
    list_prepend(one_dictionary->list_words, "IN") ;
    one_dictionary->nb_words = 4 ;
    
    one_dictionary->nb_patterns = pow(3, one_dictionary->length) ;
    one_dictionary->list_patterns = compute_patterns(one_dictionary->nb_patterns, one_dictionary->length) ;

    double theoricEntropy_in = 2 ; // E = 4*1/4 * log(4)
    double entropy_in = compute_entropy(one_dictionary, "IN") ;

    printf("Doit être %lf : %lf\n\n\n", theoricEntropy_in, entropy_in) ;

    // --------- Fin test de entropy ---------



    // -------- Début test de bestGuess pour le mot suggéré --------

    list_append(one_dictionary->list_words, "NO") ;
    one_dictionary->nb_words++ ;  

    char* bestWord = calloc(1, sizeof(char[one_dictionary->length+1])) ;
    compute_bestGuess(one_dictionary, bestWord) ;
    assert(strcmp(bestWord, "IN") == 0) ;

    compute_compatible(one_dictionary, "01", "IN") ;

    compute_bestGuess(one_dictionary, bestWord) ;
    assert(strcmp(bestWord, "NO") == 0) ;

    
    free(bestWord) ;
    dictionary_destroy(one_dictionary) ;

    // --------- Fin test de bestGuess pour le mot suggéré ---------
}

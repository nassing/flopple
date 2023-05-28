#include "patterns.h"

int main(void)
{
    // -------- Début test de computePatterns --------

    int length = 2 ;
    int nb_patterns = pow(3, length) ;
    list_str* list_patterns = fillWithPatterns(nb_patterns, length) ;
    printf("Doit être [ 00, 01, 02, 10, 11, 12, 20, 21, 22 ] : ") ;
    list_print(list_patterns) ;
    printf("\n\n") ;
    list_destroy(list_patterns) ;

    // --------- Fin test de computePatterns ---------
}

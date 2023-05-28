#include "solver.h"

int main()
{
    for (int i = 3 ; i < 9 ; i++)
    {
        update_wsolf(i) ;

        dictionary* one_dictionary = begin_game("dico.txt") ;
        compute_patterns_and_openingWord_into_txt(one_dictionary) ;
        dictionary_destroy(one_dictionary) ;

    }
}

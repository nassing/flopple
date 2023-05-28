#include "dictionary.h"

int main(void)
{
    dictionary* one_dictionary = dictionary_create() ;
    assert(list_is_empty(one_dictionary->list_words)) ;
    assert(list_is_empty(one_dictionary->list_patterns)) ;

    dictionary_print(one_dictionary) ;
    printf("\n\n") ;

    list_prepend(one_dictionary->list_words, "HELLO") ;
    assert(!(list_is_empty(one_dictionary->list_words))) ;
    dictionary_print(one_dictionary) ;
    printf("\n\n") ;

    list_prepend(one_dictionary->list_words, "WORLD") ;
    assert(!(list_is_empty(one_dictionary->list_words))) ;
    dictionary_print(one_dictionary) ;
    printf("\n\n") ;

    dictionary_destroy(one_dictionary) ;
}

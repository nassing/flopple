#include "patterns.h"

void aux_compute_patterns(list_str* list_patterns, int n, int nb_patterns, int length)
{
    int nb_loops = pow(3, n) ;
    int nb_repetitions = nb_patterns/(3*nb_loops) ;
    
    if (n == length-1)
    {
        element_str* current_element = list_patterns->head ;

        for (int i=0 ; i < nb_patterns ; i++)
        {
            if (i%3 == 0)
            {
                current_element->string_value[n] = '0' ;
                current_element = current_element->next ;
            }
            else if (i%3 == 1)
            {
                current_element->string_value[n] = '1' ;
                current_element = current_element->next ;
            }
            else
            {
                current_element->string_value[n] = '2' ;
                current_element = current_element->next ;
            }
        }
    }

    else
    {
        element_str* current_element = list_patterns->head ;

        for (int i=0 ; i < nb_loops; i++)
        {
            for (int j=0 ; j < nb_repetitions ; j++)
            {
                current_element->string_value[n] = '0' ;
                current_element = current_element->next ;
            }
            for (int j=0 ; j < nb_repetitions ; j++)
            {
                current_element->string_value[n] = '1' ;
                current_element = current_element->next ;
            }
            for (int j=0 ; j < nb_repetitions ; j++)
            {
                current_element->string_value[n] = '2' ;
                current_element = current_element->next ;
            }
        }
        aux_compute_patterns(list_patterns, n+1, nb_patterns, length) ;
    }
}

list_str* compute_patterns(int nb_patterns, int length)
{
    list_str* list_patterns = list_create() ;
    char* one_string = calloc(1, sizeof(char[length+1]));
    for (int i=0 ; i < length ; i++)
    {
        strcat(one_string, "0") ;
    }
    for (int i=0 ; i < nb_patterns ; i++)
    {
        list_prepend(list_patterns, one_string) ;
    }
    free(one_string) ;

    aux_compute_patterns(list_patterns, 0, nb_patterns, length) ;
    return list_patterns ;
}

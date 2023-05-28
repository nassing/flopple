#include "bestGuess.h"

double compute_entropy(dictionary* one_dictionary, char* word)
{
    assert(!list_is_empty(one_dictionary->list_words)) ;

    double E = 0 ;
    element_str* current_pattern = one_dictionary->list_patterns->head ;

    while (current_pattern != NULL)
    {
        int nb_compatible = get_nb_compatible_words(one_dictionary, current_pattern->string_value, word) ;

        double p = (double) nb_compatible / (double) one_dictionary->nb_words ;

        if (p == 0)
        {
            E += p ;
        }
        // Le cas p = 1 n'existe pas, on va le filtrer avant de calculer l'entropie (il n'existe que s'il ne reste qu'un seul mot dans le dictionnaire)
        else
        {
            double I = -log2(p) ;
            E += p*I ;
        }
        current_pattern = current_pattern->next ;
    }

    return E ;
}

void compute_bestGuess(dictionary* one_dictionary, char* bestWord)
{
    assert(!(list_is_empty(one_dictionary->list_words))) ;

    if (one_dictionary->nb_words == 1)
    {
        strcpy(bestWord, one_dictionary->list_words->head->string_value) ;
    }
    else
    {
        double Emax = 0 ;
        int position = 0 ;

        element_str* current_word = one_dictionary->list_words->head ;

        while (current_word != NULL)
        {
            double E = compute_entropy(one_dictionary, current_word->string_value) ;
            
            if (Emax < E)
            {
                Emax = E ;
                strcpy(bestWord, current_word->string_value) ;
            }

            current_word = current_word->next ;
            position++ ;
        }
    }
}

#include "compatible.h"

int is_compatible(char* pattern, char* word, char* otherWord, int length)
{
    // Les lettres grises doivent être exclues
    // Les lettres vertes doivent rester à leur place
    // Les lettres jaunes doivent être partout ailleurs sauf à l’endroit d’origine et aux places de lettres vertes, attention aux lettres multiples
    // Pour gérer les lettres multiples, on utilise une liste de 0 et de 1, de longueur length : liste[i] = 1 si otherWord[k] a déjà été validé (si word[k] est vert et otherWord[k] = word[k] ou bien s’il existe i != k tq word[i] est jaune et otherWord[k] = word[i] et que c’est une association unique)

    // Il faudra libérer l'espace
    int* checked = (int*) calloc(1, length*sizeof(int)) ;
    for (int i=0 ; i < length ; i++)
    {
        checked[i] = 0 ;
    }

    for (int i=0 ; i < length ; i++)
    {
        if (pattern[i] == '2')
        {
            // Si la lettre i de word est verte, on vérifie qu'elle l'est aussi dans otherWord
            if ((word[i] == otherWord[i]) && (checked[i] == 0))
            {
                // Si les deux lettres i sont vertes, on indique que la lettre i de otherWord a été traitée et on continue
                checked[i] = 1 ;
            }
            else
            {
                // Si les deux lettres ne sont pas vertes, otherWord n'est pas compatible
                free(checked) ;
                return 0 ;
            }
        }

        else if (pattern[i] == '1')
        {
            // Si la lettre i de word est orange
            if (word[i] == otherWord[i])
            {
                // Si la lettre i dans word est orange et que la lettre i dans otherWord est verte, otherWord n'est pas compatible
                free(checked) ;
                return 0 ;
            }
            else
            {
                // On va utiiser boolean pour sortir de la boucle si on trouve un k tq k != i et otherWord[k] == word[i]
                // On sait déjà que si otherWord[k] == word[k], k != i
                int boolean = 1 ;
                for (int k=0 ; ((k < length) && (boolean == 1)) ; k++)
                {
                    // Si on atteint la dernière lettre de otherWord qu'elle n'est pas celle attendue, ou bien qu'elle est celle qu'on cherche mais qu'elle a déjà été analysée, otherWord n'est pas compatible
                    if ((k == length-1) && ((otherWord[k] != word[i]) || ((k == length-1) && (otherWord[k] == word[i]) && (checked[k] == 1))))
                    {
                        free(checked) ;
                        return 0 ;
                    }

                    // On vérifie que la lettre n'a pas déjà été analysée pour pouvoir traiter le cas des lettres multiples
                    if ((otherWord[k] == word[i]) && (checked[k] == 0))
                    {
                        checked[k] = 1 ;
                        boolean = 0 ;
                    }
                }
            }
        }
        
        else if (pattern[i] == '0')
        {
            // Si la lettre i de word est grise, on vérifie qu'elle n'apparait pas dans otherWord sans être analysée
            for (int k=0 ; k < length ; k++)
            {
                // Si elle apparait dans otherWord, il faut qu'elle soit déjà analysée (pour traiter le cas des lettres multiples)
                if ((otherWord[k] == word[i]) && (checked[k] == 0))
                {
                    free(checked) ;
                    return 0 ;
                }
            }
        }
    }
    free(checked) ;
    return 1 ;
}

int get_nb_compatible_words(dictionary* one_dictionary, char* pattern, char* word)
{
    assert(one_dictionary->list_words != NULL) ;

    int N = 0 ;
    element_str* current_element = one_dictionary->list_words->head ;
    
    while (current_element != NULL)
    {
        if (is_compatible(pattern, word, current_element->string_value, one_dictionary->length) == 1)
        {
            N++ ;
        }
        current_element = current_element->next ;
    }
    return N ;
}

void compute_compatible(dictionary* one_dictionary, char* pattern, char* word)
{
    assert(one_dictionary->list_words != NULL) ;
    assert(!(list_is_empty(one_dictionary->list_words))) ; // il y a au moins un élément

    element_str* previous_element = one_dictionary->list_words->head ;
    element_str* current_element = previous_element->next ;
    element_str* tmp = NULL ;

    while ((previous_element != NULL) && (!(is_compatible(pattern, word, previous_element->string_value, one_dictionary->length))))
    {
        tmp = previous_element ;

        one_dictionary->list_words->head = current_element ;
        previous_element = current_element ;
        if (previous_element != NULL)
        {
            current_element = previous_element->next ;
        }
        else
        {
            current_element = NULL ;
        }

        free(tmp->string_value) ;
        free(tmp) ;

        one_dictionary->nb_words-- ;
    }
    while (current_element != NULL)
    {
        if (!(is_compatible(pattern, word, current_element->string_value, one_dictionary->length)))
        {
            tmp = current_element ;

            previous_element->next = current_element->next ;
            current_element = previous_element->next ;

            free(tmp->string_value) ;
            free(tmp) ;

            one_dictionary->nb_words-- ;
        }
        else
        {
            previous_element = current_element ;
            current_element = previous_element->next ;
        }
    }
}

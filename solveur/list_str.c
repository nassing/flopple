#include "list_str.h"

list_str* list_create()
{
    list_str* new_list = calloc(1, sizeof(list_str)) ;

    return new_list ;
}

bool list_is_empty(list_str* one_list)
{
    assert(one_list != NULL) ;

    return one_list->head == NULL ;
}

void list_destroy(list_str* one_list)
{
    assert(one_list != NULL) ;

    element_str* current = one_list->head ;
    element_str* tmp = NULL ;
    while (current != NULL)
    {
        tmp = current ;
        current = current->next ;
        free(tmp->string_value) ;
        free(tmp) ;
    }
    free(one_list) ;
}

void list_print(list_str* one_list)
{
    assert(one_list != NULL) ;

    printf("[ ") ;
    element_str* current_element = one_list->head ;
    if (current_element != NULL)
    {
        printf("%s", current_element->string_value) ;
        current_element = current_element->next ;
    }
    while (current_element != NULL)
    {
        printf(", %s", current_element->string_value) ;
        current_element = current_element->next ;
    }
    printf(" ]") ;
}

void list_prepend(list_str* one_list, char* one_string)
{
    assert(one_list != NULL) ;

    // On crée l'élément qui va être rajouté
    element_str* new_element = calloc(1, sizeof(element_str)) ;
    
    new_element->string_value = calloc(1, sizeof(char[strlen(one_string) + 1])) ;
    strcpy(new_element->string_value, one_string) ;
    new_element->next = one_list->head ;

    // On l'ajoute au début
    one_list->head = new_element ;
}

char* list_first(list_str* one_list)
{
    assert(one_list != NULL);
    assert(!list_is_empty(one_list));

    return one_list->head->string_value ;
}

void list_append(list_str* one_list, char* one_string)
{
    assert(one_list != NULL) ;

    // On crée l'élément qui va être rajouté
    element_str* new_element = calloc(1, sizeof(element_str)) ;

    new_element->string_value = calloc(1, sizeof(char[strlen(one_string) + 1])) ;
    strcpy(new_element->string_value, one_string) ;
    new_element->next = NULL ;

    // On l'ajoute à la fin
    element_str* current_element = one_list->head ;
    
    // Si la liste est vide, on l'ajoute au début
    if (current_element == NULL)
    {
        one_list->head = new_element ;
    }

    // Sinon, on parcourt la liste jusqu'à la fin pour ajouter le nouvel élément
    else
    {
        while (current_element->next != NULL)
        {
            current_element = current_element->next ;
        }
        current_element->next = new_element ;
    }
}

char* list_last(list_str* one_list)
{
    assert(one_list != NULL) ;
    assert(!(list_is_empty(one_list))) ;

    // On parcourt la liste jusqu'à la fin
    element_str* current_element = one_list->head ;

    while ((current_element != NULL) && (current_element->next !=NULL))
    {
        current_element = current_element->next ;
    }

    return current_element->string_value ;
}

void list_remove(list_str* one_list, char* one_string)
{
    assert(one_list != NULL) ;
    assert(!(list_is_empty(one_list))) ;

    // On parcourt la liste jusqu'à trouver l'élément
    element_str* previous_element = one_list->head ;
    element_str* current_element = one_list->head->next ;
    if (current_element == NULL)
    {
        if (strcmp(previous_element->string_value, one_string) == 0)
        {
            one_list->head = current_element ;
            free(previous_element->string_value) ;
            free(previous_element) ;
        }
    }
    else
    {
        if (strcmp(previous_element->string_value, one_string) == 0)
        {
            one_list->head = current_element ;
            free(previous_element->string_value) ;
            free(previous_element) ;
        }
        while ((current_element != NULL) && (current_element->next !=NULL) && (strcmp(current_element->string_value, one_string) != 0))
        {
            previous_element = current_element ;
            current_element = current_element->next ;
        }
        if (strcmp(current_element->string_value, one_string) == 0)
        {
            previous_element->next = current_element->next ;
            free(current_element->string_value) ;
            free(current_element) ;
        }
    }
}

void list_remove_of_index(list_str* one_list, int index)
{
    assert(one_list != NULL) ;
    assert(!(list_is_empty(one_list))) ;

    // On parcourt la liste jusqu'à atteindre le bon indice
    element_str* previous_element = one_list->head ;
    element_str* current_element = one_list->head->next ;
    if (current_element == NULL)
    {
        if (index == 0)
        {
            one_list->head = current_element ;
            free(previous_element->string_value) ;
            free(previous_element) ;
        }
    }
    else
    {
        if (index == 0)
        {
            one_list->head = current_element ;
            free(previous_element->string_value) ;
            free(previous_element) ;
        }

        int position = 1 ;

        while ((current_element != NULL) && (current_element->next !=NULL) && (position != index))
        {
            previous_element = current_element ;
            current_element = current_element->next ;
            position++ ;
        }

        if (position == index)
        {
            previous_element->next = current_element->next ;
            free(current_element->string_value) ;
            free(current_element) ;
        }
    }
}

char* list_get(list_str* one_list, int index)
{
    assert(one_list != NULL) ;
    assert(!(list_is_empty(one_list))) ;

    int position = 0 ;
    element_str* current_element = one_list->head ;

    while ((position != index) && (current_element->next != NULL))
    {
        current_element = current_element->next ;
        position++ ;
    }

    // Dans le cas où l'indice est négatif ou trop grand
    assert(position == index) ;

    return current_element->string_value ;
}

int list_index_of(list_str* one_list, char* one_string)
{
    assert(one_list != NULL) ;
    assert(!(list_is_empty(one_list))) ;

    int position = 0 ;
    element_str* current_element = one_list->head ;

    while ((current_element->next != NULL) && (strcmp(current_element->string_value, one_string)))
    {
        current_element = current_element->next ;
        position++ ;
    }

    if (strcmp(current_element->string_value, one_string) == 0)
    {
        return position ;
    }
    else
    {
        return -1 ;
    }
}

int list_len(list_str* one_list)
{
    assert(one_list != NULL) ;

    int length = 0 ;
    element_str* current_element = one_list->head ;
    
    while (current_element != NULL)
    {
        length++ ;
        current_element = current_element->next ;
    }
    return length ;
}

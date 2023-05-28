#include "files.h"

int read_wsolf()
{
    FILE* file = NULL;
    file = fopen("wsolf.txt", "r+");

    // On lit la longueur du mot en considérant qu'il s'agit de la première ligne du fichier
    char line[256] ;
    fgets(line, sizeof(line), file) ;
    char** p_end = NULL ;
    int length = (int) strtol(line, p_end, 10) ;
    fclose(file) ;

    return length ;
}

int get_words_and_nb_words(char fileName[256], int length, list_str* list_words)
{
    int nb_words = 0 ;
    FILE* file = NULL ;
    file = fopen(fileName, "r+") ;

    char word[256] = "" ;
    while (fgets(word, 256, file) != NULL)
    {
        if ((int) strlen(word) == length+1)
        {
            word[strcspn(word, "\n")] = 0;
            list_prepend(list_words, word) ;
            nb_words++ ;
        }
    }
    return nb_words ;
}

void update_wsolf(int length)
{
    FILE* file = NULL ;
    file = fopen("wsolf.txt", "w+") ;

    char str[32] ;
    sprintf(str, "%d", length) ;
    if (length < 10)
    {
        fwrite(str, 1, 1, file) ;
    }
    else
    {
        fwrite(str, 1, 2, file) ;
    }
    fwrite("\n", 1, 1, file) ;

    fclose(file) ;
}

void compute_patterns_and_openingWord_into_txt(dictionary* one_dictionary)
{
    char str[32] ;
    sprintf(str, "%d", one_dictionary->length) ;
    char fileName[64] = "patterns_of_length" ;
    strcat(fileName, str) ;
    int nb_patterns = pow(3, one_dictionary->length) ;

    one_dictionary->list_patterns = compute_patterns(nb_patterns, one_dictionary->length) ;

    FILE* file = NULL ;
    file = fopen(fileName, "w+") ;

    char* openingWord = (char*) calloc(1, sizeof(char[one_dictionary->length+6])) ;
    compute_bestGuess(one_dictionary, openingWord) ;

    int i = 0 ;

    element_str* current_pattern = one_dictionary->list_patterns->head ;
    while (current_pattern != NULL)
    {
        if (i == 0)
        {
            fwrite(openingWord, 1, one_dictionary->length, file) ;
            fwrite("\n", 1, 1, file) ;
            i++ ;
        }
        else
        {
            char string[64] ;
            strcpy(string, current_pattern->string_value) ;
            fwrite(string, 1, one_dictionary->length, file) ;
            fwrite("\n", 1, 1, file) ;
            current_pattern = current_pattern->next ;
        }
    }

    fclose(file) ;

    free(openingWord) ;
    //list_destroy(one_dictionary->list_patterns) ;
}

char* get_patterns_and_openingWord(dictionary* one_dictionary)
{
    char str[32] ;
    sprintf(str, "%d", one_dictionary->length) ;
    char fileName[64] = "patterns_of_length" ;
    strcat(fileName, str) ;

    FILE* file = NULL ;
    file = fopen(fileName, "r+") ;

    char line[one_dictionary->length+1] ;
    list_str* list_patterns = list_create() ;

    char* openingWord = (char*) calloc(1, sizeof(char[one_dictionary->length+1])) ;

    int i = 0 ;
    while (fgets(line, sizeof(line), file))
    {
        if (strcmp(line,"\n") != 0)
        {
            line[strcspn(line, "\n")] = 0 ;
            if (i == 0)
            {
                strcpy(openingWord, line) ;
                i++ ;
            }
            else
            {
                list_prepend(list_patterns, line) ;
            }
        }
    }

    one_dictionary->list_patterns = list_patterns ;

    fclose(file) ;

    return openingWord ;
}

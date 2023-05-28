#include "solveur.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/*
int test_returnBigrammes()
{
    First_frequency* shee2 = returnBigrammes( "tui.txt", "00112", "AEHET");
    Frequency* shee = shee2->freq;

    while (shee->prev_elmt != NULL)
    {
        shee = shee->prev_elmt;
    }
    
    while (shee->next_elmt != NULL)
    {
        printf("test return: %s\n %f\n",shee->elemt, shee->freq);
        shee = shee->next_elmt;
    }
    return 0;
}

int test_bestFrequencies()
{
    First_word* dico = createDico("pli07.txt", 5);
    First_frequency* freq = returnBigrammes("frequences_bigrammes.txt", "00000", "LOUIX");


    Node* node = malloc(sizeof(Node));
    node->length = 2;
    node->letters = "OU";
    node->pattern = "22";
    node->position = 1;

    First_frequency* filtered_freq = bestFrequencies(dico, freq, node);  
    Frequency* f_freq = filtered_freq->freq;

    while (f_freq->next_elmt != NULL)
    {
        printf("test best :%s \n",f_freq->elemt);
        f_freq = f_freq->next_elmt;
    }
    return 0;
}
int bibi_tests()
{
    test_bestFrequencies();
    test_returnBigrammes();

    return 0;
}
*/
int main(){

    //printf("%f\n",getFrequency("AA"));
    //printf("%f\n",getFrequency("NS"));
    //printf("%s,%f",FrequencyOfconcatElements("A", "B")->elemt,FrequencyOfconcatElements("A", "B")->freq);
    Frequency* list1 = malloc(sizeof(Frequency));
    Frequency* list2= malloc(sizeof(Frequency));
    Frequency* next1 = malloc(sizeof(Frequency));
    Frequency* next2= malloc(sizeof(Frequency));
    //Frequency* next_next2= malloc(sizeof(Frequency));
    list1->next_elmt=next1;
    list2->next_elmt=next2;
    next1->prev_elmt=list1;
    next2->prev_elmt=list2;
    //next2->next_elmt=next_next2;
    //next_next2->prev_elmt=next2;
    list1->elemt="A";
    list1->freq=0.0815;
    next1->elemt="BS";
    next1->freq=0.00275188;
    list2->elemt="CU";
    list2->freq=0.0186671;
    next2->elemt="B";
    next2->freq=0.097;
    //next_next2->elemt="XY";
    //next_next2->freq=0,4;
    //printf("%d\n", length_freq(list2));
    Frequency* frequ = computeFrequencies(beginningFrequency(list1), beginningFrequency(list2));
    beginningFrequency(frequ);
    //printf("%s\n",frequ->elemt);
    for (int i=0; i<length_freq(frequ) ; i++){
        printf("%s,%f",frequ->elemt, frequ->freq);
        frequ=frequ->next_elmt;
    } 
    freeFrequency(list1);
    freeFrequency(list2);
    
    //Frequency* f = FrequencyOfconcatElements("A", "A");
    //printf("%s, %f", f->elemt, f->freq);
    //bibi_tests();
    return 0;
}



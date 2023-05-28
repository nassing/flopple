#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "solveur.h"
#include <ctype.h>


double globalFrequency(double f1, double f2, double f3) //marche
{
    return (f1+f2+f3)/3;
}

double getFrequency(char* element){ //marche

    FILE* fichier;
    if (strlen(element)==2)
    {
        fichier = fopen("frequences_bigrammes.txt", "r");
    }
    else if (strlen(element)==1)
    {
        fichier = fopen("frequences_lettres.txt", "r");
    }
    
    char buf[100] = "";
    double frequency;
    bool flag = false;
    if (fichier != NULL)
    {
        while (fgets(buf, 100, fichier) != NULL) {
            buf[strcspn(buf,"\n")]=0;
            if (buf[0]==element[0] && buf[1]==element[1])
            {
                flag=true;
            }
            else if (flag==true){
                frequency = toDouble(buf);
                return frequency;
            }
        }
    }
}

void removeFrequency(First_frequency* first, Frequency* freq)
{  
    if (freq == first->freq)
    {
        Frequency* next = malloc(sizeof(Frequency));
        next = freq->next_elmt;
        first->freq = next;

        return;
    }
    else if (freq->next_elmt == NULL)
    {
        Frequency* prev = malloc(sizeof(Frequency));
        prev = freq->prev_elmt;
        prev->next_elmt = NULL;

        return;
    }
    else
    {
        Frequency* next = freq->next_elmt;
        Frequency* prev = freq->prev_elmt;

        next->prev_elmt = prev;
        prev->next_elmt = next;

        return;
    }
}

bool bibi_compatible(char* chaine, char* pattern, char* word)
{
    int length = strlen(word);
    int l_chaine = strlen(chaine);
    for(int i = 0; i < l_chaine; i++)
    {
        for(int j = 0; j < length; j++)
        {
            if( chaine[i]==word[j])
            {
                if(pattern[j] == '0')
                {
                    char letter = chaine[i];
                    int count = 0;
                    int count2 = 0;
                    int count3 = 0;
                    for(int k = 0; k<length; k++)
                    {
                        count2 = 0;
                        if(word[k] == letter)
                        {
                            if( pattern[k] != '0')
                            { count++; }
                            else
                            { count3++; }
                        }
                        for(int n = 0; n<2; n++)
                        {
                            if(chaine[n] == letter)
                            { count2++; }
                        }
                    }
                    if( count2>count && count3 != 0)
                    { return false;}
                }  
            }
        }
    }
    return true;
}

Frequency* createFreq()
{
    Frequency* list = malloc(sizeof(Frequency));
    list->elemt = calloc(1, sizeof(char[3]));
    list->freq = 0;
    return list;
}

First_frequency* returnBigrammes(char* fichier, char* pattern, char* word)
{
    FILE* file = fopen(fichier, "r");
    char* chaine = malloc(sizeof(char[52]));
    First_frequency* first = malloc(sizeof(First_frequency));
    Frequency* list = createFreq();
    first->freq = list;
    if (file != NULL)
    {
        int i=0;
        while (fgets(chaine, 52, file) != NULL)
        {
            if ( i%2 == 0 && bibi_compatible(chaine, pattern, word))
            {
                chaine[strcspn(chaine, "\n")] = 0;
                list->elemt = strdup(chaine);
            }
            else if ( i%2 == 1 && list->elemt != NULL)
            {
                double flo = toDouble(chaine);
                list->freq = flo;
                Frequency* next = createFreq();
                
                next->prev_elmt = list;
                list->next_elmt = next;
                list = next;
            }
            i++;
        }
    }
    return first;
}




Frequency* FrequencyOfconcatElements(char* elmt1, char* elmt2){ //marche
    char* last1 = elmt1+strlen(elmt1)-1;
    //printf("%s\n",last1);
    char* first2 = &elmt2[0];
    //printf("%s\n", first2);
    Frequency* frequency = calloc(sizeof(Frequency),1);
    char* bigramme = malloc(sizeof(char[2]));
    bigramme[0]=*last1;
    bigramme[1]=*first2;
    frequency->elemt=bigramme;
    frequency->freq = getFrequency(bigramme);
    return frequency;

}


//Dictionary* sortDico(Dictionary* dico, char* pattern, char* word);

First_frequency* bestFrequencies(First_word* first_dico, First_frequency* first_freq, Node* node)
{
    Frequency* freq = first_freq->freq;

    while(freq->next_elmt != NULL)
    {
        Dictionary* dico = first_dico->dico;
        bool comp = false;
        while (dico->next != NULL && comp == false)
        {
            if(access_chunk(dico->word, node->position, node->length) == node->letters)
            { comp = true; }
            dico = dico->next;
        }
        if ( !comp )
        {
            //printf("%s \n", freq->elemt);
            removeFrequency(first_freq, freq); 
        }
        freq = freq->next_elmt;
    }
    while (freq->prev_elmt != NULL)
    {
        freq = freq->prev_elmt;
    }
    first_freq->freq = freq;
    return first_freq;
}

Frequency* computeFrequencies(Frequency* list1, Frequency* list2){
    assert(length_freq(list1)==length_freq(list2));
    Frequency* computeFrequencies = malloc(sizeof(Frequency));
    
    //for (int i=0; i<length_freq(list1); i++){
    while(list1->next_elmt != NULL){
        //for (int j=0; i<length_freq(list2); j++){
        while (list2->next_elmt != NULL){        
            char elem1[12];
            char elem2[12];
            char* elemCat;
            char* value = malloc(sizeof(char[12]));
            strcpy( elem1, list1->elemt);
            strcpy( elem2, list2->elemt);
            elemCat = strcat(elem1, elem2);
            strcpy( value, elemCat);
            computeFrequencies->elemt = value;
            computeFrequencies->freq=globalFrequency(list1->freq,list2->freq, FrequencyOfconcatElements(&((list1->elemt)[strlen(list1->elemt)-1]),&((list2->elemt)[0]))->freq);
            Frequency* f=malloc(sizeof(Frequency));
            computeFrequencies->next_elmt=f;
            f->prev_elmt=computeFrequencies;
            computeFrequencies=computeFrequencies->next_elmt;
            list2=list2->next_elmt;
        }
        char elem1[12];
        char elem2[12];
        char* elemCat;
        char* value = malloc(sizeof(char[12]));
        strcpy( elem1, list1->elemt);
        strcpy( elem2, list2->elemt);
        elemCat = strcat(elem1, elem2);
        strcpy( value, elemCat);
        computeFrequencies->elemt = value;
        computeFrequencies->freq=globalFrequency(list1->freq,list2->freq, FrequencyOfconcatElements(&((list1->elemt)[strlen(list1->elemt)-1]),&((list2->elemt)[0]))->freq);
        Frequency* f=malloc(sizeof(Frequency));
        computeFrequencies->next_elmt=f;
        f->prev_elmt=computeFrequencies;
        computeFrequencies=computeFrequencies->next_elmt;
        list2 = beginningFrequency(list2);
        list1=list1->next_elmt;
    }
    while (list2->next_elmt != NULL){        
        char elem1[12];
        char elem2[12];
        char* elemCat;
        char* value = malloc(sizeof(char[12]));
        strcpy( elem1, list1->elemt);
        strcpy( elem2, list2->elemt);
        elemCat = strcat(elem1, elem2);
        strcpy( value, elemCat);
        computeFrequencies->elemt = value;
        computeFrequencies->freq=globalFrequency(list1->freq,list2->freq, FrequencyOfconcatElements(&((list1->elemt)[strlen(list1->elemt)-1]),&((list2->elemt)[0]))->freq);
        Frequency* f=malloc(sizeof(Frequency));
        computeFrequencies->next_elmt=f;
        f->prev_elmt=computeFrequencies;
        computeFrequencies=computeFrequencies->next_elmt;
        list2=list2->next_elmt;
        }
    char elem1[12];
    char elem2[12];
    char* elemCat;
    char* value = malloc(sizeof(char[12]));
    strcpy( elem1, list1->elemt);
    strcpy( elem2, list2->elemt);
    elemCat = strcat(elem1, elem2);
    strcpy( value, elemCat);
    computeFrequencies->elemt = value;
    computeFrequencies->freq=globalFrequency(list1->freq,list2->freq, FrequencyOfconcatElements(&((list1->elemt)[strlen(list1->elemt)-1]),&((list2->elemt)[0]))->freq);
    Frequency* f=malloc(sizeof(Frequency));
    computeFrequencies->next_elmt=f;
    f->prev_elmt=computeFrequencies;
    computeFrequencies=computeFrequencies->next_elmt;
    computeFrequencies = beginningFrequency(computeFrequencies);
    return computeFrequencies;
};


//doit renvoyer les meilleurs bigrammes qui sont dans le dico

/*
char* compute(Tree* tree, Dictionary* dico){
    Dictionary* sorted_dictionary = sortDico(dico, tree->node->pattern, tree->node->letters);
    Frequency* bigrammes = returnBigrammes("frequences_bigrammes.txt",  tree->node->pattern, tree->node->letters);
    Frequency* lettres = returnBigrammes("frequences_lettres.txt",  tree->node->pattern, tree->node->letters);
    Node* racine = tree->node;
    Frequency* left = compute_rec(tree->tleft, sorted_dictionary, bigrammes, lettres);
    Frequency* right = compute_rec(tree->tright, sorted_dictionary, bigrammes, lettres);
    left = beginningFrequency(left);
    while (left->next_elmt != NULL){
        left->elemt=strcat(left->elemt, racine->letters);
        left=left->next_elmt;
    }
    return computeFrequencies(beginningFrequency(left), beginningFrequency(right));
}

Frequency* compute_rec(Tree* tree, Dictionary* dico, Frequency* bigrammes, Frequency* lettres){
    
    
    Node* racine = tree->node;
    int length = racine->length;
    Tree* tleft = tree->tleft;
    Tree* tright = tree->tright;

    if (length ==4 || length ==3)                                                       
    {
        
        //if (tleft->node->length==2)
        //{
        Frequency* lfrequencies =  bestFrequencies(dico, bigrammes, tleft->node);
        Frequency* rfrequencies;
        //}
        if (tright->node->length==1)
        {
            rfrequencies = bestFrequencies(dico, lettres, tleft->node);
        }
        else if (tright->node->length==2)
        {
            rfrequencies = bestFrequencies(dico, bigrammes, tleft->node);
        }

        Frequency* globalfrequencies = computeFrequencies(lfrequencies, rfrequencies);

        bestFrequencies(dico, globalfrequencies, tree->node);
    }
    else 
    {
        return beginningFrequency(bestFrequencies(dico,computeFrequencies(compute_rec(tleft,dico,bigrammes,lettres),compute_rec(tright,dico,bigrammes,lettres)),tree->node));
        //return strcat(strcat(compute_rec(tree->tleft, dico, bigrammes, lettres),racine->letters),compute_rec(tree->tright, dico, bigrammes, lettres)); 
    }
}

*/

#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include "architecture.c"

double toDouble(char* str);

Frequency* FrequencyOfconcatElements(char* elmt1, char* elmt2);

char* highestFrequency (int length, char** table, int number);

bool charFits(char* chaine, int position); //on retrouve le node correspondant avec la position

double getFrequency(char* chaine);

double globalFrequency(double f1, double f2, double f3);

First_frequency* returnBigrammes(char* fichier, char* pattern, char* word);

Dictionary* sortDico(Dictionary* dico, char* pattern, char* word);

First_frequency* bestFrequencies(First_word* dico, First_frequency* freq, Node* node);

Frequency* compute_rec(Tree* tree, Dictionary* dico, Frequency* bigrammes, Frequency* lettres);

char* compute(Tree* tree, Dictionary* dico);


//Frequency* returnBigrammes(char* fichier, char* pattern);




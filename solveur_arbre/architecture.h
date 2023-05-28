#ifndef __ARCH__H__
#define __ARCH__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*--------------------------------------------------------------------------------------------------------------------------------------------------------*/


//==========================================================================================================================================
//
//                                                    Structure des dictionnaires
//
//==========================================================================================================================================


typedef struct Dictionary Dictionary ;
struct Dictionary
{
    // La longueur des mots du dictionnaire
    char* word;
    // Un pointeur vers le mot suivant
    Dictionary* next ;
    // Un pointeur vers le mot précédent
    Dictionary* previous ;
} ;

typedef struct First_word First_word;
struct First_word
{
    Dictionary* dico;
};

typedef struct History History ;
struct History
{
    char* word;
    char* pattern;
    History* next;
    History* prev;
};

History* last_word(History* entered_word);
//==========================================================================================================================================
//
//                                                    Manipulation des dictionnaires
//
//==========================================================================================================================================





//==========================================================================================================================================
//
//                                                    Outils de diminution des dictionnaires
//
//==========================================================================================================================================






//==========================================================================================================================================

//==========================================================================================================================================
//
//                                                    Manipulation des chaînes de caractères
//
//==========================================================================================================================================

// renvoie une sous-chaîne en fonction de sa position et sa longueur
char* access_chunk(char* chain, int index, int length);

// renvoie si la chaîne est de longueur paire
bool isEven(char* element);

//==========================================================================================================================================
//
//                                                    Structure d'un noeud
//
//==========================================================================================================================================
typedef struct Node Node;
struct Node
{
	int length;
	int position;
    char* letters;  
	char* pattern;
};

Node* new_node(int length, int position, char* letters, char* pattern);

//==========================================================================================================================================
//
//                                                    Structure d'un arbre
//
//==========================================================================================================================================

typedef struct Tree Tree;
struct Tree
{
	Node* node;
	Tree* tleft;
	Tree* tright;
	Tree* parent;
};


//==========================================================================================================================================
//
//                                                    Manipulation des arbres
//
//==========================================================================================================================================

Tree* createTree(char* mot, char* pattern);

Tree* beginTree(Node* racine, char* mot, char* pattern);

//construit l'arbre à partir d'une chaîne de caractères
void buildTree(Tree* beginTree);

//affichage de l'arbre en préfixe
void print_tree_prefix(Tree *tr);

// compte le nombre de noeuds dans l'arbre
int count_tree_nodes(Tree *tr);

//accède à un noeud de l'arbre
Node* accessNode(Tree* tree, int pos, int length); //pos correspond à la position de la chaine dans le mot

// supprime un arbre
void delete_tree(Tree* tree);

Tree* new_tree( Node* node);



//==========================================================================================================================================
//
//                                                    Structure d'un tableau de fréquences
//
//==========================================================================================================================================

typedef struct Frequency Frequency;
struct Frequency
{
    char* elemt;
	double freq;
    Frequency* next_elmt;
    Frequency* prev_elmt;
};

typedef struct First_frequency First_frequency;
struct First_frequency
{
    Frequency* freq;
};

void freeFrequency(Frequency* freq);

Frequency* beginningFrequency(Frequency* freq);

Frequency* sortFrequenciesdsc(Frequency* list);

int length_freq(Frequency* list);

Frequency* new_Frequency();

#endif

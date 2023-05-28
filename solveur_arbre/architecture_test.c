#include "architecture.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/*
typedef struct testW testW;
struct testW
{
    char* word;
    char* try_word;
    char* pattern;
    bool isOK;
    testW* next;
    testW* prev;
};

testW* add_new_test_word(testW* list, char* pattern, char* word, char* try_word, bool isOK)
{
    testW* new_word;
    new_word = malloc(sizeof(testW));

    new_word->isOK = isOK;
    new_word->pattern = pattern;
    new_word->try_word = try_word;
    new_word->word = word;
    new_word->prev = list;
    list->next = new_word;
    
    return list->next;
}

int isOK()
{
    testW* list;
    list = malloc(sizeof(testW));

    list->try_word = "TARIE";
    list->word = "PUMBA";
    list->pattern = "00120";
    list->prev = NULL;
    list->isOK = false;
    list->next = NULL;

    list = add_new_test_word(list, "01120", "RATTS", "SHEEE", false );
    list = add_new_test_word(list, "01120", "RATTS", "FATTS", false );
    list = add_new_test_word(list, "01120", "RATTS", "FATTY", true );
    list = add_new_test_word(list, "01010", "RATTS", "ARRAY", false );
    list = add_new_test_word(list, "01120", "RATTS", "ABITI", true );
    list = add_new_test_word(list, "01120", "RATTS", "DESTE", false );

    while (list->prev != NULL)
    {
        list = list->prev;
    }
    while (list->next != NULL)
    {
        if( redOK( list->pattern, list->word, list->try_word) != list->isOK && greenOK( list->pattern, list->word, list->try_word)!= list->isOK && orangeOK( list->pattern, list->word, list->try_word) != list->isOK )
        {printf("\n %s", "erreur");}
        else
        {printf("\n %s", "tout est bon");}
        list = list->next;
    }
    if( redOK( list->pattern, list->word, list->try_word) != list->isOK && greenOK( list->pattern, list->word, list->try_word)!= list->isOK && orangeOK( list->pattern, list->word, list->try_word) != list->isOK )
        {printf("\n %s", "erreur");}
        else
        {printf("\n %s", "tout est bon");}
    printf("\n");
    return 0;
}

int dico()
{
    Dictionary* dico = newDictionary();
    dico = addToDictionary(dico, "PUMBA");
    dico = addToDictionary(dico, "PUMBO");
    dico = addToDictionary(dico, "PUMBI");

    printf("\n %s", dico->word);
    dico = removeFromDictionary(dico);-
    printf("\n %s", dico->word);
    printf("\n");

    return 0;
}
*/

int main()
{
    //printf("%s\n",access_chunk("chaine", 1, 2)); //test access_chunk ok
    //printf("%d\n", isEven("chaine")); // test isEven ok 

    char* mot = "chaine";
    char* pattern = "001201";
    Node* node_right = new_node(2,4,"ne","01");
    Tree* tree_right = new_tree(node_right);

    Node* node_left = new_node(3,0,"cha","001");
    Tree* tree_left = new_tree(node_left);

    Node* root = new_node(1,3,"i","2");

   // printf("%s\n", accessNode(tree_right,1,2)->letters);  il faut attendre d'avoir un vrai arbre
    //Tree* tree = join_tree(tree_left, tree_right, root);
    //print_tree_prefix(tree);
    //printf("\n");
    //Tree* firstTree = beginTree(root, mot, pattern);
    //print_tree_prefix(firstTree);
    //printf("\n");
    Tree* tree2 = beginTree(root,mot,pattern); 
    //printf("%p\n", &tree2);
    //isOK();
    //dico();
    //print_tree_prefix(tree2);
    //printf("%s \n", isEven(tree2->node->letters) ? "true" : "false");
    //printf("%s \n", isEven(tree2->tleft->node->letters) ? "true" : "false");
    //printf("%s \n", isEven(tree2->tright->node->letters) ? "true" : "false");
    //petiteFonction(tree_right,d 0);
    //print_tree_prefix(tree_right);
    buildTree(tree2);
    print_tree_prefix(tree2);
    /*Frequency* list = new_Frequency();
    list->elemt="AA";
    list->freq=0.2;
    Frequency* next= new_Frequency();
    list->next_elmt= next;
    next->prev_elmt=list;
    next->elemt="BB";
    next->freq=0.3;
    
    Frequency* next_next= new_Frequency();
    list->next_elmt->next_elmt= next_next;
    next_next->elemt="CC";
    next_next->freq=0.1;
    list->next_elmt->next_elmt->prev_elmt = next;
    Frequency* sorted = sortFrequenciesdsc(list);
    //Frequency* sorted=beginningFrequency(list);
    printf("%f, %s \n", sorted->freq, sorted->elemt);
    printf("%f, %s \n", sorted->next_elmt->freq, sorted->next_elmt->elemt);
    printf("%f, %s \n", sorted->next_elmt->next_elmt->freq, sorted->next_elmt->next_elmt->elemt); */



    return 0;
}
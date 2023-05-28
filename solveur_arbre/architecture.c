#include "architecture.h"
#include <assert.h>
#include <string.h>
#include <math.h> 

//==========================================================================================================================================
//
//                                                    Outils divers
//
//==========================================================================================================================================


double toDouble( char* str) 
{ 
    char* ptr;
    char* toD = str;
    double fl = 0;
    fl = strtod(toD, &ptr);

    return(fl);
}

bool isIn(char letter, char* word)
{
    int length = strlen(word);
    for(int i = 0; i<length; i++)
    {
        char elmt =word[i];
        if(elmt==letter)
        {return true;}
    }
    return false;
}

History* last_word(History* entered_word){
    while (entered_word->next != NULL){
        entered_word=entered_word->next;
    }
    return entered_word;
}

//==========================================================================================================================================
//
//                                                    Manipulation des dictionnaires
//
//==========================================================================================================================================

History* backToHead(History* histo)
{
    while ( histo->prev != NULL)
    {
        histo = histo->prev;
    }
    return histo->next;
}

Dictionary* voidDictionary(void)
{
    Dictionary* dico;
    dico = malloc(sizeof(Dictionary));

    dico->next = NULL;
    dico->previous = NULL;
    dico->word = NULL;

    return dico;
}

First_word* newDictionary(void)
{
    First_word* first = malloc(sizeof(First_word));
    Dictionary* dictionary = malloc(sizeof(Dictionary));

    // Initialisation 
    dictionary->next = NULL;
    dictionary->previous = NULL;
    dictionary->word = NULL;
    first->dico = dictionary;

    return first;
}

Dictionary* addToDictionary(Dictionary* dictionary, char* word)
{
    if (dictionary->word == NULL)
    {
        char* value = malloc(sizeof(char[12]));
        strcpy(value, word);
        dictionary->word = value;
        return dictionary;
    }
    else
    {
        Dictionary* new_dictionary = voidDictionary();
        char* value = malloc(sizeof(char[12]));
        strcpy(value, word);
        new_dictionary->word = value;
        new_dictionary->previous = dictionary;
        new_dictionary->next = NULL;
        dictionary->next = new_dictionary;
        return new_dictionary;
    }
}

First_word* createDico(char* fichier, int length)
{
    FILE* file = fopen(fichier, "r");
    char* chaine = malloc(30);
    First_word* first = newDictionary();
    Dictionary* dico = first->dico;
    if (file != NULL)
    {
        while (fgets(chaine, 30, file) != NULL)
        {
            chaine[strcspn(chaine, "\n")] = 0;
            int len = strlen(chaine);
            if (len == length)
            {
                addToDictionary(dico, chaine);
                Dictionary* new_dictionary = voidDictionary();
                new_dictionary->previous = dico;
                dico->next = new_dictionary;
                dico = new_dictionary;
            }
        }
    }
    return first;
}

void removeFromDictionary(First_word* first, Dictionary* dico)
{  
    if (dico == first->dico)
    {
        Dictionary* next = malloc(sizeof(Dictionary));
        next = dico->next;
        first->dico = next;

        return;
    }
    else if (dico->next == NULL)
    {
        Dictionary* prev = malloc(sizeof(Dictionary));
        prev = dico->previous;
        prev->next = NULL;

        return;
    }
    else
    {
        Dictionary* next = dico->next;
        Dictionary* prev = dico->previous;

        next->previous = prev;
        prev->next = next;

        return;
    }
}

//==========================================================================================================================================
//
//                                                    Outils de diminution des dictionnaires
//
//==========================================================================================================================================


bool greenOK( char* pattern, char* word, char* try_word)
{
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
        if(pattern[i] == '2' && word[i] != try_word[i])
        {
            return false;
        }
    }
    return true;
}

bool redOK( char* pattern, char* word, char* try_word)
{
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
        if(pattern[i] == '0')
        {
            if (word[i] == try_word[i])
            { return false; }

            char letter = word[i];
            int count = 0;
            int count2 = 0;
            int count3 = 0;
            for(int j = 0; j<length; j++)
            {
                if(word[j] == letter)
                {
                    if( pattern[j] != '0')
                    { count++; }
                    else
                    { count3++; }
                }
                if(try_word[j] == letter)
                { count2++; }
            }
            if( count2>count && count3 != 0)
            { return false;}   
        }
    }
    return true;
}

bool orangeOK( char* pattern, char* word, char* try_word)
{
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
        if(pattern[i] == '1') 
        {
            char letter = word[i];
            char* try = try_word;
            if(!(isIn(letter, try)))
            {
                return false;
            }
        }
    }
    return true;
}

History* new_entry(History* histo, char* word, char* pattern)
{
    History* new = malloc(sizeof(History));
    new->word = word;
    new->pattern = pattern;
    new->prev = histo;

    histo->next = new;
    return new;
}

bool not_entered(History* hist, char* word)
{
    while (hist->prev != NULL)
    {
        hist = hist->prev;
    }

    while (hist->next != NULL)
    {
        if (hist->word == word)
        {
            return true;
        }
    }
    if (hist->word == word)
    {
        return true;
    }
    return false;    
}

bool word_compatible(char* word, History* history)
{
    while (history != NULL)
    {
        if( !(greenOK(history->pattern, history->word, word) && redOK(history->pattern, history->word, word) && orangeOK(history->pattern, history->word, word)) )
        {
            return false;
        }
        history = history->next;
    }
    return true;
}

First_word* checkWord(First_word* first, History* entered_word)
{
    Dictionary* dico = first->dico;
    if ( first->dico != NULL)
    {   
        while ( !word_compatible(dico->word, entered_word) && dico != NULL )
        {
            removeFromDictionary(first, first->dico);
            dico = first->dico;
        }
        while ( dico->next != NULL )
        {   
            if ( !word_compatible(dico->word, entered_word))
            {
                Dictionary* next = dico->next;
                removeFromDictionary(first, dico);
                dico = next;
            }
            else
            {
                dico = dico->next;
            }
        }
    }
    return first;
}



//==========================================================================================================================================
//
//                                                    Manipulation des chaînes de caractères
//
//==========================================================================================================================================

char* access_chunk(char* chain, int index, int length)
{
    char* chunk = calloc(sizeof(char),length);
    for (int i=index, j=0; i<index+length; i++, j++)
    {
            chunk[j]=chain[i];
    }
        return chunk;
}

// renvoie si la chaîne est de longueur paire
bool isEven(char* element){
    return (strlen(element)%2==0);
};



void freeFrequency(Frequency* freq){
     while (freq->prev_elmt != NULL)
    {
        freq=freq->prev_elmt;
    }
    while (freq->next_elmt != NULL){
        freq=freq->next_elmt;
        free(freq->prev_elmt);
  
    }

}

Frequency* new_Frequency(){
    Frequency* new = malloc(sizeof(Frequency));
    new->next_elmt=NULL;
    new->prev_elmt=NULL;
    return new;
}

Frequency* beginningFrequency(Frequency* freq){ //marche
    while (freq->prev_elmt != NULL)
    {
        freq=freq->prev_elmt;
    }
    return freq;

};

int length_freq(Frequency* list){ //marche
    list = beginningFrequency(list);
    int i=1;
    while (list->next_elmt != NULL){
        i++;
        list=list->next_elmt;
    }
    return i;
}

//==========================================================================================================================================
//
//                                                    Manipulation des arbres
//
//==========================================================================================================================================



Node* accessNode(Tree* tree, int pos, int length)
{
    if (tree->node->position == pos && tree->node->length==length) 
    {
        return tree->node;
    }
    if (tree->tleft == NULL && tree->tright == NULL && (tree->node->position != pos) && (tree->node->length != length)){
        printf("%s", "erreur");
        return NULL;
    }
    Node* racine = calloc(sizeof(Node),1);
    racine=tree->node;
    int pivot = racine->position;
    if (pos<pivot){
        accessNode(tree->tleft, pos, length);
    }
    else if (pos>pivot)
    {
        accessNode(tree->tright, pos, length);
    }
    free(racine);
}

// Delete the current tree
void delete_tree(Tree* tree )
{
	if (tree == NULL)
	{
		return;
	}

	delete_tree(tree->tleft);
	delete_tree(tree->tright);
	free(tree);

	return;
}

Node* new_node(int length, int position, char* letters, char* pattern){
    Node* node = calloc(sizeof(Node),1);
    node->length=length;
    node->position=position;
    node->letters=letters;
    node->pattern=pattern;
    return node;
};

// Initialize a new tree
Tree* new_tree( Node* node)
{
	Tree* tree=(Tree*)malloc(sizeof(Tree));
	tree->tleft = NULL;
	tree->tright = NULL;
	tree->parent = NULL;
	tree->node = node;

	return tree;
}

// Créer un noeud et y fixer deux branches
Tree* join_tree( Tree* tleft, Tree* tright, Node* node )
{
	Tree* tree = new_tree( node);

	tree->tleft = tleft;
	tree->tright = tright;
	
	if (tleft != NULL)
	{ tleft->parent = tree; }

	if (tright != NULL)
	{ tright->parent = tree; }

	return tree;
}

// Compte le nombre de noeuds descendant de Tree
int count_tree_nodes(Tree *tr)
{
	if(tr == NULL)
		return 0;

	return (count_tree_nodes(tr->tleft) + count_tree_nodes(tr->tright) + 1);	
}

void print_tree_prefix(Tree* tree)
{
	if(tree == NULL)
		return;

    else
    	printf("%s, %s, %d, %d \n", tree->node->letters, tree->node->pattern, tree->node->position, tree->node->length);

    if(tree->tleft != NULL)
    	print_tree_prefix(tree->tleft);

    if(tree->tright != NULL)
    	print_tree_prefix(tree->tright);
};

Tree* beginTree(Node* racine, char* mot, char* pattern)
{
    char* cleft = access_chunk(mot, 0, racine->position);
    char* pattern_left = access_chunk(pattern, 0, racine->position);
    char* cright = access_chunk(mot, racine->position +1, strlen(mot)-(racine->position+1));
    char* pattern_right = access_chunk(pattern, racine->position +1, strlen(pattern)-(racine->position+1));
    Node* node_left= new_node(strlen(cleft), 0, cleft, pattern_left);
    Node* node_right= new_node(strlen(cright), racine->position +1, cright, pattern_right);
    Tree* tree_left = new_tree(node_left);
    Tree* tree_right= new_tree(node_right);
    Tree* beginTreee = join_tree(tree_left, tree_right, racine);
    return beginTreee;
}

void buildTree(Tree* beginTree) 
{
    bool finished_l = false;
    bool finished_r = false;

    Tree* tleft_ = beginTree->tleft;

    Tree* tright_ = beginTree->tright;


    Tree* leftside_l= malloc(sizeof(Tree));
    Tree* rightside_l= malloc(sizeof(Tree));
    Tree* leftside_r = malloc(sizeof(Tree));
    Tree* rightside_r = malloc(sizeof(Tree));   

    tleft_->tleft=leftside_l;
    leftside_l->parent=tleft_;
    tleft_->tright=rightside_l;
    rightside_l->parent=tleft_;
    tright_->tleft=leftside_r;
    leftside_r->parent=tright_;
    tright_->tright=rightside_r;
    rightside_r->parent=tright_;

    int lpivot, rpivot;

    if (tleft_->node->length == 1 || tleft_->node->length == 2){
        tleft_->tleft=NULL;
        tleft_->tright=NULL;
        finished_l= true;

    }
    else 
    {
        if(isEven(tleft_->node->letters))
        {
            lpivot= (tleft_->node->length)/2-1;  
        }
    
        else 
        {
            lpivot=(tleft_->node->length+1)/2-1;
        }

        char* cleft = access_chunk(tleft_->node->letters, 0, lpivot+1);
        char* pattern_left = access_chunk(tleft_->node->pattern, 0, lpivot+1);
        char* cright = access_chunk(tleft_->node->letters, lpivot +1, strlen(tleft_->node->letters)-(lpivot+1));
        char* pattern_right = access_chunk(tleft_->node->pattern, lpivot +1, strlen(tleft_->node->letters)-(lpivot+1));
        tleft_->tleft=new_tree( new_node(strlen(cleft),tleft_->node->position,cleft,pattern_left));
        tleft_->tright=new_tree( new_node(strlen(cright),strlen(cleft),cright,pattern_right));
    }


    if (tright_->node->length == 1 || tright_->node->length ==2){
        tright_->tleft=NULL;
        tright_->tright=NULL;
        finished_r = true;
    }

    else {
        if (isEven(tright_->node->letters))
        {
             rpivot= tright_->node->length/2 -1;
        }
        else 
        {
             rpivot= (tright_->node->length+1)/2 -1;
        }
         
  
    char* cleft2 = access_chunk(tright_->node->letters, 0, rpivot);
    char* pattern_left2 = access_chunk(tright_->node->pattern, 0, rpivot);
    char* cright2 = access_chunk(tright_->node->letters, rpivot, strlen(tright_->node->letters)-strlen(cleft2));
    char* pattern_right2 = access_chunk(tright_->node->pattern, rpivot +1, strlen(tright_->node->letters)-strlen(cleft2));
    leftside_r=new_tree( new_node(strlen(cleft2),tright_->node->position,cleft2,pattern_left2));
    rightside_r=new_tree( new_node(strlen(cright2),strlen(cleft2),cright2,pattern_right2));
    }
  
    if (!finished_l)
    {
        buildTree(tleft_);
    }
    if (!finished_r)
    {
        buildTree(tright_);
    }
    if (finished_r &&  finished_l)
    {
        return ;
    } 
    
};

/*
Tree* createTree(char* mot, char* pattern)
{
    int root=0;
    for (int i=0; i<strlen(pattern) ; i++){
        if (pattern[i]=='2' && abs(i-(int)(strlen(pattern))/2)<abs(root-(int)(strlen(pattern))/2)){
            root=i;
        }
    }
    Node* racine = new_node(strlen(mot), root, mot, pattern);
    Tree* firstTree = beginTree(racine, mot, pattern);
    buildTree(firstTree);
    return firstTree;
}

Frequency* sortFrequenciesdsc(Frequency* list)
{
    Frequency* sorted_list = new_Frequency();
    sorted_list->elemt=list->elemt;
    sorted_list->freq= list->freq;
    list=list->next_elmt;

    for (int i=1; i<length_freq(list); i++)
    {
        sorted_list=beginningFrequency(sorted_list);
        if(list->freq <= sorted_list->freq)
        {
            while (sorted_list->prev_elmt !=NULL && list->freq > sorted_list->prev_elmt->freq )
            {
                sorted_list=sorted_list->prev_elmt;
            }
            if (sorted_list->prev_elmt ==NULL)
            {
                Frequency* current = malloc(sizeof(Frequency));
                current->freq = list->freq;
                current->elemt= list->elemt;
                sorted_list->prev_elmt = current;
                current->next_elmt=sorted_list;
                    
            }
            else if (list->freq >= sorted_list->prev_elmt->freq && list->freq <= sorted_list->freq)
            {
                Frequency* new= malloc(sizeof(Frequency));
                new->elemt=list->elemt;
                new->freq=list->freq;

                sorted_list->prev_elmt->next_elmt=new;
                new->prev_elmt=sorted_list->prev_elmt;

                new->next_elmt=sorted_list;
                sorted_list->prev_elmt=new;

            }
        }
        else if(list->freq > sorted_list->freq)
        {
            while (sorted_list->next_elmt !=NULL && list->freq > sorted_list->prev_elmt->freq )
            {
                sorted_list=sorted_list->next_elmt;
            }
            if (sorted_list->next_elmt ==NULL)
            {
                Frequency* current = malloc(sizeof(Frequency));
                current->freq = list->freq;
                current->elemt= list->elemt;
                sorted_list->next_elmt = current;
                current->prev_elmt=sorted_list;
            }
            else if (list->freq <= sorted_list->prev_elmt->freq && list->freq > sorted_list->freq)
            {
                Frequency* new= malloc(sizeof(Frequency));
                new->elemt=list->elemt;
                new->freq=list->freq;

                sorted_list->prev_elmt->next_elmt=new;
                new->prev_elmt=sorted_list->prev_elmt;

                new->next_elmt=sorted_list;
                sorted_list->prev_elmt=new;

            }
    }
    list=list->next_elmt;
    }
    return sorted_list;
}

*/
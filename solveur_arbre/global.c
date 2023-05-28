#include "global.h"

char* bestWord(First_word* sorted_dico, History* entered_word)
{
    // entrer les deux premiers mots associés à la taille dans first_words.txt et stocker eux et leurs pattern dans entered_word
    entered_word= last_word(entered_word);
    sorted_dico = checkWord(sorted_dico, entered_word); 
    Tree* tree = createTree(entered_word->word, entered_word->pattern);
    return compute(tree, sorted_dico);
}
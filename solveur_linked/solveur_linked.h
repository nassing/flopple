typedef struct LinkedWord LinkedWord;
typedef struct Dictionary Dictionary;
typedef struct GreenLetters GreenLetters;


struct LinkedWord 
{
    LinkedWord* previous; //L'adresse du pointeur du mot précédent
    LinkedWord* next;   //L'adresse du pointeur du prochain mot
    char* value;   //Le mot
};

struct Dictionary
{
    LinkedWord* firstWord;
};

LinkedWord* MakeLinkedWord();

Dictionary* MakeDictionary(unsigned int wordSize, char* dictionaryName);

void PrintDictionary(Dictionary* dico);

void RemoveFromDictionary(LinkedWord* removedWord,Dictionary* dictionary);



void RefreshDictionary(Dictionary* possibleSolutions, char* input, LinkedWord* bestWord);


#include <stdlib.h>
#include <stdio.h>
#include "solveur_linked.c"

int main()
{
    int totalTests = 0;
    int categoryTests = 0;

    int passedCategoryTests = 0;
    int passedTests = 0;


    //Tests LinkedWords---------------------------------------------------------------------------------------------------------------
    //Fini, fonctionne
    printf("\n    Tests for LinkedWords");
    passedCategoryTests = 0;
    categoryTests = 0;

    LinkedWord* word1 = MakeLinkedWord();
    LinkedWord* word2 = MakeLinkedWord();
    LinkedWord* word3 = MakeLinkedWord();
    word1 -> value = "word1";
    word2 -> value = "word2";
    word3 -> value = "word3";
    word2 -> previous = word1;
    word1 -> next = word2;
    word2 -> next = word3;
    word3 -> previous = word2;

    if(strcmp(word2 -> next -> value, "word3") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(strcmp(word2 -> previous -> value, "word1") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(strcmp(word1 -> next -> value, "word2") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(strcmp(word1 -> next -> next -> value, "word3") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(strcmp(word3 -> previous -> previous -> value, "word1") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;


    printf("\nLinkedWords : %d test(s) passed out of %d", passedCategoryTests, categoryTests);

    free(word1);
    free(word2);
    free(word3);

    //Tests MakeDictionary---------------------------------------------------------------------------------------------------------------
    printf("\n\n    Tests for MakeDictionary");
    passedCategoryTests = 0;
    categoryTests = 0;

    Dictionary* dictionary = MakeDictionary(5,"dictionary_test.txt");
    if(strcmp(dictionary -> firstWord -> value, "ONEAA") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(strcmp(dictionary -> firstWord -> next -> next -> previous -> value, "TWOAA") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(strcmp(dictionary -> firstWord -> next -> next -> value, "THREE") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(dictionary -> firstWord -> previous == NULL)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    dictionary = MakeDictionary(3,"dictionary_test.txt");
    if(strcmp(dictionary -> firstWord -> value, "ONE") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(strcmp(dictionary -> firstWord -> next -> next -> value, "THR") == 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    if(dictionary -> firstWord -> next -> next -> next == NULL)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    printf("\nMakeDictionary : %d test(s) passed out of %d", passedCategoryTests, categoryTests);
    
    free(dictionary);
    
    //Tests RemoveFromDictionary------------------------------------------------------------------------------------------------------------
    printf("\n\n    Tests for RemoveFromDictionary");
    passedCategoryTests = 0;
    categoryTests = 0;

    dictionary = MakeDictionary(5,"dictionary_test.txt");
    char* secondWord = dictionary -> firstWord -> next -> value;
    RemoveFromDictionary(dictionary -> firstWord, dictionary);
    if(dictionary -> firstWord -> value == secondWord)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    free(dictionary);

    dictionary = MakeDictionary(5,"dictionary_test.txt");
    char* penultimateWord = dictionary -> firstWord -> next -> value;
    RemoveFromDictionary(dictionary -> firstWord -> next -> next, dictionary);
    if(dictionary -> firstWord -> next -> value == penultimateWord)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    free(dictionary);

    dictionary = MakeDictionary(5,"dictionary_test.txt");
    char* firstWord = dictionary -> firstWord -> value;
    char* lastWord = dictionary -> firstWord -> next -> next -> value;
    RemoveFromDictionary(dictionary -> firstWord -> next, dictionary);
    if(dictionary -> firstWord -> value == firstWord)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;
    
    if(dictionary -> firstWord -> next -> value == lastWord)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    printf("\nRemoveFromDictionary : %d test(s) passed out of %d", passedCategoryTests, categoryTests);
    
    
    //Tests RefreshDictionary-------------------------------------------------------------------------------------------------------------
    printf("\n\n    Tests for RefreshFromDictionary");
    passedCategoryTests = 0;
    categoryTests = 0;


    dictionary = MakeDictionary(5, "dictionary_test.txt");
    secondWord = dictionary -> firstWord -> next -> value;
    RefreshDictionary(dictionary,"00022", dictionary -> firstWord);
    if(dictionary -> firstWord -> value == secondWord)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;
    
    
    dictionary = MakeDictionary(5, "dictionary_test.txt");
    firstWord = dictionary -> firstWord -> value;
    RefreshDictionary(dictionary,"22222", dictionary -> firstWord);
    if(dictionary -> firstWord -> value == firstWord)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    dictionary = MakeDictionary(5, "dictionary_test.txt");
    char* three = dictionary -> firstWord -> next -> next -> value;
    RefreshDictionary(dictionary,"00100", dictionary -> firstWord);
    if(dictionary -> firstWord -> value == three)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    dictionary = MakeDictionary(5, "dictionary_test.txt");
    RefreshDictionary(dictionary,"00011", dictionary -> firstWord -> next -> next);
    if(dictionary -> firstWord == NULL)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    dictionary = MakeDictionary(5, "dictionary_test.txt");
    char* oneaa = dictionary -> firstWord -> value;
    RefreshDictionary(dictionary,"00010", dictionary -> firstWord -> next -> next);
    if(dictionary -> firstWord -> value == oneaa)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    dictionary = MakeDictionary(5, "dictionary_test2.txt");
    oneaa = dictionary -> firstWord -> value;
    RefreshDictionary(dictionary,"00010", dictionary -> firstWord -> next -> next);
    if(dictionary -> firstWord -> value == oneaa)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    printf("\nRefreshDictionary : %d test(s) passed out of %d", passedCategoryTests, categoryTests);
    
    //Tests getScore---------------------------------------------------------------------------------------------------------------
    
    printf("\n\n    Tests for getScore");
    passedCategoryTests = 0;
    categoryTests = 0;


    dictionary = MakeDictionary(5,"dictionary_test.txt");
    LinkedWord* inputWord = MakeLinkedWord();
    inputWord -> value = "ZZZZZ";
    char* greenLetters = "A";
    char* greenLettersPositions = "0";

    if(getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) == (float) 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;
    
    inputWord -> value = "ORDRE";
    greenLetters = "O";
    greenLettersPositions = "0";
    if(getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) > (float) 0.06 &&getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) < (float) 0.07)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;


    inputWord -> value = "ONEAZ";
    greenLetters = "ONEAZ";
    greenLettersPositions = "01234";
    if(getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) > (float) 0.33 && getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) < (float) 0.34)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;


    inputWord -> value = "ONEAZ";
    greenLetters = "ONEAZ";
    greenLettersPositions = "56789";
    if(getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) == (float) 0)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    inputWord -> value = "ONEAA";
    greenLetters = "OEA";
    greenLettersPositions = "023";
    if(getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) > (float) 0.26 && getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) < (float) 0.27)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    
    inputWord -> value = "TWOAA";
    greenLetters = "WOA";
    greenLettersPositions = "123";
    if(getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) > (float) 0.26 && getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) < (float) 0.267)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    inputWord -> value = "THREE";
    greenLetters = "TEE";
    greenLettersPositions = "234";
    
    if(getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) > (float) 0.13 && getScore(inputWord, dictionary, 5, greenLetters, greenLettersPositions) < (float) 0.14)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    printf("\ngetScore : %d test(s) passed out of %d", passedCategoryTests, categoryTests);
    
    //Tests getGreenLetters---------------------------------------------------------------------------------------------------------------
    printf("\n\n    Tests for getGreenLetters");
    passedCategoryTests = 0;
    categoryTests = 0;

    char greenLetters1[256] = "";
    char greenLettersPosition1[256] = "";
    char* wordInput = "TARIE";
    char* inputCode = "20000";
    getGreenLetters(greenLetters1,greenLettersPosition1,wordInput,inputCode);

    if(greenLetters1[0] == 'T' && greenLettersPosition1[0] == '0')
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    wordInput = "TARIE";
    inputCode = "22222"; 
    getGreenLetters(greenLetters1,greenLettersPosition1,wordInput,inputCode);
    if( !strcmp(greenLetters1,"TARIE") && !strcmp(greenLettersPosition1, "01234") )
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    memset(greenLetters1, 0, sizeof(greenLetters1));    // = ""
    memset(greenLettersPosition1, 0, sizeof(greenLetters1));
    wordInput = "TARIE";
    inputCode = "20000"; 
    getGreenLetters(greenLetters1,greenLettersPosition1,wordInput,inputCode);
    wordInput = "CARTE";
    inputCode = "00020"; 
    getGreenLetters(greenLetters1,greenLettersPosition1,wordInput,inputCode);
    if( !strcmp(greenLetters1,"TT") && !strcmp(greenLettersPosition1, "03") )
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    printf("\ngetGreenLetters : %d test(s) passed out of %d", passedCategoryTests, categoryTests);    

    
    //Tests getBestWord---------------------------------------------------------------------------------------------------------------
    printf("\n\n    Tests for getBestWord");
    passedCategoryTests = 0;
    categoryTests = 0;

    Dictionary* possibleSolutions;
    Dictionary* possibleInputs;


    memset(greenLetters1, 0, sizeof(greenLetters1));    // = ""
    memset(greenLettersPosition1, 0, sizeof(greenLetters1));       
    possibleInputs = MakeDictionary(5, "dictionary_test.txt");  //Liste qu'on touchera pas ou peu
    possibleSolutions = MakeDictionary(5, "dictionary_test.txt");  //Liste qu'on touchera pas ou peu

    getGreenLetters(greenLetters1,greenLettersPosition1,"TARIE","02020");
    LinkedWord* bestWord = getBestWord(possibleSolutions, possibleInputs, 5, greenLetters1, greenLettersPosition1);

    if(!strcmp(bestWord -> value, "THREE"))
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    possibleInputs = MakeDictionary(6, "dictionary_test3.txt");  //Liste qu'on touchera pas ou peu
    possibleSolutions = MakeDictionary(6, "dictionary_test3.txt");  //Liste qu'on touchera pas ou peu
    memset(greenLetters1, 0, sizeof(greenLetters1));    // = ""
    memset(greenLettersPosition1, 0, sizeof(greenLetters1));    
    getGreenLetters(greenLetters1,greenLettersPosition1,"ARCHE","20002");
    bestWord = getBestWord(possibleSolutions, possibleInputs, 6, greenLetters1, greenLettersPosition1);
    if(!strcmp(bestWord -> value, "ARGUER"))
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    possibleInputs = MakeDictionary(3, "dictionary_test3.txt");  //Liste qu'on touchera pas ou peu
    possibleSolutions = MakeDictionary(3, "dictionary_test3.txt");  //Liste qu'on touchera pas ou peu
    memset(greenLetters1, 0, sizeof(greenLetters1));    // = ""
    memset(greenLettersPosition1, 0, sizeof(greenLetters1));    
    getGreenLetters(greenLetters1,greenLettersPosition1,"ARC","200");
    bestWord = getBestWord(possibleSolutions, possibleInputs, 3, greenLetters1, greenLettersPosition1);
    if(!strcmp(bestWord -> value, "ARE"))
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    printf("\ngetBestWord : %d test(s) passed out of %d", passedCategoryTests, categoryTests);

    /*
    //Tests getFirstBestWord---------------------------------------------------------------------------------------------------------------
    printf("\n\n    Tests for getFirstBestWord");
    passedCategoryTests = 0;
    categoryTests = 0;

    if(false)
    {
        passedCategoryTests += 1;
        passedTests += 1;
    }
    categoryTests +=1;
    totalTests +=1;

    printf("\ngetFirstBestWord : %d test(s) passed out of %d", passedCategoryTests, categoryTests);
    */

    //Results-------------------------------------------------------------------------------------------------------------------------------
    printf("\n---------------------------------------------------------------------");
    printf("\n\nFinal results : %d test(s) passed out of %d\n", passedTests, totalTests);

}
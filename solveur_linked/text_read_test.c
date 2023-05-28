#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    
    FILE* file = fopen("dico.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), file)) 
    {
        printf("%s", line);
    }
    fclose(file);

    //char* dicoName = getDictionaryName(5);
    printf("ok");
    return 0;
}


#include "lineHandling.h"
#include <string.h>

char * findExpression(char * line, char * expression)
{
    size_t lineSize = strlen(line);
    size_t expSize = strlen(expression);
    int found = 1;

    if(expSize > lineSize)
        return NULL;

    size_t i;
    for(i = 0; i < lineSize-expSize; i++)
    {
        size_t j;
        for(j = i; j < expSize+i; j++)
        {
            if(line[j] != expression[j-i])
                found = 0;
        }

        if(found == 1)
            return line + i;

        found = 1;
    }

    return NULL;
}

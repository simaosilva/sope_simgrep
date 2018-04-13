#include "lineHandling.h"
#include <string.h>
#include <ctype.h>


char * findExpression(char * line, char * expression, bool is_case_sensitive)
{
  size_t lineSize = strlen(line);
  size_t expSize = strlen(expression);
  int found = 1;

  if(expSize > lineSize)
  return NULL;

  size_t i, j;
  for(i = 0; i < lineSize-expSize; i++)
  {
    for(j = i; j < expSize+i; j++)
    {
      if (!is_case_sensitive) {
        if(line[j] != expression[j-i] )
        found = 0;
      }
      else {
        if(tolower(line[j]) != tolower(expression[j-i]))
        found = 0;
      }
    }

    if(found == 1)
    return line + i;

    found = 1;
  }

  return NULL;
}

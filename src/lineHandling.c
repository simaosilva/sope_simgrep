#define _GNU_SOURCE

#include "lineHandling.h"
#include <string.h>
#include <ctype.h>


char * findExpression(char * line, char * expression, bool is_case_sensitive, bool word) {
    size_t lineSize = strlen(line);
    size_t expSize = strlen(expression);
    int found = 1;

    if (expSize > lineSize)
        return NULL;

    if (word) {
        char * searchp = line;
        if (is_case_sensitive) {
            while ((searchp = strcasestr(searchp, expression)) != NULL) {
                if (searchp == line || !isalnum(*(searchp - 1))) {
                    if ((!isalnum(*(searchp + expSize)) || (*(searchp + expSize)) == '\0')) {
                        return searchp;
                    }
                }
                searchp = searchp + expSize;
            }
        }
        else {
            while ((searchp = strstr(searchp, expression)) != NULL) {
                if (searchp == line || !isalnum(*(searchp-1))) {
                    if ((!isalnum(*(searchp + expSize)) || (*(searchp + expSize)) == '\0')) {
                        return searchp;
                    }
                }
                searchp = searchp + expSize;
            }
        }
    } else {
        size_t i, j;
        for (i = 0; i < lineSize - expSize; i++) {
            for (j = i; j < expSize + i; j++) {
                if (!is_case_sensitive) {
                    if (line[j] != expression[j - i])
                        found = 0;
                } else {
                    if (tolower(line[j]) != tolower(expression[j - i]))
                        found = 0;
                }
            }

            if (found == 1)
                return line + i;

            found = 1;
        }

    }

    return NULL;
}

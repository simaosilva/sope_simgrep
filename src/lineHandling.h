#ifndef _LINEHANDLING_H_
#define _LINEHANDLING_H_

#include <stdbool.h>

//
//To find specified expression in a line
//
char * findExpression(char * line, char * expression, bool is_case_sensitive, bool word);

#endif /*_LINEHANDLING_H_*/

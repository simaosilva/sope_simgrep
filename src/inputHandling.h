//
// Created by mariana on 04-04-2018.
//

#ifndef PROJETO_INPUTHANDLING_H
#define PROJETO_INPUTHANDLING_H

#include "grep.h"

/*
 * Checks arguments given by user and sets the respective flags in the grepOptions structure (?); returns 0 if successful, -1 otherwise;
 */
int checkArguments(Grep * grep, int argc, char * argv[]);

#endif //PROJETO_INPUTHANDLING_H

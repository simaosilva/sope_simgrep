//
// Created by mariana on 04-04-2018.
//

#ifndef PROJETO_GREPOPTIONS_H
#define PROJETO_GREPOPTIONS_H

#include <stdbool.h>

typedef struct grep_t {
    bool ignore;
    bool fileNameOnly;
    bool lineNumber;
    bool numberLinesFound;
    bool word;
    bool recursive;
    char * expression;
    char * file;    // file or directory
} Grep;

/*
 * Creates an instance of a GrepOptions struct
 */
Grep * createGrep();
/*
 * Sets the flags of a GrepOptions struct according to a given array of options; returns index of the member AFTER the last option found
 */
int setGrepOptions(Grep * grepOptions, int optionsSize, char * options[]);
/*
 * Sets the expression to search for; returns 0 if successful, -1 otherwise
 */
int setGrepExpression(Grep * grep, char * expression);
/*
 * Sets the files on which to run grep; returns 0 if successful, -1 otherwise
 */
int setGrepFile(Grep * grep, char * file);
/*
 * Deletes a GrepOptions struct
 */
void deleteGrep(Grep * p);

#endif //PROJETO_GREPOPTIONS_H

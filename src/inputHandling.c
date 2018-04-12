//
// Created by mariana on 04-04-2018.
//

#include <stdio.h>
#include "inputHandling.h"

int checkArguments(Grep * grep, int argc, char * argv[]) {
    int i;
    //OPTIONS (OPTIONAL)
    i = setGrepOptions(grep, argc, argv);
    //EXPRESSION
    if (i == argc) {
        perror("Incorrect number of arguments given, check usage\n");
        return -1;
    } else {
        setGrepExpression(grep, argv[i]);
    }
    //FILE (OPTIONAL)
    i++;
    if (i != argc) {
        setGrepFile(grep, argv[i]);
    }
    return 0;
}
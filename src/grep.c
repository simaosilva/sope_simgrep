//
// Created by mariana on 04-04-2018.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "grep.h"

Grep * createGrep() {
  Grep * ret = (Grep*) malloc(sizeof(Grep));

  ret->ignore = false;
  ret->fileNameOnly = false;
  ret->lineNumber = false;
  ret->numberLinesFound = false;
  ret->word = false;
  ret->recursive = false;
  ret->expression = NULL;
  ret->file = NULL;

  return ret;
}

int setGrepOptions(Grep * grepOptions, int optionsSize, char * options[]) {
  int i;
  for (i = 1; i < optionsSize; i++) {
    if(strcmp(options[i], "-c") == 0) {
      grepOptions->numberLinesFound = true;
      continue;
    }
    if(strcmp(options[i], "-i") == 0) {
      grepOptions->ignore = true;
      continue;
    }
    if(strcmp(options[i], "-l") == 0) {
      grepOptions->fileNameOnly = true;
      continue;
    }
    if(strcmp(options[i], "-n") == 0) {
      grepOptions->lineNumber = true;
      continue;
    }
    if(strcmp(options[i], "-r") == 0) {
      grepOptions->recursive = true;
      continue;
    }
    if(strcmp(options[i], "-w") == 0) {
      grepOptions->word = true;
      continue;
    }
    break;
  }

  if (grepOptions->fileNameOnly) {
    grepOptions->numberLinesFound = false;
    grepOptions->lineNumber = false;
  }

  return i;
}

int setGrepExpression(Grep* grep, char * expression) {
  size_t len = strlen(expression);
  grep->expression = (char*) malloc (len+1);
  if (grep->expression == NULL) {
    perror("Unable to allocate memory\n");
    return -1;
  }
  size_t i;
  for(i=0;i<=len;i++) {
    grep->expression[i] = expression[i];
  }
  return 0;
}

int setGrepFile(Grep * grep, char * file) {
  size_t len = strlen(file);
  grep->file = (char*) malloc (len+1);
  if (grep->file == NULL) {
    perror("Unable to allocate memory\n");
    return -1;
  }
  size_t i;
  for(i=0;i<=len;i++) {
    grep->file[i] = file[i];
  }
  return 0;
}

void deleteGrep(Grep * p) {
  free(p->expression);
  free(p->file);
  free(p);
}

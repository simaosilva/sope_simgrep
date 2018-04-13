//
// Created by mariana on 04-04-2018.
//

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "fileHandling.h"
#include "lineHandling.h"


void searchDirs(char * dirName, Grep * grep) {
  int pid, ret;
  int child_counter = 0;

  DIR *dirp;
  struct dirent *direntp;
  struct stat stat_buf;
  char name[200];

  // if the argument specified for the file parameter is just that, a file, then this will be null, and if we error check the file won't be analyzed
  if ((dirp = opendir(dirName)) == NULL) {
    grep->recursive = false;
    processFile(dirName, grep);
    return;
  }

  while ((direntp = readdir(dirp)) != NULL) {
    sprintf(name, "%s/%s", dirName, direntp->d_name);

    if (lstat(name, &stat_buf) == -1) {
      perror(name);
      exit(3);
    }

    if (S_ISREG(stat_buf.st_mode)) {
      //run function that checks if the file should be analyzed
      pid = fork();
      if (pid > 0) {
        child_counter++;

        if ( (ret = waitpid(-1, NULL, WNOHANG)) == -1) {  // check if some child had returned
          perror("waitpid()");
          exit(6);
        }
        else if (ret > 0) {
          child_counter--;
        }
      }
      else if (pid == 0) {
        processFile(name, grep);
        exit(0);
      }
      else {
        perror("Couldn't process fork...");
        exit(1);
      }
    } else if (S_ISDIR(stat_buf.st_mode)) {

      if (!grep->recursive) {
        fprintf(stderr, "%s is a directory\n",name);
        exit(4);
      }

      if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
        //recursively call the function to search all directories
        pid = fork();
        if (pid > 0) {
          child_counter++;

          if ( (ret = waitpid(-1, NULL, WNOHANG)) == -1) {     // check if some child had returned
            perror("waitpid()");
            exit(6);
          }
          else if (ret > 0) {
            child_counter--;
          }
        }
        else if (pid == 0) {
          searchDirs(name, grep);
          exit(0);
        }
        else {
          perror("Couldn't process fork...");
          exit(1);
        }
      }
    }
  }

  // wait for all childs
  while (child_counter-- > 0) {
    if (wait(NULL) == -1) {
      perror("wait()");
      exit(8);
    }
  }

  closedir(dirp);
}

void processFile(char * fileName, Grep *grep) {
  FILE * file = fopen(fileName, "r");
  if (file == NULL) {
    perror("Couldn't open file...");
    exit(1);
  }

  char *line = NULL;
  size_t allocated_size;
  int lineNumber = 0, lineCounter = 0;

  while(getline(&line, &allocated_size, file) != -1) {
    char string_to_print[200] = {0};
    lineNumber++;
    //run function that analyzes a line
    if (findExpression(line, grep->expression, grep->ignore, grep->word) != NULL) {

      if (grep->numberLinesFound) {
        lineCounter++;
      }
      else {
        if (grep->fileNameOnly) {
          printf("%s\n", fileName);
          free(line);
          fclose(file);
          return;
        }
        if (grep->recursive) {
          sprintf(string_to_print, "%s:", fileName);
        }
        if(grep->lineNumber) {
          sprintf(string_to_print, "%s%d:", string_to_print, lineNumber);
        }
        printf("%s%s", string_to_print, line);
      }
    }
  }

  if (grep->numberLinesFound && grep->recursive) {
    printf("%s:%d\n", fileName, lineCounter);
  }
  else if (grep->numberLinesFound && !grep->recursive){
    printf("%d\n", lineCounter);
  }

  free(line);
  fclose(file);
}

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
    int pid;
    int status;

    pid = fork();

    if (pid > 0) {
        wait(&status);
    } else if (pid == 0) {
        DIR *dirp;
        struct dirent *direntp;
        struct stat stat_buf;
        char name[200];

        if ((dirp = opendir(dirName)) == NULL) { // if the argument specified for the file parameter is just that, a file, then this will be null, and if we error check the file won't be analyzed
                processFile(dirName, grep);
        }

        while ((direntp = readdir(dirp)) != NULL) {
            sprintf(name, "%s/%s", dirName, direntp->d_name);
            if (lstat(direntp->d_name, &stat_buf) == -1)
            {
                perror("lstat ERROR");
                exit(3);
            }
            if (S_ISREG(stat_buf.st_mode)) {
                //run function that checks if the file should be analyzed
                processFile(name, grep);
            } else if (S_ISDIR(stat_buf.st_mode)) {

                if (!grep->recursive) {
                    fprintf(stderr, "%s is a directory\n",name);
                    exit(4);
                }

                if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
                    //recursively call the function to search all directories
                    searchDirs(name, grep);
                }
            }
        }

        closedir(dirp);
        exit(0);
    } else if (pid < 0) {
        perror("Couldn't process fork...");
        exit(1);
    }
}

void processFile(char * fileName, Grep *grep) {
    FILE * file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Couldn't open file...");
        exit(1);
    }
    char *line = NULL;
    size_t allocated_size;
    while(getline(&line, &allocated_size, file) != -1) {
        //run function that analyzes a line
        if (findExpression(line, grep->expression, grep->ignore) != NULL) {
            if (!grep->fileNameOnly) {
                if (!grep->numberLinesFound) {
                    printf("%s", line);
                } else {
                    grep->lineCount++;
                }
                printf("%s\n", fileName);
            }
        }
    }
    fclose(file);
}

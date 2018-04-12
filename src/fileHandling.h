//
// Created by mariana on 04-04-2018.
//

#ifndef PROJETO_FILEHANDLING_H
#define PROJETO_FILEHANDLING_H

#include "grep.h"

void searchDirs(char * dirName,  Grep * grep);

void processFile(char * fileName, struct dirent * direntp, struct stat stat_buf);



#endif //PROJETO_FILEHANDLING_H

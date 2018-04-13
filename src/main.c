#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "inputHandling.h"
#include "fileHandling.h"

void sigint_handler(int sig) {
    char c;
    printf("\n > Are you sure you want to terminate (Y/N)? ");
    c = getchar();
    if (c == 'y' || c == 'Y')
        exit(0);
    else if (c == 'n' || c == 'N')
        return;
    else {
        printf("Unrecognized character...\n");
        sigint_handler(SIGINT);
    }
}

int main(int argc, char * argv[]) {

    /*******************************/
    /******* SIGNAL HANDLING *******/
    /*******************************/

    struct sigaction action;
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGINT ,&action,NULL) < 0) {
        fprintf(stderr,"Unable to install SIGINT handler...\n");
        exit(1);
    }

    /*****************************/
    /******* MAIN SEQUENCE *******/
    /*****************************/

    Grep * grep = createGrep();
    if (checkArguments(grep, argc, argv) != 0) {
        return 1;
    }
    searchDirs(grep->file, grep);
    deleteGrep(grep);
    return 0;

    /*********************/
    /******* TESTS *******/
    /*********************/

/*    char linha[] = "This eBook is for the use of anyone anywhere at no cost and with";
    char search[] = "eBook";
    printf("%d\n", (int) strlen(linha));
    printf("%d\n", (int) strlen(search));
    printf("%s\n", boyer_moore((uint8_t*) linha, strlen(linha), (uint8_t*) search, strlen(search)));
    return 0;*/
}
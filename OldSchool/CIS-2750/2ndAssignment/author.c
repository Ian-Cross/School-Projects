#include "stream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int removeFlag = 0;
    char* username;

    /* Just make sure that they follow the rules of execution */
    if (argc <= 1){
        printf("Please include the username as a argument\n");
        exit(1);
    }

    if (strcmp(argv[1],"-r") == 0) removeFlag = 1;

    username = createUsername(argc,argv);

    char list[1000];
    /* Collect the list from the user */
    printf("List Streams: ");
    fgets(list,1000,stdin);

    /* Add or remove the user to the necessary stream files */
    if (removeFlag){
        removeUser(username,list);
    } else {
        addUser(username,list);
    }

    free(username);
    return 0;
}

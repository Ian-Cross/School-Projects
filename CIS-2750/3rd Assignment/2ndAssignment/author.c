#include "stream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char username[999] = "";
    char *u = username;
    char list[999] = "";
    char *l = list;
    char removeFlag[10] = "";
    char *r = removeFlag;
    char c;
    FILE* input = fopen("AddAuthor.new","r");
    if (input == NULL){
        printf("The file is broken\n");
        exit(1);
    }

    while ((c = fgetc(input)) != '\n'){
        *u++ = c;
    }

    while ((c = fgetc(input)) != '\n'){
        *l++ = c;
    }

    c = fgetc(input);
    while (c != '\n' && c != EOF ){
        *r++ = c;
        c = fgetc(input);
    }

    printf(":%s:%s:%s:\n",username,list,removeFlag);

    /* Add or remove the user to the necessary stream files */
    if (strcmp(removeFlag,"on") == 0 ){
        removeUser(username,list);
    } else {
        addUser(username,list);
    }

    fclose(input);
    remove("AddAuthor.new");
    return 0;
}

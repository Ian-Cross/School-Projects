#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stream.h"

int main(int argc, char const *argv[]) {
    printf("Hello I am Here\n");
    UserPost* newPost = NULL;

    newPost = (UserPost*)malloc(sizeof(UserPost));
    if (newPost == NULL){
        printf("Sorry there wasn't enough space\n");
        exit(1);
    }

    newPost->username = (char*)malloc(sizeof(char)*60);
    if (newPost->username == NULL){
        printf("Sorry there wasn't enough space\n");
        exit(1);
    }

    newPost->streamName = (char*)malloc(sizeof(char)*60);
    if (newPost->streamName == NULL){
        printf("Sorry there wasn't enough space\n");
        exit(1);
    }

    newPost->data = (char*)malloc(sizeof(char)*60);
    if (newPost->data == NULL){
        printf("Sorry there wasn't enough space\n");
        exit(1);
    }

    newPost->text = (char*)malloc(sizeof(char)*60);
    if (newPost->text == NULL){
        printf("Sorry there wasn't enough space\n");
        exit(1);
    }


    strcpy(newPost->username,"Steve");
    strcpy(newPost->streamName,"cats");
    strcpy(newPost->data,"fart");
    strcpy(newPost->text,"Hello there you suck");

    updateStream(newPost);

    free(newPost->username);
    free(newPost->streamName);
    free(newPost->data);
    free(newPost->text);
    free(newPost);
    return 0;
}

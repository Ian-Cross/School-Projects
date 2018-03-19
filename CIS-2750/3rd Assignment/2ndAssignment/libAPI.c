#include <stdio.h>
#include <string.h>
#include "stream.h"

int main(int argc, char *argv[]) {
    if (strcmp(argv[1],"updateStream") == 0) {

    } else if (strcmp(argv[1],"isUserInStream") == 0){
        printf("%d",isUserInStream(argv[2],argv[3]));
    } else if (strcmp(argv[1],"createUsername") == 0) {

    } else if (strcmp(argv[1],"addUser") == 0) {
        addUser(argv[2],argv[3]);
    } else if (strcmp(argv[1],"printUser") == 0) {

    } else if (strcmp(argv[1],"removeUser") == 0) {

    } else if (strcmp(argv[1],"createFiles") == 0) {

    } else if (strcmp(argv[1],"nameStream") == 0) {
        printf("%s\n",nameStream(argv[2]));
    } else if (strcmp(argv[1],"nameStreamData") == 0) {

    } else if (strcmp(argv[1],"nameStreamUsers") == 0) {

    }
    return 0;
}

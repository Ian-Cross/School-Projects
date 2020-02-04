#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

FILE * openfile(const char* filename, char* privalage);
void indent(FILE* outputFile, int indentation);
char* emptyBuffer(char* buffer);

int main(int argc, char const *argv[]) {
    /* creating the files */
    FILE * inputFile;
    FILE * outputFile;
    char* outFileName = NULL;
    List * list = NULL;

    /* makes sure there are two files included */
    if (argc != 2){
        printf("Please make sure to enter a input file\n");
        exit(1);
    }

    list = createList();


    /* opening the input file */
    inputFile = openfile(argv[1],"r");

    /* Creating the output file name, and opening it */
    outFileName = (char*)malloc(sizeof(char)*strlen(argv[1]) + 1);
    if (outFileName == NULL){
        printf("There wasn't enough space\n");
        exit(1);
    }
    strcpy(outFileName,argv[1]);
    outFileName[strlen(outFileName)-1] = '\0';
    outputFile = openfile(outFileName,"w");
    free(outFileName);

    char token = fgetc(inputFile);
    char* buffer = (char*)malloc(sizeof(char));
    if (buffer == NULL){
        printf("There is not enough space\n");
        exit(1);
    }

    int bufferLength = 0;
    int inQuote = -1;
    int include = -1;
    int comment = -1;
    int multiLineComment = -1;
    int escapeChar = -1;
    int inc = 0;
    char lastChar = '\0';
    char c;

    strcpy(buffer,"\0");

    while (token != EOF){

        bufferLength = strlen(buffer);

        buffer = realloc(buffer,bufferLength+3);
        if (buffer == NULL){
            printf("Im sorry there isnt enough space\n");
            exit(1);
        }
        buffer[bufferLength] = token;
        buffer[bufferLength + 1] = '\0';


        if (escapeChar == 1){
            escapeChar *= -1;
        } else {
            if (token == '\\'){
                escapeChar *= -1;
            } else {
                /* Making sure to ignore everything inside of a string */
                if (token == '\"') inQuote*= -1;

                /* if it finds an include, ignore everything until the  > */
                if (strcmp(buffer,"#include") == 0 && inQuote == -1) {
                    list = addItem(list,buffer);
                    include = 1;
                }
                if (include == 1 && token == '>') include = -1;

                if (include == 1 && token == '\"'){
                    inc++;
                    if (inc == 2) {
                        inc = 0;
                        include = -1;
                    }
                }

                /* Ignoring everything that could be a multi Line comment */
                if (strcmp(buffer,"/") == 0 && inQuote == -1) {
                    c = fgetc(inputFile);
                    if (c == '*'){
                        token = c;
                        multiLineComment = 1;
                        continue;
                    } else if (c == '/') {
                        token = c;
                        comment = 1;
                        continue;
                    } else {
                        ungetc(c,inputFile);
                    }
                }
                if (multiLineComment == 1 && token == '*') {
                    c = fgetc(inputFile);
                    if (c != '/'){
                        ungetc(c,inputFile);
                    } else {
                        token = c;
                        buffer[bufferLength+1] = '/';
                        multiLineComment = -1;
                        lastChar = 27;
                    }
                }

                if (comment == 1 && token == '\n') {
                    comment = -1;
                    buffer[bufferLength] = '\0';
                    lastChar = 27;
                    token = '/';
                }

                if (inQuote == -1 && comment == -1 && include == -1 && multiLineComment == -1){
                    switch (token) {
                        case '(':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,"(");
                            buffer = emptyBuffer(buffer);
                            break;
                        case ')':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,")");
                            buffer = emptyBuffer(buffer);
                            break;
                        case ',':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,",");
                            buffer = emptyBuffer(buffer);
                            break;
                        case '>':
                            if (lastChar == '-'){
                                buffer[bufferLength] = '\0';
                                buffer[bufferLength-1] = '\0';
                                if (buffer[0] != '\0'){
                                    list = addItem(list,buffer);
                                }
                                list = addItem(list,"->");
                                buffer = emptyBuffer(buffer);
                            }
                            break;
                        case '.':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,".");
                            buffer = emptyBuffer(buffer);
                            break;
                        case '=':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,"=");
                            buffer = emptyBuffer(buffer);
                            break;
                        case '/':
                            if (lastChar == 27) {
                                list = addItem(list,"\0");
                                buffer[bufferLength+2] = '\0';
                                list = addItem(list,buffer);
                                buffer = emptyBuffer(buffer);
                                lastChar = '5';
                            } else {
                                buffer[bufferLength] = '\0';
                                if (buffer[0] != '\0'){
                                    list = addItem(list,buffer);
                                }
                                list = addItem(list,"/");
                                buffer = emptyBuffer(buffer);
                            }
                            break;
                        case '*':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,"*");
                            buffer = emptyBuffer(buffer);
                            break;
                        case '+':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,"+");
                            buffer = emptyBuffer(buffer);
                            break;
                        case '-':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,"-");
                            buffer = emptyBuffer(buffer);
                            break;
                        case ';':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,";");
                            buffer = emptyBuffer(buffer);
                            break;
                        case '{':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,"{");
                            buffer = emptyBuffer(buffer);
                            break;
                        case '}':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                            }
                            list = addItem(list,"}");
                            buffer = emptyBuffer(buffer);
                            break;
                        case '\n':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                                buffer = emptyBuffer(buffer);
                            }
                            break;
                        case ' ':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                                buffer = emptyBuffer(buffer);
                            }
                            break;
                        case '\t':
                            buffer[bufferLength] = '\0';
                            if (buffer[0] != '\0'){
                                list = addItem(list,buffer);
                                buffer = emptyBuffer(buffer);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        token = fgetc(inputFile);
    }

    free(buffer);
    fclose(inputFile);

    Prog* myProgram;

    myProgram = createProgram(list);

    printProgram(myProgram,outputFile);

    deleteProgram(myProgram);
    free(myProgram);

    deleteList(list);
    fclose(outputFile);
    return 0;
}

/*************
 *Function Name: openfile()
 *Function Description: Will open or create a file with the given name and permission
 *Parameters In: The name of the file to open, the permissions for the file.
 *Parameters output: a opened pointer to a file
 *Errors: quits if the file could note be open
 *************/
FILE * openfile(const char* filename, char* privalage){
    FILE* newfile = NULL;

    /* Opening the file */
    newfile = fopen(filename,privalage);
    if (newfile == NULL) {
      /* quit when the file DNE or couldn't be opened */
      printf("Sorry, file: %s could not be opened\n", filename);
      exit(1);
    }

    return newfile;
}

/*************
 *Function Name: emptyBuffer()
 *Function Description: Will take in a string and reset it back to nothing
 *Parameters In: the strign to empty
 *Parameters output: a empty string
 *Errors: N/A
 *************/
 char* emptyBuffer(char* buffer){
     free(buffer);
     buffer = malloc(sizeof(char));
     buffer[0] = '\0';
     return buffer;
 }

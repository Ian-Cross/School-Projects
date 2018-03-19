#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedElement.h"

void printFileHeader();
void printFileFooter();
void addBuffer(char ** buffer,char c);
void addBufferS(char ** buffer, char * c);
void resetBuffer(char ** buffer);

int main(int argc, char const *argv[]) {

    if (argc != 2){
        printf("I'm sorry, please enter the filename as a argument\n");
        exit(1);
    }

    int length = strlen(argv[1]);
    /* Create a copy of the file name */
    char* newName = malloc(sizeof(char) * (length + 1));
    strcpy(newName,argv[1]);
    /* Changing the file extension in the copy */
    newName[length-4] = '\0';
    strcat(newName,"php");

    FILE* infile = fopen(argv[1],"r");
    FILE* textFile;
    /* Add the starting stuff to a header file */
    printFileHeader();
    char c;
    int i;
    int size = 0;
    int height = 0;
    /* A couple of strings to be used as buffers through the parsing */
    char* text = malloc(sizeof(char) + 1);
    char* buffer = malloc(sizeof(char) + 1);
    char* tags = malloc(sizeof(char) + 1);
    char* link = malloc(sizeof(char) + 1);
    char* name = malloc(sizeof(char) + 1);
    char* value = malloc(sizeof(char) + 1);

    /* Parse the file and build the linked element */
    while ((c = fgetc(infile)) != EOF){
        if (c != '.'){
            printf("Something went really wrong %c\n",c);
            exit(1);
        }
        size = 0;
        height = 0;
        c = fgetc(infile);

        switch (c) {
            /* HEADERS */
            case 'h':
                /* start of the html tag */
                printf("\t\t\t<h");
                c = fgetc(infile);
                c = fgetc(infile);
                /* Check if its just an empty header tag */
                if (c != ')'){
                    addBuffer(&buffer,c);
                    while ((c = fgetc(infile)) != '\n'){
                        /* skip over white space and division chars */
                        if (c == ',' || c == ')') {
                            if (strlen(buffer)){
                                addBuffer(&tags,' ');
                                addBufferS(&tags,buffer);
                                resetBuffer(&buffer);
                            }
                            /* Skip leading spaces */
                            while (1){
                                c = fgetc(infile);
                                if (c != ' ') break;
                            }
                            ungetc(c,infile);
                            continue;
                        }
                        if (c == ' ' || c == '\t'){
                            addBuffer(&buffer,c);
                            continue;
                        }
                        /* Terminating condition */
                        if (c == '\n') break;
                        /* if it finds the size tag, set the value accordingly */
                        if (strcmp(buffer,"size=") == 0){
                            size = c - '0';
                            resetBuffer(&buffer);
                        /* If if finds the text tag, build the string and set the value */
                        } else if (strcmp(buffer,"text=\"") == 0){
                            do {
                                addBuffer(&text,c);
                            } while ((c = fgetc(infile)) != '\"');
                            resetBuffer(&buffer);
                        /* Otherwise just keep looking */
                        } else {
                            addBuffer(&buffer,c);
                        }
                    }
                } else {
                    c = fgetc(infile);
                }
                /* Add in the default values */
                if (size == 0) size = 3;
                if (strlen(text) == 0) addBufferS(&text,"HEADER\0");

                /* Close out the html tag with the given values */
                printf("%d%s>%s</h%d>\n",size,tags,text,size);
                resetBuffer(&buffer);
                resetBuffer(&text);
                resetBuffer(&tags);
                break;
            /* BUTTON */
            case 'b':
                c = fgetc(infile);
                c = fgetc(infile);
                /* Check if its just an empty header tag */
                if (c != ')'){
                    addBuffer(&buffer,c);
                    while ((c = fgetc(infile)) != '\n'){
                        /* skip over white space and division chars */
                        if (c == ',' || c == ')') {
                            if (strlen(buffer)){
                                addBuffer(&tags,' ');
                                addBufferS(&tags,buffer);
                                resetBuffer(&buffer);
                            }
                            /* Skip leading spaces */
                            while (1){
                                c = fgetc(infile);
                                if (c != ' ') break;
                            }
                            ungetc(c,infile);
                            continue;
                        }
                        if (c == ' ' || c == '\t'){
                            addBuffer(&buffer,c);
                            continue;
                        }
                        /* Terminating condition */
                        if (c == '\n') break;
                        /* if it finds the size tag, set the value accordingly */
                        if (strcmp(buffer,"link=\"") == 0){
                                do {
                                    addBuffer(&link,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"name=\"") == 0){
                                do {
                                    addBuffer(&text,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"formLink=\"") == 0){
                                do {
                                    addBuffer(&value,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else {
                            addBuffer(&buffer,c);
                        }
                    }
                } else {
                    c = fgetc(infile);
                }
                /* Add in the default values */
                if (strlen(text) == 0) addBufferS(&text,"BUTTON\0");
                if (strlen(link) == 0) addBufferS(&link," ");

                /*Printing out the html tag full of data */
                printf("\t\t\t<form class=\"buttonForm\" method=\"POST\"action=\"%s\">\n",link);
                printf("\t\t\t\t<input %s type=\"submit\" ",tags);
                if (strlen(value)) printf("name=\"%s\" ",value);
                printf("value=\"%s\" >\n",text);
                printf("\t\t\t</form>\n");
                resetBuffer(&buffer);
                resetBuffer(&text);
                resetBuffer(&link);
                resetBuffer(&value);
                resetBuffer(&tags);
                break;
            /* HORRIZONTAL LINE */
            case 'd':
                printf("\t\t\t<hr>\n");
                /* Skip over all the characters associated */
                for (i = 0; i < 3; i++) {
                    c = fgetc(infile);
                }
                break;
            /* EXECUTABLE */
            case 'e':
               c = fgetc(infile);
               c = fgetc(infile);
               /* Check if its just an empty header tag */
               if (c != ')'){
                   addBuffer(&buffer,c);
                   while ((c = fgetc(infile)) != '\n'){
                       /* skip over white space and division chars */
                       if (c == ',' || c == ')') {
                           if (strlen(buffer)){
                               addBuffer(&tags,' ');
                               addBufferS(&tags,buffer);
                               resetBuffer(&buffer);
                           }
                           /* Skip leading spaces */
                           while (1){
                               c = fgetc(infile);
                               if (c != ' ') break;
                           }
                           ungetc(c,infile);
                           continue;
                       }
                       if (c == ' ' || c == '\t'){
                           addBuffer(&buffer,c);
                           continue;
                       }
                       /* Terminating condition */
                       if (c == '\n') break;
                       /* if it finds the size tag, set the value accordingly */
                       if (strcmp(buffer,"exe=\"") == 0){
                               do {
                                   addBuffer(&link,c);
                               } while ((c = fgetc(infile)) != '\"');
                               resetBuffer(&buffer);
                           /* Otherwise just keep looking */
                       } else {
                           addBuffer(&buffer,c);
                       }
                   }
               } else {
                   c = fgetc(infile);
               }

               /*Printing out the html tag full of data */
               printf("\t\t\t<?PHP\n\t\t\texec('./%s',$output,$status);\n",link);
               printf("\t\t\tif ($status == 2){\n");
               printf("\t\t\t\texec('./bin/%s',$output,$status);\n",link);
               printf("\t\t\t\tif ($status == 2){\n");
               printf("\t\t\t\t\texec('./bin/%s',$output,$status);\n",link);
               printf("\t\t\t\t}\n\t\t\t} ?>\n");
               resetBuffer(&buffer);
               resetBuffer(&text);
               resetBuffer(&link);
               resetBuffer(&tags);
                break;
            /* INPUT */
            case 'i':
                c = fgetc(infile);
                c = fgetc(infile);
                /* Check if its just an empty header tag */
                if (c != ')'){
                    addBuffer(&buffer,c);
                    while ((c = fgetc(infile)) != '\n'){
                        /* skip over white space and division chars */
                        if (c == ',' || c == ')') {
                            if (strlen(buffer)){
                                addBuffer(&tags,' ');
                                addBufferS(&tags,buffer);
                                resetBuffer(&buffer);
                            }
                            /* Skip leading spaces */
                            while (1){
                                c = fgetc(infile);
                                if (c != ' ') break;
                            }
                            ungetc(c,infile);
                            continue;
                        }
                        if (c == ' ' || c == '\t'){
                            addBuffer(&buffer,c);
                            continue;
                        }
                        /* Terminating condition */
                        if (c == '\n') break;
                        /* if it finds the size tag, set the value accordingly */
                        if (strcmp(buffer,"action=\"") == 0){
                                do {
                                    addBuffer(&link,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                                printf("\t\t\t<form %s method=\"post\" action=\"%s\">\n",tags,link);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"text=\"") == 0){
                                do {
                                    addBuffer(&text,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"name=\"") == 0){
                                do {
                                    addBuffer(&name,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"value=\"") == 0){
                                do {
                                    addBuffer(&value,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                                printf("\t\t\t\t %s <input type=\"text\" name=\"%s\" value=\"%s\"><br>\n",text,name,value);
                                resetBuffer(&value);
                                resetBuffer(&text);
                                resetBuffer(&name);
                            /* Otherwise just keep looking */
                        } else {
                            addBuffer(&buffer,c);
                        }
                    }
                } else {
                    c = fgetc(infile);
                }

                /*Printing out the  end of the html tag */
                printf("\t\t\t\t<input class=\"submitButton\" type=\"submit\" value=\"Submit\" >\n");
                printf("\t\t\t</form>\n");
                resetBuffer(&buffer);
                resetBuffer(&text);
                resetBuffer(&link);
                resetBuffer(&tags);
                resetBuffer(&name);
                break;
            /* LINK */
            case 'l':
                c = fgetc(infile);
                c = fgetc(infile);
                /* Check if its just an empty header tag */
                if (c != ')'){
                    addBuffer(&buffer,c);
                    while ((c = fgetc(infile)) != '\n'){
                        /* skip over white space and division chars */
                        if (c == ',' || c == ')') {
                            if (strlen(buffer)){
                                addBuffer(&tags,' ');
                                addBufferS(&tags,buffer);
                                resetBuffer(&buffer);
                            }
                            while (1){
                                c = fgetc(infile);
                                if (c != ' ') break;
                            }
                            ungetc(c,infile);
                            continue;
                        }
                        if (c == ' ' || c == '\t'){
                            addBuffer(&buffer,c);
                            continue;
                        }
                        /* Terminating condition */
                        if (c == '\n') break;
                        /* if it finds the size tag, set the value accordingly */
                        if (strcmp(buffer,"link=\"") == 0){
                                do {
                                    addBuffer(&link,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"text=\"") == 0){
                                do {
                                    addBuffer(&text,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else {
                            addBuffer(&buffer,c);
                        }
                    }
                } else {
                    c = fgetc(infile);
                }
                /* Add in the default values */
                if (strlen(text) == 0) addBufferS(&text,"LINK\0");
                if (strlen(link) == 0) addBufferS(&link," ");

                /*Printing out the html tag full of data */
                printf("\t\t\t<a %s href=\"%s\">%s</a>\n",tags,link,text);
                resetBuffer(&buffer);
                resetBuffer(&text);
                resetBuffer(&link);
                resetBuffer(&tags);
                break;
            /* IMAGE */
            case 'p':
                c = fgetc(infile);
                c = fgetc(infile);
                /* Check if its just an empty header tag */
                if (c != ')'){
                    addBuffer(&buffer,c);
                    while ((c = fgetc(infile)) != '\n'){
                        /* skip over white space and division chars */
                        if (c == ',' || c == ')') {
                            if (strlen(buffer)){
                                addBuffer(&tags,' ');
                                addBufferS(&tags,buffer);
                                resetBuffer(&buffer);
                            }
                            while (1){
                                c = fgetc(infile);
                                if (c != ' ') break;
                            }
                            ungetc(c,infile);
                            continue;
                        }
                        if (c == ' ' || c == '\t'){
                            addBuffer(&buffer,c);
                            continue;
                        }
                        /* Terminating condition */
                        if (c == '\n') break;
                        /* if it finds the size tag, set the value accordingly */
                        if (strcmp(buffer,"image=\"") == 0){
                            do {
                                addBuffer(&link,c);
                            } while ((c = fgetc(infile)) != '\"');
                            resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"size=\"") == 0){
                            do {
                                addBuffer(&text,c);
                            } while ((c = fgetc(infile)) != 'x');
                            height = atoi(text);
                            c = fgetc(infile);
                            resetBuffer(&text);
                            do {
                                addBuffer(&text,c);
                            } while ((c = fgetc(infile)) != '\"');
                            size = atoi(text);
                            resetBuffer(&buffer);
                            resetBuffer(&text);
                            /* Otherwise just keep looking */
                        } else {
                            addBuffer(&buffer,c);
                        }
                    }
                } else {
                    c = fgetc(infile);
                }
                /* Add in the default values */
                if (size == 0) {
                    height = 100;
                    size = 100;
                }
                if (strlen(link) == 0) addBufferS(&link," ");

                /*Printing out the html tag full of data */
                printf("\t\t\t<img src=\"%s\" height=\"%d\" width=\"%d\" %s>\n",link,height,size,tags);
                resetBuffer(&buffer);
                resetBuffer(&link);
                resetBuffer(&tags);
                break;
            /* RADIO BUTTONS */
            case 'r':
                c = fgetc(infile);
                c = fgetc(infile);
                /* Check if its just an empty header tag */
                if (c != ')'){
                    addBuffer(&buffer,c);
                    while ((c = fgetc(infile)) != '\n'){
                        /* skip over white space and division chars */
                        if (c == ',' || c == ')') {
                            if (strlen(buffer)){
                                addBuffer(&tags,' ');
                                addBufferS(&tags,buffer);
                                resetBuffer(&buffer);
                            }
                            /* Skip leading spaces */
                            while (1){
                                c = fgetc(infile);
                                if (c != ' ') break;
                            }
                            ungetc(c,infile);
                            continue;
                        }
                        if (c == ' ' || c == '\t'){
                            addBuffer(&buffer,c);
                            continue;
                        }
                        /* Terminating condition */
                        if (c == '\n') break;
                        /* if it finds the size tag, set the value accordingly */
                        if (strcmp(buffer,"action=\"") == 0){
                                do {
                                    addBuffer(&link,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                                printf("\t\t\t<form %s method=\"post\" action=\"%s\">\n",tags,link);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"name=\"") == 0){
                                do {
                                    addBuffer(&text,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"value=\"") == 0){
                                do {
                                    addBuffer(&name,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                                printf("\t\t\t\t<input");
                                /* first round flag */
                                if (size == 0) {
                                    printf(" checked");
                                    size = 1;
                                }
                                printf(" type=\"radio\" name=\"%s\" value=\"%s\"> %s <br>\n",text,name,name);
                                resetBuffer(&name);
                            /* Otherwise just keep looking */
                        } else {
                            addBuffer(&buffer,c);
                        }
                    }
                } else {
                    c = fgetc(infile);
                }

                /*Printing out the  end of the html tag */
                printf("\t\t\t\t<input class=\"submitButton\" type=\"submit\" value=\"Submit\" >\n");
                printf("\t\t\t</form>\n");
                resetBuffer(&buffer);
                resetBuffer(&text);
                resetBuffer(&link);
                resetBuffer(&tags);
                resetBuffer(&name);
                break;
            /* TEXT */
            case 't':
                c = fgetc(infile);
                c = fgetc(infile);
                printf("\t\t\t<div>\n");
                /* Check if its just an empty header tag */
                if (c != ')'){
                    addBuffer(&buffer,c);
                    while ((c = fgetc(infile)) != '\n'){
                        /* skip over white space and division chars */
                        if (c == ',' || c == ')') {
                            if (strlen(buffer)){
                                addBuffer(&tags,' ');
                                addBufferS(&tags,buffer);
                                resetBuffer(&buffer);
                            }
                            /* Skip leading spaces */
                            while (1){
                                c = fgetc(infile);
                                if (c != ' ') break;
                            }
                            ungetc(c,infile);
                            continue;
                        }

                        if (c == ' ' || c == '\t'){
                            addBuffer(&buffer,c);
                            continue;
                        }
                        /* Terminating condition */
                        if (c == '\n') break;
                        /* Insertion of text directly */
                        if (strcmp(buffer,"text=\"") == 0){
                            do {
                                addBuffer(&text,c);
                            } while ((c = fgetc(infile)) != ')');
                            text[strlen(text)-1] = '\0';
                            ungetc(c,infile);
                            resetBuffer(&buffer);
                            printf("\t\t\t\t%s\n",text);
                        /* If they are trying to redirect a file FIX ME */
                        } else if (strcmp(buffer,"file=\"") == 0){
                            do {
                                addBuffer(&text,c);
                            } while ((c = fgetc(infile)) != '\"');
                            ungetc(c,infile);
                            resetBuffer(&buffer);
                            textFile = fopen(text,"r");
                            if (textFile == NULL){
                                printf("OOPSIES %s\n",text);
                            }
                            printf("\t\t\t\t");
                            while ((c = fgetc(textFile)) != EOF) {
                                printf("%c",c);
                                if (c == '\n') printf("\t\t\t\t");
                            }
                            printf("\n");
                            fclose(textFile);
                        /* Otherwise just keep looking */
                        } else {
                            addBuffer(&buffer,c);
                        }
                    }
                } else {
                    c = fgetc(infile);
                }
                /* Add in the default values */
                if (strlen(text) == 0) {
                    addBufferS(&text,"Text\0");
                    printf("\t\t\t\t%s\n",text);
                }

                /* Close out the html tag */
                printf("\t\t\t</div>\n");
                resetBuffer(&buffer);
                resetBuffer(&text);
                resetBuffer(&tags);
                break;
            /* LINE BREAK */
            case 'z':
                printf("\t\t\t<br>\n");
                /* Skip over all the characters associated */
                for (i = 0; i < 3; i++) {
                    c = fgetc(infile);
                }
                break;
            /* CHECK BOX */
            case 'c':
                c = fgetc(infile);
                c = fgetc(infile);
                /* Check if its just an empty header tag */
                if (c != ')'){
                    addBuffer(&buffer,c);
                    while ((c = fgetc(infile)) != '\n'){
                        /* skip over white space and division chars */
                        if (c == ',' || c == ')') {
                            if (strlen(buffer)){
                                addBuffer(&tags,' ');
                                addBufferS(&tags,buffer);
                                resetBuffer(&buffer);
                            }
                            /* Skip leading spaces */
                            while (1){
                                c = fgetc(infile);
                                if (c != ' ') break;
                            }
                            ungetc(c,infile);
                            continue;
                        }
                        if (c == ' ' || c == '\t'){
                            addBuffer(&buffer,c);
                            continue;
                        }
                        /* Terminating condition */
                        if (c == '\n') break;
                        /* if it finds the size tag, set the value accordingly */
                        if (strcmp(buffer,"action=\"") == 0){
                                do {
                                    addBuffer(&link,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                                printf("\t\t\t<form %s method=\"post\" action=\"%s\">\n",tags,link);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"text=\"") == 0){
                                do {
                                    addBuffer(&text,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"name=\"") == 0){
                                do {
                                    addBuffer(&name,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                            /* Otherwise just keep looking */
                        } else if (strcmp(buffer,"value=\"") == 0){
                                do {
                                    addBuffer(&value,c);
                                } while ((c = fgetc(infile)) != '\"');
                                resetBuffer(&buffer);
                                printf("\t\t\t\t %s <input type=\"checkbox\" name=\"%s\" value=\"%s\"><br>\n",text,name,value);
                                resetBuffer(&value);
                                resetBuffer(&text);
                                resetBuffer(&name);
                            /* Otherwise just keep looking */
                        } else {
                            addBuffer(&buffer,c);
                        }
                    }
                } else {
                    c = fgetc(infile);
                }

                /*Printing out the  end of the html tag */
                printf("\t\t\t\t<input class=\"submitButton\" type=\"submit\" value=\"Submit\" >\n");
                printf("\t\t\t</form>\n");
                resetBuffer(&buffer);
                resetBuffer(&text);
                resetBuffer(&link);
                resetBuffer(&tags);
                resetBuffer(&name);
                break;
            default:
                break;
        }
    }

    printFileFooter();
    fclose(infile);

    free(newName);
    return 0;
}

/*************
 *Function Name: printFileHeader()
 *Function Description: starts of the php file with the starting
  values by printing them to stdout
 *Parameters In: N/A
 *Parameters output: N/A
 *Errors: N/A
 *************/
void printFileHeader(){
    printf("<?PHP\n"
                "\tif (isset($_GET['login'])){\n"
                    "\t\t$username = $_GET['username'];\n"
                    "\t\t$textArea = \"Please select a stream to start!\";\n"
                "\t} else if (isset($_POST['changeStream'])){\n"
                    "\t\t$currentPost = getLastPost($_GET['stream']);\n"
                    "\t\tload($_GET['username'],$_GET['stream'],none);"
                    "\t\t$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);\n"
                    "\t\tupdateUserFile($_GET['username'],$_GET['stream'],$currentPost,\"date\");\n"
                "\t} else if (isset($_POST['nextPost'])){\n"
                    "\t\t$currentPost = $_GET['currPost'] + 1;\n"
                    "\t\tif ($currentPost > getLastPost($_GET['stream'])) $currentPost = $_GET['currPost'];\n"
                    "\t\t$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);\n"
                    "\t\tupdateUserFile($_GET['username'],$_GET['stream'],$currentPost,$_GET['sort']);\n"
                "\t} else if (isset($_POST['lastPost'])){\n"
                    "\t\t$currentPost = $_GET['currPost'] -1;\n"
                    "\t\t\tif ($currentPost <= 0) $currentPost = 1;\n"
                    "\t\t$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);\n"
                    "\t\tupdateUserFile($_GET['username'],$_GET['stream'],$currentPost,$_GET['sort']);\n"
                "\t} else if (isset($_POST['checkForNew'])){\n"
                    "\t\tload($_GET['username'],$_GET['stream'],none);"
                    "\t\t$textArea = updateViewer($_GET['username'],$_GET['stream'],$_GET['currPost']);\n"
                    "\t\tupdateUserFile($_GET['username'],$_GET['stream'],$currentPost,$_GET['sort']);\n"
                "\t} else if (isset($_POST['markAll'])){\n"
                    "\t\texec(\"./2ndAssignment/viewAPI.py markAll \".$_GET['username'].\" \".$_GET['stream'],$output,$status);\n"
                    "\t\t$currentPost = getLastPost($_GET['stream']);\n"
                    "\t\t$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);\n"
                "\t} else if (isset($_POST['toggle'])){\n"
                "\t}\n\n"

                "\tfunction get($form){\n"
                    "\t\t$paramList = \"?\";\n"
                    "\t\tforeach ($form as $key => $value) {\n"
                        "\t\t\t$paramList .= \"&\".$key.\"=\".$value;\n"
                    "\t\t}\n"
                    "\t\treturn $paramList;\n"
                "\t}\n\n"

                "\tfunction getLastPost($streamName) {\n"
                    "\t\texec(\"./2ndAssignment/viewAPI.py getLastRead \".$_GET['username'].\" \".$streamName,$output,$status);\n"
                    "\t\tif ($status) {\n"
                        "\t\t\techo \"Get last Post \".$status;\n"
                    "\t\t}\n"
                    "\t\treturn ( (int)$output[0] );\n"
                "\t}\n\n"

                "\tfunction load($username,$streamName,$sort){\n"
                    "\t\texec(\"./2ndAssignment/viewAPI.py loadPosts \".$username.\" \".$streamName.\" \".$sort,$output,$status);\n"
                "\t}\n\n"

                "\tfunction updateUserFile($username,$streamName,$currentPost,$sort) {\n"
                    "\t\tif ($streamName != \"All\" and $sort != \"name\") {\n"
                        "\t\t\texec(\"./2ndAssignment/viewAPI.py updateUserFile \".$username.\" \".$streamName,$output,$status);\n"
                        "\t\t\tif ($status) {\n"
                            "\t\t\t\techo \"Update user Stream \".$status;\n"
                        "\t\t\t}\n"
                    "\t\t}\n"
                "\t}\n\n"

                "\tfunction updateViewer($username,$streamName,$currentPost) {\n"
                    "\t\texec(\"./2ndAssignment/viewAPI.py getPost \".$username.\" \".$currentPost,$textArea,$status);\n"
                    "\t\tif ($status) {\n"
                        "\t\t\techo \" update Viewer \".$status;\n"
                    "\t\t}\n"
                    "\t\treturn $textArea;\n"
                "\t}\n\n"

                "\tfunction formatPost($post) {\n"
                    "\t\tif ($post[0] == 'P')\n"
                        "\t\t\techo $post;\n"
                    "\t\telse {\n"
                        "\t\t\t$index = 3;\n"
                        "\t\t\techo $post[0].\"\\n\";\n"
                        "\t\t\techo $post[1].\"\\n\";\n"
                        "\t\t\techo $post[2].\"\\n\";\n"
                        "\t\t\twhile ($post[$index][0] == '-') {\n"
                        "\t\t\t\techo $post[$index].\"\\n\";\n"
                        "\t\t\t\t$index++;\n"
                        "\t\t\t}\n"
                    "\t\t}\n"
                "}\n\n"

            "?>\n"
            "<!DOCTYPE html>\n"
                "\t<html>\n"
                    "\t\t<head>\n"
                        "\t\t\t<meta charset=\"utf-8\">\n"
                        "\t\t\t<title>Assignment 3</title>\n"
                        "\t\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\">\n"
                        "\t\t</head>\n\n"
                        "\t\t<body>\n");
}

/*************
 *Function Name: printFileFooter()
 *Function Description: closes out the php file with the final few
  lines by printing them to stdout
 *Parameters In: N/A
 *Parameters output: N/A
 *Errors: N/A
 *************/
void printFileFooter(){
    printf("\t\t</body>\n"
           "\t</html>\n");
}

/*************
 *Function Name: addBuffer()
 *Function Description: will take in the given char and add it to
  the end of the given string
 *Parameters In: (char **) The address of the string to append to (char) the character to append
 *Parameters output: N/A
 *Errors: If the program runs out of memory the program will quit
 *************/
void addBuffer(char ** buffer, char c){
    char * tempBuffer;
    int length = strlen(*buffer);
    /* give space to hold the old string */
    tempBuffer = malloc(sizeof(char) * length);
    if (tempBuffer == NULL){
        printf("Sorry Something went wrong space could not be created\n");
        exit(1);
    }
    strcpy(tempBuffer,*buffer);

    /* Increase the space in the old string */
    *buffer = realloc(*buffer,length+3);
    if (*buffer == NULL){
        printf("Sorry Something went wrong space could not be created\n");
        exit(1);
    }
    /* copy the old data back over and add the new data */
    strcpy(*buffer,tempBuffer);
    (*buffer)[length] = c;
    (*buffer)[length+1] = '\0';
}

/*************
 *Function Name: addBufferS()
 *Function Description: will take in the given string and add it to
  the end of the given string
 *Parameters In: (char **) The address of the string to append to (char *) the string to append
 *Parameters output: N/A
 *Errors: If the program runs out of memory the program will quit
 *************/
void addBufferS(char ** buffer, char * c){
    char * tempBuffer;
    int length = strlen(*buffer);
    /* give space to hold the old string */
    tempBuffer = malloc(sizeof(char) * length);
    if (tempBuffer == NULL){
        printf("Sorry Something went wrong space could not be created\n");
        exit(1);
    }
    strcpy(tempBuffer,*buffer);
    /* Increase the space in the old string */
    *buffer = realloc(*buffer,length+strlen(c)+1);
    if (*buffer == NULL){
        printf("Sorry Something went wrong space could not be created\n");
        exit(1);
    }
    /* copy the old data back over and add the new data */
    strcpy(*buffer,tempBuffer);
    strcat(*buffer,c);
}

/*************
 *Function Name: resetBuffer()
 *Function Description: will empty the given string, cleaning up the memory
 *Parameters In: (char **) the address of the string to clear
 *Parameters output: N/A
 *Errors: If the program runs out of memory the program will quit
 *************/
void resetBuffer(char ** buffer){
    /* Clean up the memory */
    free((*buffer));
    /* reset it to empty */
    (*buffer) = malloc(sizeof(char) + 1);
    if (*buffer == NULL){
        printf("Sorry Something went wrong space could not be created\n");
        exit(1);
    }
    strcpy((*buffer),"\0");
}

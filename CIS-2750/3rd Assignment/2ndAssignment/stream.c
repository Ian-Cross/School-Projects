#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream.h"

/*************
*Function Name: updateStream
*Function Description: Adds a new post to the stream specified in streamName, if the
 stream does not exist it will create
*Parameters In: (userPost Struct) The new post data
*Parameters output: N/A
*Errors: N/A
*************/
void updateStream(UserPost *post){
    FILE* file = NULL, * datafile = NULL;
    char* fileName, * datafileName;
    fileName = nameStream(post->streamName);
    file = fopen(fileName,"r+");
    if (file == NULL){
        printf("I'm sorry, but that stream does not exist\n");
    } else if (!isUserInStream(post->username,post->streamName)) {
        printf("I'm sorry, but user: %s is not subscribed to stream: %s and cannot post there\n",post->username,post->streamName);
        fclose(file);
    } else {
        fseek(file,0,SEEK_END);
        fprintf(file, "Sender: %s\n",post->username);
        fprintf(file, "Date: %s",post->date);
        fprintf(file, "%s",post->text);
        datafileName = nameStreamData(post->streamName);
        datafile = fopen(datafileName,"a");
        fprintf(datafile, "%ld\n",ftell(file));
    }
    free(fileName);
}

/*************
*Function Name: isUserInStream
*Function Description: checks to see if the given user is in the streamUsers file
*Parameters In: (string) The username to check (string) The stream to search
*Parameters output: (int) a success flag returning 0 is the user isn't in the stream, 1 otherwise
*Errors: N/A
*************/
int isUserInStream(char* username,char* stream){
    /* Creates the file name for the streamUsers file */
    char* infileName = nameStreamUsers(stream);
    FILE* infile = fopen(infileName,"r");
    if (infile == NULL){
        printf("Not stream file\n");
        return 0;
    }
    char line[512];
    int length,match = 0;

    /*cycles through the file line by line */
    while (fgets(line,512,infile) != NULL){
        match = 1;
        length = strlen(username);
        /* tries to match up the given username with the one on the current line
           it stops looking as soon as something doesn't match */
        int i;
        for (i = 0; i < length; i++){
            if (username[i] != line[i]){
                match = 0;
                break;
            }
        }
        if (match) break;
    }

    /* clean up memory */
    free(infileName);
    fclose(infile);
    return match;
}

/*************
*Function Name: createUsername
*Function Description: Take all the arguments from the command line and fits them all together
*Parameters In: (array of strings) holding all the parts of the username entered
*Parameters output: (string) The newly crafted username
*Errors: N/A
*************/
char* createUsername(int argc, char * argv[]){
    int removeFlag = 0;
    int length = 1;
    int i;

    char* username = malloc(sizeof(char) + 1);
    if (strcmp(argv[1],"-r") == 0) removeFlag = 1;

    /* Collect all of the names after the execution and flag, to build the username */
    for (i = removeFlag+1; i < argc; i++){
        /* Save the Old username */
        length += strlen(argv[i]);
        char* holder = malloc(sizeof(char)*(length));
        strcpy(holder,username);
        /* Extend the old username */
        username = realloc(username,sizeof(char)*length+1);
        strcpy(username,holder);
        /* Add a space if necessary */
        if (i-removeFlag > 1) strcat(username," ");
        strcat(username,argv[i]);
        free(holder);
    }
    return username;
}

/*************
*Function Name: adduser
*Function Description: Adds a user with the given username to all of the streams specified
 in the list, if a stream does not exist it will be created
*Parameters In: (string) The username to be added; (string) A comma seperated list of streams
*Parameters output: N/A
*Errors: N/A
*************/
void addUser(char* username, char* list){
    char delim[] = ", \n";
    char *token;

    /* Break up the list of stream names given by the user */
    token = strtok(list, delim);
    while( token != NULL )
    {
        /* Creates each of the files for the new stream */
        createFiles(token);
        /* puts the spcified username into each of the files with 0 messages read*/
        printUser(username,token);
        token = strtok(NULL, delim);
    }
}

/*************
*Function Name: printUser
*Function Description: Prints out the given username with 0 messages read into the given stream
*Parameters In: (string) The username to be added; (string) A stream to add the user to
*Parameters output: N/A
*Errors: N/A
*************/
void printUser(char* userName, char* stream){
    FILE* file;
    /* create the filename for the given stream */
    char* fileName = nameStreamUsers(stream);

    /* Checks if the user already exists in that file
       if they don't, add them; if the do just quit*/
    if (!isUserInStream(userName,stream)){
        file = fopen(fileName,"a");
        fprintf(file, "%s: 0\n",userName);
        fclose(file);
    } else {
        printf("The user: %s, is already in the stream: %s\n",userName,stream);
    }
    free(fileName);
}

/*************
*Function Name: removeUser
*Function Description: Removes a user with the given username from all of the streams
 specified in the list.
*Parameters In: (String) The username to be removed; (string) A comma seperated list of streams
*Parameters output: N/A
*Errors: N/A
*************/
void removeUser(char* username, char* list){
    char delim[] = ", \n";
    char* token;
    char line[512];
    FILE* infile;
    FILE* outfile;
    char* infileName;
    int length, match;

    /* get the first token */
    token = strtok(list, delim);

    /* walk through other tokens */
    while( token != NULL )
    {
        infileName = nameStreamUsers(token);
        infile = fopen(infileName,"r");
        outfile = fopen("2ndAssignment/messages/tmp.txt","a+");
        if (outfile == NULL) {
            printf("File is broken\n");
        }
        while (fgets(line,512,infile) != NULL){
            match = 1;
            length = strlen(username);
            /* If they are different lengths, don't even bother checking */
            if (line[length] != ':'){
                match = 0;
            } else {
                /* search through the given line to see if the user on that line matches the given name */
                int i;
                for (i = 0; i < length; i++){
                    if (username[i] != line[i]){
                        match = 0;
                    }
                }
            }
            /* just print out any users that don't match the given one */
            if (!match){
                fprintf(outfile, "%s",line);
            }
        }
        /* remove the old user file */
        remove(infileName);
        /* rename the temperary file to the right name */
        rename("2ndAssignment/messages/tmp.txt",infileName);
        /* clean up the memory */
        fclose(infile);
        fclose(outfile);
        free(infileName);
        token = strtok(NULL, delim);
    }
}

/*************
*Function Name: createFiles
*Function Description: This function just ensures that all the files for a stream exist
*Parameters In: (String) The name of the stream for the files
*Parameters output: N/A
*Errors: N/A
*************/
void createFiles(char* streamName){
    FILE* file;
    char* fileName;

    /* Create the stream file, open it with append, so that if the
       file does not exist it will be created but if it does nothing
       will be overwritten */
    fileName = nameStream(streamName);
    file = fopen(fileName,"a");
    free(fileName);
    fclose(file);

    /* Create the streamData file, open it with append, so that if the
       file does not exist it will be created but if it does nothing
       will be overwritten */
    fileName = nameStreamData(streamName);
    file = fopen(fileName,"a+");
    free(fileName);
    fclose(file);

    /* Create the streamUser file, open it with append, so that if the
       file does not exist it will be created but if it does nothing
       will be overwritten */
    fileName = nameStreamUsers(streamName);
    file = fopen(fileName,"a+");
    free(fileName);
    fclose(file);
}

/*************
*Function Name: nameStream
*Function Description: This function will concatinate together the propername for the stream file
*Parameters In: (String) The name of the stream for the files
*Parameters output: (String) The name for the stream file
*Errors: program will quit if malloc fails, or return NULL if the stream name is empty
*************/
char* nameStream(char* streamName){
    /* make sure there is a stream name */
    if (streamName == NULL){
        printf("Error occured when creating a file name\n");
        return NULL;
    }
    char* fileName = malloc(sizeof(char)*(strlen(streamName)+50));
    if (fileName == NULL){
        printf("Im sorry there wasn't enough space\n");
        exit(1);
    }
    /* Put together the stream file name */
    strcpy(fileName,"2ndAssignment/messages/");
    strcat(fileName,streamName);
    strcat(fileName,"Stream.txt\0");
    return fileName;
}

/*************
*Function Name: nameStreamData
*Function Description: This function will concatinate together the propername for the stream data file
*Parameters In: (String) The name of the stream for the files
*Parameters output: (String) The name for the stream file
*Errors: program will quit if malloc fails, or return NULL if the stream data name is empty
*************/
char* nameStreamData(char* streamName){
    /* Make sure there is a stream name */
    if (streamName == NULL){
        printf("Error occured when creating a file name\n");
        return NULL;
    }
    char* fileName = malloc(sizeof(char)*(strlen(streamName)+50));
    if (fileName == NULL){
        printf("Im sorry there wasn't enough space\n");
        exit(1);
    }
    /* Put together the stream data file name */
    strcpy(fileName,"2ndAssignment/messages/");
    strcat(fileName,streamName);
    strcat(fileName,"StreamData.txt\0");
    return fileName;
}

/*************
*Function Name: nameStreamUsers
*Function Description: This function will concatinate together the proper name for the stream Users file
*Parameters In: (String) The name of the stream for the files
*Parameters output: (String) The name for the stream Users file
*Errors: program will quit if malloc fails, or return NULL if the stream name is empty
*************/
char* nameStreamUsers(char* streamName){
    /* Make sure there is a streamName */
    if (streamName == NULL){
        printf("Error occured when creating a file name\n");
        return NULL;
    }
    char* fileName = malloc(sizeof(char)*(strlen(streamName)+50));
    if (fileName == NULL){
        printf("Im sorry there wasn't enough space\n");
        exit(1);
    }
    /* Build together the streamUsers filename */
    strcpy(fileName,"2ndAssignment/messages/");
    strcat(fileName,streamName);
    strcat(fileName,"StreamUsers.txt\0");
    return fileName;
}

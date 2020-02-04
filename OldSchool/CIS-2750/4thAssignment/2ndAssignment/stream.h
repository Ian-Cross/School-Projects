#ifndef __icross__Stream__
#define __icross__Stream__

typedef struct userPost{
    char* username;
    char* streamName;
    char* date;
    char* text;
} UserPost;

/*************
*Function Name: updateStream
*Function Description: Adds a new post to the stream specified in streamName, if the
 stream does not exist it will create
*Parameters In: (userPost Struct) The new post data
*Parameters output: N/A
*Errors: N/A
*************/
void updateStream(UserPost* myStruct);

/*************
*Function Name: isUserInStream
*Function Description: checks to see if the given user is in the streamUsers file
*Parameters In: (string) The username to check (string) The stream to search
*Parameters output: (int) a success flag
*Errors: N/A
*************/
int isUserInStream(char* username,char* stream);

/*************
*Function Name: adduser
*Function Description: Adds a user with the given username to all of the streams specified
 in the list, if a stream does not exist it will be created
*Parameters In: (string) The username to be added; (string) A comma seperated list of streams
*Parameters output: N/A
*Errors: N/A
*************/
void addUser(char* username, char* list);

char* createUsername(int argc, char ** args);

void printUser(char* userName, char* stream);

/*************
*Function Name: removeUser
*Function Description: Removes a user with the given username from all of the streams
 specified in the list.
*Parameters In: (String) The username to be removed; (string) A comma seperated list of streams
*Parameters output: N/A
*Errors: N/A
*************/
void removeUser(char* username, char* list);

/*************
*Function Name: createFiles
*Function Description: This function just ensures that all the files for a stream exist
*Parameters In: (String) The name of the stream for the files
*Parameters output: N/A
*Errors: N/A
*************/
void createFiles(char* streamName);

/*************
*Function Name: nameStream
*Function Description: This function will concatinate together the propername for the stream file
*Parameters In: (String) The name of the stream for the files
*Parameters output: (String) The name for the stream file
*Errors: program will quit if malloc fails, or return NULL if the stream name is empty
*************/
char* nameStream(char* streamName);

/*************
*Function Name: nameStreamData
*Function Description: This function will concatinate together the propername for the stream data file
*Parameters In: (String) The name of the stream for the files
*Parameters output: (String) The name for the stream file
*Errors: program will quit if malloc fails, or return NULL if the stream data name is empty
*************/
char* nameStreamData(char* streamName);

/*************
*Function Name: nameStreamUsers
*Function Description: This function will concatinate together the proper name for the stream Users file
*Parameters In: (String) The name of the stream for the files
*Parameters output: (String) The name for the stream Users file
*Errors: program will quit if malloc fails, or return NULL if the stream name is empty
*************/
char* nameStreamUsers(char* streamName);


#endif

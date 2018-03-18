#ifndef __icross_FileOpening__
#define __icross_FileOpening__

/**
 * openFIle
 * Opens up a given file with given permisions and checks if the file exits
 * IN: char* fileName: the name of the file to be opened, char* type: the wanted permissions of the file
 * OUT: FILE* : returns the open file to be edited
 * ERROR: quits when the file DNE, or cannot be opened
 */
FILE* openFile(char* fileName,char* type);

#endif

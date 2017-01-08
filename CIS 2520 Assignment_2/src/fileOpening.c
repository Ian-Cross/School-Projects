#include <stdio.h>

FILE* openFile(char* fileName,char* type)
{
	FILE* file;
	//opens the file with the given permissions
	file = fopen(fileName,type);

	//quits, and returns a fail case if the file cannot be opened or DNE
	if (file == NULL){
		printf("Could Not open file: %s\n", fileName);
		return NULL;
	}
	//gives back the open file
	return file;
}

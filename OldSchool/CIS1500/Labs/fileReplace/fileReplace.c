#include "fileReplace.h"

int main(int argc, char **argv) {
  FILE *file;
  FILE *newFile;
  char input[255];

  if (argc != 3) {
    printf("Not enough arguments (FileName, OutputName)\n");
    exit(1);
  }

  file = fopen(argv[1], "r");

  if (file == NULL) {
    printf("Given file does not exist");
    exit(1);
  }

  newFile = fopen(argv[2], "w");

  if (newFile == NULL) {
    printf("The given file does not exist\n");
    exit(1);
  }

  while (fgets(input, 254, file) != NULL) {
    for (int i = 0; i < strlen(input); i++) {
      if (input[i] == 'a' || input[i] == 'e') {
        input[i] = 'c';
      }
    }
    fprintf(newFile, "%s", input);
  }

  fclose(file);
  fclose(newFile);

  printf("Program is done, quitting now.\n");

  return 0;
}

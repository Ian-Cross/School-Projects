#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GetFileName(char fileName[])
{
    printf("Please enter the name of the file you wish to scramble\n");
    scanf("%s",fileName);
    return;
}

void ScrambleWord(char word[],int wordSize)
{
    if (wordSize == 0)
    {
        return;
    }

    int numMiddleLetters = wordSize-2;
    int spotsLeft[50];
    int spotInArray;

    for (int i = 0; i < 50; i++)
        spotsLeft[i] = i;

    for (int i = 0; i < numMiddleLetters; i++)
    {
        spotsLeft[i] = i+1;
    }

    int squished = 0;
    printf("%c",word[0]);

    while (numMiddleLetters-squished >= 1)
    {
        spotInArray = rand()%(numMiddleLetters-squished);
        int spotInWord = spotsLeft[spotInArray];
        printf("%c", word[spotInWord]);

        for(int i = spotInArray; i < numMiddleLetters-1-squished; i++)
        {
            spotsLeft[i] = spotsLeft[i+1];
        }

        squished++;
    }

    printf("%c", word[wordSize-1]);
}

void ProcessText(char fileName[])
{
    char letter;
    char inputWord[50];
    int wordSize = 0;
    FILE * inFile;

    for (int i = 0; i < 50; i++)
    {
        inputWord[i] = '0';
    }

    inFile = fopen(fileName,"r");

    if (inFile == NULL)
    {
        printf("Could not open file myfile.txt.\n");
        return;
    }

    while (!feof(inFile))
    {
        letter = fgetc(inFile);
        //printf("'%c' : %d\n",letter,letter);
        if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122))
        {
            inputWord[wordSize] = letter;
            wordSize++;
        }
        else
        {
            ScrambleWord(inputWord,wordSize);
            printf("%c",letter);
            wordSize = 0;
        }
    }

    // Done with file, so close it
    fclose(inFile);
    return;
}

int main (int argc, char * argv[])
{
    srand(time(NULL));
    char fileName[50] = "";
    GetFileName(fileName);
    ProcessText(fileName);
    return 0;
}

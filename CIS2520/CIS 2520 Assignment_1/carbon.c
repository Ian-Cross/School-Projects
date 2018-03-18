/*********************
* Ian Cross
* 0911085
* September 16 2016
* Assignemnt 1
*********************/

#include <stdio.h>

/***************************
This function takes in two values and switches them for one another
***************************/
void swap(char *carbon, char *b) {
  //change the values from a to b and b to a
  char temp;
  temp = *carbon;
  *carbon = *b;
  *b = temp;
}

/***************************
This function recusivly cycles through the word, calling another funtion
to swap the letters and printing the permutations when they have been found
***************************/
void print(char *carbon, int index, int length) {
    if(index == length-1) {
        printf("%s\n", carbon);
    } else {
        for(int j = index; j < length; j++) {
            //swap up the characters
            swap(carbon + index, carbon + j);
            //recall the funtion moving along to the next letters
            print(carbon, index + 1, length);
            //swap back the characters
            swap(carbon + index, carbon + j);
        }
    }
}

/***************************
This function starts off the process with the definition of the word to be permutated
***************************/
void question1(){
  char carbon[20] = "carbon"; //defining the array
  print(carbon,0,6);
  printf("Question 1 is complete.\n\n");
  getchar();
}

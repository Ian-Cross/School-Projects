/*********************
* Ian Cross
* 0911085
* September 16 2016
* Assignemnt 1
*********************/

#include <stdio.h>
#include "carbon.c"
#include "ackermann.c"
#include "newton.c"

/***************************
This function displays a menu for the user
and calls the correct function when the user decides
***************************/
int main() {
  char answer = 't';
  system("clear");

  printf("Which question would you like to see the output for?\n");

  //getting input from the user, completing the correct action based on the input
  while (answer != 'q')
  {
    printf("press '1' for Carbon Permutation\npress '2' for the Ackermann\npress '3' To find Newton Squares\npress q to quit\n");
    answer = getchar();

    system("clear");

    switch (answer) {
      case '1':
        question1(); //carbon permutaitons
        break;
      case '2':
        question2(); //ackermann function
        break;
      case '3':
        question3(); //Newton's squares
        break;
      case 'q':
        break;
      default:
        printf("Please enter in a correct character.\n\n");
        break;
    }
  }
  system("clear");
  //cleaning up the buffer
  int ch; while ((ch = getchar()) != '\n' && ch != EOF);
  return 0;
}

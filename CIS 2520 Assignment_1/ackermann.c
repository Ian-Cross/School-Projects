/*********************
* Ian Cross
* 0911085
* September 16 2016
* Assignemnt 1
*********************/

#include <stdio.h>

/***************************
This function recursively finds the root to match the given square within
the given range using newtons method
***************************/
int ackermann(int m, int n){
  if (m == 0 && (n > 0 || n == 0)){
    n++; //the terminate case
  }
  else if (n == 0 && m > 0){
    n = ackermann(m-1,1); //recalling the funciton with new values
  }
  else if (n > 0 && m > 0){
    n = ackermann(m-1,ackermann(m,n-1)); //recalling the funciton with new values
  }
  return n;
}

/***************************
This function gathers the correct and usable information from the user
then calls the calculation function, outputting the result
***************************/
void question2(){
  getchar();
  int m = -1,n = -1;
  printf("This is the ackermann function.\n");
  //getting information from the user
  while (m < 0 || m > 5) {
    printf("Please enter a value between (0 and 5) for m: ");
    scanf("%d",&m);
  }
  while (n < 0 || n > 5-m) { //anything out of this range will overflow the integer value.
    printf("Please enter a value between (0 and %d) for n: ",5-m);
    scanf("%d",&n);
  }
  //printing and calculating the ackermann number.
  printf("The Ackermann number for the coordinates (%d,%d) is: %d\n",m,n,ackermann(m,n));
  printf("Question 2 is complete.\n\n");
  getchar();
}

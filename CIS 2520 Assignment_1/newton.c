/*********************
* Ian Cross
* 0911085
* September 16 2016
* Assignemnt 1
*********************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>

/***************************
This function recursivly calculates the root of the given square to the precision of epsilon
each function call changes the root until it finds one that is in the acceptable range
***************************/
double newtonRecusion(double x, double a, double epsilon){
  if ((fabs(a*a - x) <= epsilon)) //comparing the root to its square and seeing if it is in range
  {
    return a;
  }else{
    return newtonRecusion(x,(a+x/a)/2,epsilon); //calls the function again with a new value for a
  }
}

/***************************
This function iterativly calculates the root of the given square to the precision of epsilon
each time the loop occurs it changes the root until it finds one that is in the acceptable range
***************************/
double newtonIterative(double x, double a, double epsilon){
  while (a != 0) //fail case
  {
    if ((fabs(a*a - x) <= epsilon)) //comparing the root to its square and seeing if it is in range
    {
      return a;
    }else{
      a = (a+x/a)/2; //changing the value of a to move closer to the correct root of the square
    }
  }
  return 0;
}

/***************************
This fuction calls the two calculation functions
The user has two choices, they can enter values in manually or
test the speed of finding 100 million roots.
***************************/
void question3(){
  struct timeb t_start, t_current;
  double t_diff;
  double root, radicand, epsilon;
  int answer = 0;

  printf("Press 1 to find a square yourself, press 2 to time the functions\n");
  scanf("%d",&answer);
  if (answer == 2)
  {
    ftime(&t_start); //starting the stopwatch
    for (int i = 1; i < 100000000; i++) {
      newtonRecusion(i,1,0.0000001);
    }
    ftime(&t_current); //stopping the stopwatch

    //Calculation of the elapsed time from the members of the timeb structs
    t_diff = ((double) (1000.0 * (t_current.time - t_start.time) + (t_current.millitm - t_start.millitm)))/1000;

    printf("Newton Recursive took %.3lf seconds to calculate 100 million squares\n",t_diff); //printing out the calculated time elapesd

    ftime(&t_start); //starting the stopwatch again
    for (int i = 1; i < 100000000; i++) {
      newtonIterative(i,1,0.0000001);
    }
    ftime(&t_current); //stopping the stopwatch

    //Calculation of the elapsed time from the members of the timeb structs
    t_diff = ((double)(1000.0 * (t_current.time - t_start.time) + (t_current.millitm - t_start.millitm)))/1000;

    printf("Newton Iterative took %.3lf seconds to calculate 100 million squares\n",t_diff); //printing out the calculated time elapesd

  } else if (answer == 1) {
    //collecting user information
    printf("Please enter in a radicand: ");
    scanf("%lf",&radicand);
    printf("\nNow enter a Epsilon: ");
    scanf("%lf",&epsilon);
    printf("\n\n");

    root = newtonRecusion(radicand,1,epsilon);

    printf("Newton Recursion found %lf as a square\n",root);//printing out the calculated time elapsed

    root = newtonIterative(radicand,1,epsilon);

    printf("newton Iterative found %lf as a square\n",root); //printing out the calculated time elapesd
  } else {
    printf("Wrong answer quitting this question\n");
  }

    printf("Question 3 is complete.\n\n");
    getchar();
}

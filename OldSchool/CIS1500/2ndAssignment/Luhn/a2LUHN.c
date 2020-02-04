/****************************
CIS1500 Credit Card Validator
Ian Cross
Nov 27/15
This program will take a credit number from
a user and will test if it is valid by
using the Luhn algorithm
****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readCC (int creditCardNumber[]);
void isValid (int creditCardNumber[]);
int runLuhn (int creditCardNumber[]);

int main (void)
{
    //declare variables
    int creditCardNumber[16];

    //Quitting the program form a bad return from the readCC function
    if (readCC(creditCardNumber) == -1)
    {
        return 0;
    }

    isValid(creditCardNumber);

    return 0;
}

/*************************
readCC: reads the credit card number from the user
In: int creaditCardNumber[]
Out: returns a good value if the input from the user was 16 digits
*************************/
int readCC(int creditCardNumber[])
{
    //Declaring variables
    int x;
    char userInputString[100];

    //Prompt the user for a credit card number and input up to 99 characters
    printf("Please enter a credit card number to test\nenter it like this ################: ");
    fgets(userInputString,100,stdin);

    //Testing if the user inputted 16 digits, testing for 17 to take into account the '/n' character
    if (strlen(userInputString) != 17)
    {
        printf("There isn't 16 digits there, please try again\n");
        return -1;
    }

    //converting from character values to integer values
    for (x = 15; x >= 0; x--)
    {
        creditCardNumber[x] = userInputString[x] - '0';
    }
    return 1;
}

/*************************
isValid: Calls the runLuhn() function and interprets the input
In: int creditCardNumber[]
Out: nothing
*************************/
void isValid(int creditCardNumber[])
{
    //The credit card will be valid if the returned value is 0
    if (runLuhn(creditCardNumber) == 0)
    {
        printf("The credit card number is valid!\n");
    }
    else
    {
        printf("The credit card number is not valid!\n");
    }
    return;
}

/*************************
runLuhn: Applies the Luhn algorithm to the crdit card number to test validitiy
In: int creditCardNumber[]
Out: returns the value of the remainder of the sum of the digits divided by 10
*************************/
int runLuhn(int creditCardNumber[])
{
    //declare variables
    int x;
    int sum = 0;

    //Iterates through the crdit card number array backward
    for (x = 15; x >= 0; x--)
    {
        //if the current indecy is an even number
        if ((x%2) == 0)
        {
            //doubling the value and adding the two digits togetherwhen its over 10
            creditCardNumber[x] *= 2;
            if (creditCardNumber[x] >= 10)
            {
                creditCardNumber[x] -=9;
            }
        }
        //Summing all the values together
        sum += creditCardNumber[x];
    }

    return (sum%10);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct stack {
  double data;
  struct stack* next;
} Stack;

/************
*Function Name: createNode
*Function Description: takes the given data, creates memory for the new node and puts the data in
*Parameters In: double containing the data wishing to be added to a node
*Parameters output: returns the newly created node
*Errors: N/A
************/
Stack *createNode(double data);

/************
*Function Name: pushback
*Function Description: Adds a new node to the front of the list
*Parameters In: double, containing the data to be added to the list. Stack, the list head to be appended
*Parameters output: returns the newly updated list
*Errors: N/A
************/
Stack *pushback(Stack* operands, double data);

/************
*Function Name: popoff
*Function Description: Removes the first node from the list
*Parameters In: Stack, the list head to be trunkcated
*Parameters output: returns the newly updated list
*Errors: If there is nothing in the list
************/
Stack *popoff(Stack* operands);

/************
*Function Name: printStack
*Function Description: prints out the list in a nice line
*Parameters In: Stack, the list to be printed
*Parameters output: N/A
*Errors: N/A
************/
void printStack(Stack* operands);

int main(int argc, char const *argv[]) {
  char* arg = malloc(sizeof(argv[1])+1);
  strcpy(arg,argv[1]);
  if (argc != 2){
    printf("Please execute the program with the correct format\n");
  } else {
    Stack* operands = NULL;
    int length = strlen(arg);
    for (int i = 0; i < length; i++){
      if (isdigit(arg[i])){
        operands = pushback(operands,arg[i] - '0');
      } else {
        double op1 = 0,op2 = 0,answer = 0;
        if (operands != NULL)
          op1 = operands->data;
        operands = popoff(operands);
        if (operands != NULL)
          op2 = operands->data;
        operands = popoff(operands);

        if (arg[i] == '+'){
          answer = op1 + op2;
          operands = pushback(operands,answer);
        } else if (arg[i] == '-'){
          answer = op2 - op1;
          operands = pushback(operands,answer);
        } else if (arg[i] == '*'){
          answer = op1 * op2;
          operands = pushback(operands,answer);
        } else if (arg[i] == '/'){
          if (fabs(op1 - 0) == 0){
            printf("Devided by zero, oops\n");
            exit(1);
          }
          answer = op2 / op1;
          operands = pushback(operands,answer);
        }
      }
    }
    printf("%s = ", arg);
    printStack(operands);
  }
  return 0;
}

Stack *createNode(double data){
  Stack* newList = malloc(sizeof(Stack));
  newList->data = data;
  newList->next = NULL;
  return newList;
}

Stack *pushback(Stack* operands, double data){
  Stack* newOperand =  malloc(sizeof(Stack));
  if (newOperand == NULL){
    newOperand = createNode(data);
  } else {
    newOperand = createNode(data);
    newOperand->next = operands;
  }
  return newOperand;
}

Stack *popoff(Stack* operands){
  Stack* newOperand =  malloc(sizeof(Stack));
  newOperand = operands;
  if (newOperand == NULL){
    printf("Something went wrong, tried to do an operation on an empty list\n");
    exit(1);
  }
  newOperand = newOperand->next;
  return newOperand;
}

void printStack(Stack* operands){
  Stack* operand = malloc(sizeof(Stack));
  operand = operands;
  if (operand == NULL){
    printf("The list is empty\n");
  } else {
    while (operand != NULL){
      printf("%.2lf ",operand->data);
      operand = operand->next;
    }
    printf("\n");
  }
}

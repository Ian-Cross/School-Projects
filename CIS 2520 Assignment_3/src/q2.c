#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define NUM_NODES 21
#define NUM_INFO 10
typedef int Array[NUM_INFO];
typedef Array Matrix[NUM_NODES];

void printMatrix(Matrix matrix);
void makeHeap(Matrix matrix);
int getKey(Array array);
void hasKids(Matrix matrix, int index);

int main(int argc, char const *argv[]) {
  FILE * file;
  char line[100]; //to hold the line read in
  Matrix matrix; // a 20x10 array holding the values
  int i = 1,j = 0;
  char delim[2] = " \n";
  char* token;

  //opening the file
  file = fopen("assests/data.txt","r");
  if (file == NULL) {
    //quit when the file DNE or couldn't be opened
    printf("Sorry, file could not be opened");
    return 0;
  }

  while(fgets(line,100,file)){
    //get the first token
    token = strtok(line, delim);
    //cycle through to the end to get the rest of the tokens
    while( token != NULL )
    {
      matrix[i][j] = atoi(token); //convert the string to a int and store it in te matrix
      token = strtok(NULL,delim);
      j++;
    }
    i++;
    j = 0;
  }
  fclose(file);

  //printMatrix(matrix); //print out the matrix before manipulation
  //printf("\n");
  makeHeap(matrix); //organizes the array into a heap
  printMatrix(matrix); //prints out the new heap
  printf("\n");
  return 0;
}

/*************
 *Function Name: printMatrix
 *Function Description: cycles through the matrix printing out all of the values
 *Parameters In: Matrix; a two dimentional array full of 2 digit numbers
 *Parameters output: N/A
*************/
void printMatrix(Matrix matrix){
  for (int i = 1; i < NUM_NODES; i++){
    for (int j = 0; j < NUM_INFO; j++){
      printf("%d ",matrix[i][j]);
    }
    printf("\n");
  }
}

/*************
 *Function Name: makeTree
 *Function Description:
 *Parameters In: Matrix; a two dimentional array full of 2 digit numbers
 *Parameters output: N/A
*************/
void makeHeap(Matrix matrix){
  int lastParentIndex = floor(NUM_NODES/2);
  for (int i = lastParentIndex; i > 0; i--){
    hasKids(matrix,i);
  }
}

/*************
 *Function Name: hasKids
 *Function Description:
 *Parameters In: Matrix; a two dimentional array full of 2 digit numbers, int; a value to track the position in the array
 *Parameters output: N/A
*************/
void hasKids(Matrix matrix, int index){
  //fill key values with illigitamate bas values
  int leftChild = 999999999;
  int rightChild = 999999999;
  int parent = 999999999;
  int temp;

  //getting the current parent
  parent = getKey(matrix[index]);
  //if the parent has a left child, store that value
  if (index*2 < NUM_NODES) leftChild = getKey(matrix[index*2]);
  //if the parent has a right child, store that value
  if (index*2+1 < NUM_NODES) rightChild = getKey(matrix[index*2+1]);

  //finds the smallest of the two chidren
  if (leftChild < rightChild){
    //if the parent is bigger than the child
    if (parent > leftChild){
      //swap all the values stored in the parent and the child
      for (int j = 0; j < NUM_INFO; j++){
        temp = matrix[index][j];
        matrix[index][j] = matrix[index*2][j];
        matrix[index*2][j] = temp;
      }
      //recursively check if the parent, now the child broke heap rules
      hasKids(matrix,index*2);
    }
  } else {
    //if the parent is bigger than the child
    if (parent > rightChild){
      //swap all the values stored in the parent and the child
      for (int j = 0; j < NUM_INFO; j++){
        temp = matrix[index][j];
        matrix[index][j] = matrix[index*2+1][j];
        matrix[index*2+1][j] = temp;
      }
      //recursively check if the parent, now the child broke heap rules
      hasKids(matrix,index*2+1);
    }
  }
}

/*************
 *Function Name: getKey
 *Function Description: addes the first three item in the array to create the key
 *Parameters In: Array; and array containing 10 2 digit values 3 for key and 7 for info
 *Parameters output: a interger value to be used as the key
*************/
int getKey(Array array){
  //add the first 3 values to create the key
  return array[0] + array[1] + array[2];
}

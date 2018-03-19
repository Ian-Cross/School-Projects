#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defining a tree that holds a string for a value
typedef struct treeNode {
  char* data;
  struct treeNode* leftChild;
  struct treeNode* rightChild;
} TreeNode;

//defining a stack to hold the nodes of the tree
typedef struct stackNode {
  TreeNode* item;
  struct stackNode* next;
}StackNode;

//Stack functions
StackNode* createStackNode(TreeNode* toAdd);
StackNode* pushback(TreeNode* topush,StackNode* stack);
StackNode* popoff(StackNode* stack);
void printStack(StackNode* stack);

//tree functions
void printTree(TreeNode* tree, int height);
void printTreeNode(TreeNode* toprint);
int treeHeight(TreeNode* tree, int count);
TreeNode* makeTree(char* string);
TreeNode* createTreeNode(char* data);
void preOrder(TreeNode* tree);
void inOrder(TreeNode* tree);
void postOrder(TreeNode* tree);
double calculate(TreeNode* tree);
int stillVar(TreeNode* tree);
TreeNode* findAndReplace(TreeNode* tree, char* find, char* replace);

int main(int argc, char *argv[]) {
  //creates the tree
  TreeNode* tree = NULL;
  tree = makeTree(argv[1]);
  int height = treeHeight(tree,0);
  int answer = 0;
  char find[] = "xx";
  char replace[] = "x.xx";


  while (answer != 7) {
    //display the menu
    system("clear");
    printf("1. Display\n");
    printf("2. PreOrder\n");
    printf("3. InOrder\n");
    printf("4. PostOrder\n");
    printf("5. Update\n");
    printf("6. Calculate\n");
    printf("7. Exit\n");

    //get the answer and clear the new line character
    scanf("%d",&answer);
    getchar();

    switch (answer) {
      case 1:
        for (int i = 1; i <= height+1; i++){
          printf("%d   ",i);
        }
        printf("\n");
        printTree(tree,0);
        break;
      case 2:
        preOrder(tree);
        printf("\n");
        break;
      case 3:
        inOrder(tree);
        printf("\n");
        break;
      case 4:
        postOrder(tree);
        printf("\n");
        break;
      case 5:
        printf("Please then the variable you want to replace\n");
        scanf("%s",find);
        printf("Please enter the value you want to put there\n");
        scanf("%s",replace);
        getchar();
        tree = findAndReplace(tree,find,replace);
        break;
      case 6:
        if (stillVar(tree)){
          printf("There are still variables, please replace those before calculating\n");
        } else {
          printf("The total is %lf\n",calculate(tree));
        }
        break;
      default:
        break;
    }
    if (answer != 7) {
      printf("Press enter to continue: ");
      getchar();
    }
  }
  return 0;
}

/*************
 *Function Name: makeTree
 *Function Description: This is the main funciton, it parses equation, breaking each
 *item of significance into nodes, it then utalizes a stack to store the nodes. when
 *it finds a group of nodes that form a subtree, it pops them off and creates the tree
 *pushing the new subtree node onto the stack
 *Parameters In: String; holding the arethmetic expression
 *Parameters output: a fully loaded and formated tree
*************/
TreeNode* makeTree(char* string){
  StackNode* stack = NULL;
  TreeNode* newNode = NULL;
  //get the length of the expression
  int length = strlen(string);
  //allocate enough memory to hold the string
  char* token = malloc(sizeof(char)*length);
  for (int i = 0; i < length; i++){
    //ignore open brackets
    if (string[i] == '('){
      continue;
    //when an operator is found
    }else if (string[i] == '+' || string[i] == '-' || string[i] == '/' || string[i] == '*'){
      //making sure no empty nodes get added
      if (strcmp(token,"") != 0) {
        //creating a node of a tree with the data
        newNode = createTreeNode(token);
        //adding the tree node to the stack
        stack = pushback(newNode,stack);
      }
      //converting the operator to a string
      char addch[2] = "4\0";
      addch[0] = string[i];
      //creating a node of a tree with the operator
      newNode = createTreeNode(addch);
      //adding the tree node to the stack
      stack = pushback(newNode,stack);
      strcpy(token,"");
    }else if (string[i] == ')'){
      if (strcmp(token,"") != 0){
        //creating a node of a tree with the data
        newNode = createTreeNode(token);
        //adding the tree node to the stack
        stack = pushback(newNode,stack);
      }
      stack = popoff(stack);
      strcpy(token,"");
      //this is where you pop off and make a subtree
    }else {
      //converting the current character to a string and adding to the end of the token
      char addch[2] = "4\0";
      addch[0] = string[i];
      strcat(token,addch);
    }
  }
  TreeNode *newTree = stack->item;
  return newTree;
}

/*************
 *Function Name: printTree
 *Function Description: using a in order traversal of the tree, each node is visited
 *the spacing is caclulated, based of how deep in the recusion the node is. The tree is printed sideways
 *with the root of the tree furthest left.
 *Parameters In: TreeNode, holding the fully loaded tree. int, the depth of the node
 *Parameters output: N/A
*************/
void printTree(TreeNode* tree, int height){
  //an in order traverse of the tree
  if(tree){
    printTree(tree->leftChild, height+4);
    //adding spacing
    if (height > 0){
      for (int i = 0; i < height; i++){
          printf(" ");
      }
    }
    printf("%s\n", tree->data);
    printTree(tree->rightChild, height+4);
  }
}

/*************
 *Function Name: treeHeight
 *Function Description: calculates the height of the longest branch in the tree
 *Parameters In: TreeNode, holding the fully loaded tree. int, the counter for the height of the branches
 *Parameters output: returns the value of the height of the largest branch
*************/
int treeHeight(TreeNode* tree,int count){
  if (tree->leftChild != NULL){
    count++;
    count = treeHeight(tree->leftChild,count);
  }
  return count;
}

/*************
 *Function Name: createTreeNode
 *Function Description: creates a node for a tree with the given data
 *Parameters In: String; holding the data to be added
 *Parameters output: A tree node fully filled with data and null pointers
*************/
TreeNode* createTreeNode (char * data){
  TreeNode* newNode = malloc(sizeof(TreeNode));
  newNode->data = malloc(sizeof(data));
  strcpy(newNode->data,data);
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;

  return newNode;
}

/*************
 *Function Name: preOrder
 *Function Description: moves through the tree and prints them out in 'preOrder' fashion
 *Parameters In: TreeNode, a node containing the entire tree
 *Parameters output: N/A
*************/
void preOrder(TreeNode* tree){
  if (tree != NULL){
    printf("%s ",tree ->data);
    preOrder(tree->leftChild);
    preOrder(tree->rightChild);
  }
}

/*************
 *Function Name: inOrder
 *Function Description: moves through the tree and prints them out in 'inOrder' fashion
 *Parameters In: TreeNode, a node containing the entire tree
 *Parameters output: N/A
*************/
void inOrder(TreeNode* tree){
  if (tree != NULL){
    if (tree->leftChild) printf("( ");
    inOrder(tree->leftChild);
    printf("%s ",tree ->data);
    inOrder(tree->rightChild);
    if (strcmp(tree->data,"+") == 0 || strcmp(tree->data,"-") == 0
      || strcmp(tree->data,"*") == 0 || strcmp(tree->data,"/") == 0) printf(") ");
  }
}

/*************
 *Function Name: postOrder
 *Function Description: moves through the tree and prints them out in 'postOrder' fashion
 *Parameters In: TreeNode, a node containing the entire tree
 *Parameters output: N/A
*************/
void postOrder(TreeNode* tree){
  if (tree != NULL){
    postOrder(tree->leftChild);
    postOrder(tree->rightChild);
    printf("%s ",tree ->data);
  }
}

/*************
 *Function Name: calculate
 *Function Description: takes in the tree and cycles through it looking for operators
 *once and operator is found, it uses that operator on its two children. passing
 *the answer back up
 *Parameters In: TreeNode, a node containing the entire tree
 *Parameters output: Double, a value containing the answer to the equation
*************/
double calculate(TreeNode* tree){
  double answer = 0;
  if (tree != NULL){
    if (strcmp(tree->data,"+") == 0 || strcmp(tree->data,"-") == 0 || strcmp(tree->data,"*") == 0 || strcmp(tree->data,"/") == 0){
      double left = calculate(tree->leftChild);
      double right = calculate(tree->rightChild);
      char data = tree->data[0];
      switch (data) {
        case '+':
          answer = left + right;
          break;
        case '-':
          answer = left - right;
          break;
        case '*':
          answer = left * right;
          break;
        case '/':
          answer = left / right;
          break;
      }
    } else {
      sscanf(tree->data,"%lf",&answer);
    }
  }
  return answer;
}

/*************
 *Function Name: stillVar
 *Function Description: Looks through the tree to find if any
 *of the variables are yet to be replaced.
 *Parameters In: TreeNode, a node containing the entire tree
 *Parameters output: Returns a 1 if it finds a variable, 0 otherwise
*************/
int stillVar(TreeNode* tree){
  int flag = 0;
  if (tree != NULL){
    //using a post order traversal to search for any variables that will mess up the calculation
    flag = stillVar(tree->leftChild);
    flag = stillVar(tree->rightChild);
    if (tree->data[0] == 'x'){
      flag = 1;
    }
  }
  return flag;
}

/*************
 *Function Name: findAndReplace
 *Function Description: looks through the tree for the given variable,
 *once the variable is found, it replaces it in the tree with the given value
 *Parameters In: TreeNode, a node containing the entire tree. String, holding the variable name.
 *String, holding the value to replace the variable wiht
 *Parameters output: The newly updated tree
*************/
TreeNode* findAndReplace(TreeNode* tree, char* find, char* replace){
  if (tree != NULL){
    //using a post order traversal to move through the tree
    findAndReplace(tree->leftChild,find,replace);
    findAndReplace(tree->rightChild,find,replace);
    //if the data in the current node mathes what we are looking for the values are switched in
    if (strcmp(tree->data,find) == 0){
      strcpy(tree->data,replace);
    }
  }
  return tree;
}

/*************
 *Function Name: pushback
 *Function Description: Puts a given tree node onto the top of the stack
 *Parameters In: TreeNode, a node waiting to be pushed onto the stack. StackNode, the current stackpointer
 *Parameters output: A new stackpointer that has been updated with the new node
*************/
StackNode* pushback(TreeNode* topush, StackNode* stack){
  StackNode * newStack = malloc(sizeof(StackNode));
  newStack->item = topush;
  newStack->next = stack;
  return newStack;
}

/*************
 *Function Name: popoff
 *Function Description: Takes three nodes off the top of the stack and creates a subtree with them,
 *then puts the new subtree back onto the top of the stack
 *Parameters In: StackNode, the current stackpointer
 *Parameters output: A new stackpointer that has been updated
*************/
StackNode* popoff(StackNode* stack){
  TreeNode* root;
  StackNode* leftChild;
  StackNode* rightChild;

  rightChild = stack;
  stack = stack->next;

  root = stack->item;
  stack = stack->next;

  leftChild = stack;
  stack = stack->next;

  root->leftChild = leftChild->item;
  root->rightChild = rightChild->item;

  stack = pushback(root,stack);

  return stack;
}

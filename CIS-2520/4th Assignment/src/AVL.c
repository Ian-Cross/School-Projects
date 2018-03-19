#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

typedef struct treeNode {
	struct treeNode *left;
	struct treeNode *right;
	char* key;
	int occurances;
} TreeNode;

typedef struct avl {
	struct treeNode *root;
} AVL;

void printHead();
AVL *createTree();
TreeNode *createNode();
int calcHeight(TreeNode *node);
int calcSize(TreeNode *node);
int balanceFactor(TreeNode *node);
TreeNode *rotateLeftLeft(TreeNode *node);
TreeNode *rotateLeftRight(TreeNode *node);
TreeNode *rotateRightLeft(TreeNode *node);
TreeNode *rotateRightRight(TreeNode *node);
TreeNode *balanceNode(TreeNode *node);
void balanceTree(AVL *tree);
void insertNode(AVL *tree, char* key);
void removeNode(AVL *tree, char* key);
TreeNode *findNode(AVL *tree, char* key);
void findAll(TreeNode *tree, int freq);
void printNode(TreeNode *node, int depth);
void printTree(AVL *tree);

int main() {
	AVL* tree = NULL; //creating the tree
	FILE* file;
	char* token;
	char input[500];
	char line[500]; //to hold the line read in
	char delim[] = " \n\0";
	int answer = -1;
	int freq = 0;

	tree = createTree(); //allocating and initalizing the tree

	printHead(); //Displays a header to stay at the top of the program

	do {
		//display menu options
		printf("1. Load a file\n");
		printf("2. Search for a node\n");
		printf("3. Insert a node\n");
		printf("4. Remove a node\n");
		printf("5. Check height and size\n");
		printf("6. Find all nodes above a frequency\n");
		printf("7. Quit the program\n");

		//prompt
		printf("avl/> ");
		scanf("%d",&answer);
		system("clear");
		printHead(); //header

		switch (answer) {
			case 1:
				printf("Filename: ");
				scanf("%s",input);
				printf("\n");

				//opening the file
				file = fopen(input,"r");
				if (file == NULL) {
					//quit when the file DNE or couldn't be opened
					printf("Sorry, file could not be opened\n");
					continue;
				}

				while(fgets(line, 500, file)) {
					//get the first token
					token = strtok(line, delim);
					//cycle through to the end to get the rest of the tokens
					while( token != NULL ) {
						insertNode(tree, token); //add the node into the tree
						balanceTree(tree); //balance the tree
						token = strtok(NULL, delim);
					}
				}
				fclose(file);
				break;
			case 2:
				//make sure there is a tree to search
				if (tree->root == NULL){
					printf("There is no tree\n\n");
				} else {
					printf("What node would you like to search for: ");
					scanf("%s",input);
					printf("\n");
					//search for the inputted node
					TreeNode* foundNode = findNode(tree,input);
					if (foundNode == NULL){
						printf("I'm sorry that node could not be found\n\n");
					} else {
						printf("Node: %s, occurs: %d\n\n",foundNode->key,foundNode->occurances);
					}
				}
				break;
			case 3:
				printf("Enter the key you want to insert: ");
				scanf("%s",input);
				printf("\n");
				insertNode(tree,input); //insert their desired node
				balanceTree(tree); //rebalance
				break;
			case 4:
				//make sure there is a tree
				if (tree->root == NULL){
					printf("There is no tree\n\n");
				} else {
					printf("What node would you like to remove: ");
					scanf("%s",input);
					printf("\n");
					removeNode(tree,input); //remove the desired node
					if (tree->root) balanceTree(tree); //if there is still a tree, rebalnce it
				}
				break;
			case 5:
				//make sure there is a tree
				if (tree->root == NULL){
					printf("There is no tree\n\n");
				} else {
					printf("The height is %d\n",calcHeight(tree->root));
					printf("The Size is %d\n",calcSize(tree->root));
				}
				break;
					case 6:
					//make sure there is a tree
					if (tree->root == NULL){
						printf("There is no tree\n\n");
					} else {
						printf("frequency: ");
						scanf("%d",&freq);
						printf("\n");
						findAll(tree->root,freq); //search all above the given frequency
					}
				break;
			default:
				break;
		}
	} while (answer != 7);

	system("clear"); //make things look pretty
	return 0;
}

/*************
 *Function Name: printHead
 *Function Description: Prints out a header at the to of the screen
 *Parameters In: N/A
 *Parameters output: N/A
 *Errors: N/A
 *************/
void printHead(){
	printf("------------------------------\n");
	printf("Welcome to the AVL tree maker!\n");
	printf(" Ian Cross  CIS*2520  0911085 \n");
	printf("------------------------------\n");
}

/*************
 *Function Name: createTree()
 *Function Description: allocates space for the tree, sets the first node to null
 *Parameters In: N/A
 *Parameters output: Returns the newly created tree
 *Errors: Fails if no space can be allocated
 *************/
AVL *createTree() {
	AVL *newTree = NULL;

	//give space for the tree
	newTree = malloc(sizeof(AVL));
	//if no space could be allocated
	if(newTree == NULL) {
		printf("Sorry, memory could not be allocated for the new Tree\n");
		exit(1);
	}
	//initalize values
	newTree->root = NULL;
	return newTree;
}

/*************
 *Function Name: createNode()
 *Function Description: allocates space for the new node and initalizes the values to empty
 *Parameters In: N/A
 *Parameters output: returns the newly created node
 *Errors: Fails if no space can be allocated
 *************/
TreeNode *createNode() {
	TreeNode *newNode = NULL;

	//alocates space for the node
	newNode = malloc(sizeof(TreeNode));
	//if no space can be allocated for the new node, quit
	if(newNode == NULL) {
		printf("Sorry, memory could not be allocated for the new node\n");
		exit(1);
	}

	newNode->key = malloc(sizeof(char)*15);

	//initalize the values
	newNode->left = NULL;
	newNode->right = NULL;
	strcpy(newNode->key,"");
	newNode->occurances = 1;

	return newNode;
}

/*************
 *Function Name: calcHeight()
 *Function Description: Find the height of a AVL node
 *Parameters In: the node to calcualte the height of
 *Parameters output: the final return is the height of the node
 *Errors: N/A
 *************/
int calcHeight(TreeNode *node) {
	int heightLeftSubtree = 0;
	int heightRightSubtree = 0;

	if (!node->left && !node->right) return 0;

	//recursively searching the tree
	if(node->left) heightLeftSubtree = calcHeight(node->left);
	if(node->right) heightRightSubtree = calcHeight(node->right);

	if (heightRightSubtree > heightLeftSubtree){
		return ++heightRightSubtree;
	} else {
		return ++heightLeftSubtree;
	}
}

/*************
 *Function Name: calcSize()
 *Function Description: Find the amount of nodes in the tree
 *Parameters In: The tree to find the size of
 *Parameters output: Returns the size as an integer
 *Errors: N/A
 *************/
int calcSize(TreeNode* node){
	if (node == NULL) return 0; //terminating case
	int sizeLeftSubtree = calcSize(node->left); //go down the left subtree
	int sizeRightSubtree = calcSize(node->right); //go down the right subtree
	return (sizeLeftSubtree + sizeRightSubtree + 1); //add the subtrees together with the current node and move up
}

/*************
 *Function Name: calcBalanceFactor()
 *Function Description: Find the balance of an AVL node
 *Parameters In: Node to be calculated on
 *Parameters output: returns the balance factor of the given node
 *Errors: N/A
 *************/
int balanceFactor(TreeNode *node) {
	int bf = 0;

	//finds the height of the left subtree
	if(node->left) bf += calcHeight(node->left);
	else bf--;

	//finds the height of the right subtree
	if(node->right) bf -= calcHeight(node->right);
	else bf++;

	return bf;
}

/*************
 *Function Name: rotateLeftLeft()
 *Function Description: Balances the tree by appling the Left Left algorithm
 *Parameters In: A node containing a subtree to be rotated
 *Parameters output: N/A
 *Errors: N/A
 *************/
TreeNode *rotateLeftLeft(TreeNode *node) {
 	TreeNode *switchedNode = node;
	TreeNode *leftNode = switchedNode->left;

	switchedNode->left = leftNode->right;
	leftNode->right = switchedNode;

	return leftNode;
}

/*************
 *Function Name: rotateLeftRight()
 *Function Description: Balances the tree by appling the Left Right algorithm
 *Parameters In: A node containing a subtree to be rotated
 *Parameters output: N/A
 *Errors: N/A
 *************/
TreeNode *rotateLeftRight(TreeNode *node) {
	TreeNode *switchedNode = node;
	TreeNode *leftNode = switchedNode->left;
	TreeNode *rightNode = leftNode->right;

	switchedNode->left = rightNode->right;
	leftNode->right = rightNode->left;
	rightNode->left = leftNode;
	rightNode->right = switchedNode;

	return(rightNode);
}

/*************
 *Function Name: rotateRightLeft()
 *Function Description: Balances the tree by appling the Right Left algorithm
 *Parameters In: A node containing a subtree to be rotated
 *Parameters output: N/A
 *Errors: N/A
 *************/
TreeNode *rotateRightLeft(TreeNode *node) {
	TreeNode *switchedNode = node;
	TreeNode *rightNode = switchedNode->right;
	TreeNode *leftNode = rightNode->left;

	switchedNode->right = leftNode->left;
	rightNode->left = leftNode->right;
	leftNode->right = rightNode;
	leftNode->left = switchedNode;

	return(leftNode);
}

/*************
 *Function Name: rotateRightRight()
 *Function Description: Balances the tree by appling the Right Right algorithm
 *Parameters In: A node containing a subtree to be rotated
 *Parameters output: N/A
 *Errors: N/A
 *************/
TreeNode *rotateRightRight(TreeNode *node) {
	TreeNode *switchedNode = node;
	TreeNode *rightNode = switchedNode->right;

	switchedNode->right = rightNode->left;
	rightNode->left = switchedNode;

	return(rightNode);
}

/*************
 *Function Name: balanceNode()
 *Function Description: will traverse the tree and find the balance factor of each node
 	then choose how to rotate and call the rotations on the nodes besed off their balance factor.
 *Parameters In: The node to be balanced
 *Parameters output: A balanced node
 *Errors: N/A
 *************/
TreeNode *balanceNode(TreeNode *node) {
	TreeNode *newNode = NULL;

	//traversing the tree
	if(node->left)
		node->left  = balanceNode(node->left);
	if(node->right)
		node->right = balanceNode(node->right);

	//calculates the balanceFactor of the node
	int bf = balanceFactor(node);

	//if the node is left heavy
	if(bf >= 2) {
		//if the left node is right heavy
		if( balanceFactor(node->left) <= -1 )
			newNode = rotateLeftRight(node);
		//if the left node is left heavy
		else
			newNode = rotateLeftLeft(node);
	//if the node is right Heavy
	} else if(bf <= -2) {
		if( balanceFactor(node->right) >= 1 )
			//if the right node is left heavy
			newNode = rotateRightLeft(node);
		else
			//if the right node is right heavy
			newNode = rotateRightRight(node);
	//if everything is balanced
	} else {
		newNode = node;
	}
	return(newNode);
}

/*************
 *Function Name: balanceTree()
 *Function Description: Balances a given tree
 *Parameters In: A tree containing all the data
 *Parameters output: N/A
 *Errors: N/A
 *************/
void balanceTree(AVL *tree) {
	TreeNode *newTreeRoot = NULL;

	//balance the root node of the tree
	newTreeRoot = balanceNode( tree->root );

	//replacing the tree with the balanced one
	if( newTreeRoot != tree->root )  {
		tree->root = newTreeRoot;
	}
}

/*************
 *Function Name:insertNode()
 *Function Description: takes a inputted key and inserts it into the tree
 *Parameters In: the tree to be inserted into, the key to insert into the tree
 *Parameters output: N/A
 *Errors: N/A
 *************/
void insertNode(AVL *tree, char* key) {
	TreeNode *node = NULL;
	TreeNode *next = NULL;
	TreeNode *last = NULL;

	//basecase, if the tree doesn't exist
	if( tree->root == NULL ) {
		node = createNode(); //create a new node
		strcpy(node->key,key);
		tree->root = node;
	//the tree exists
	} else {
		next = tree->root;
		//progress through the tree searching for the place to put the new node
		while(next != NULL) {
			last = next;
			if(strcmp(key,next->key) < 0) {
				next = next->left;
			} else if(strcmp(key,next->key) > 0) {
				next = next->right;
				//if the node exists increase the occurances
			} else if(strcmp(key,next->key) == 0) {
				next->occurances++;
				break;
			}
		}

		//create the new node
		node = createNode();
		strcpy(node->key,key);

		//puts the node in the right place
		if(strcmp(key,last->key) < 0) last->left = node;
		if(strcmp(key,last->key) > 0) last->right = node;
	}
}

/*************
 *Function Name: removeNode()
 *Function Description: removes a given node from the tree
 *Parameters In: A tree to be manipulated, a key to remove from the tree
 *Parameters output: N/A
 *Errors: N/A
 *************/
void removeNode(AVL* tree, char* key){
	TreeNode *next = NULL;
	TreeNode *last = NULL;
	TreeNode *tempNode = NULL;

	next = tree->root;
	//while there is a tree
	while(next != NULL) {
		//progress the tree left
		if(strcmp(key,next->key) < 0) {
			last = next;
			next = next->left;
		//progress the tree right
		} else if(strcmp(key,next->key) > 0) {
			last = next;
			next = next->right;
		//when it finds a matching key
		} else if(strcmp(key,next->key) == 0) {
			//takes an occurance away if there is more than one
			if (next->occurances > 1) {
				next->occurances--;
			//if there is no children, just delete the node
			} else if (!next->left && !next->right){
				if (last == NULL){
					tree->root = NULL;
				} else {
					if (last->left){
						last->right = NULL;
					} else {
						last->left = NULL;
					}
				}
			//if there is a left child, not a right. Remove the node and pull up the children
			} else if (next->left && !next->right){
				if (last == NULL){
					tree->root = next->left;
				} else {
					if (last->left){
						last->right = next->left;
					} else {
						last->left = next->left;
					}
				}
			//if there is a right child, not a left. Remove the node and pull up the children
			} else if (!next->left && next->right){
				if (last == NULL){
					tree->root = next->right;
				} else {
					if (last->left){
						last->right = next->right;
					} else {
						last->left = next->right;
					}
				}
			//if there is both children
			} else {
				//find the replacment node
				tempNode = next->right;
				while (tempNode->left != NULL){
					tempNode = tempNode->left;
				}

				//transfer over the data, and remove the old node
				next->occurances = tempNode->occurances;
				char* temphold = tempNode->key;
				removeNode(tree,tempNode->key);
				strcpy(next->key,temphold);
			}
			break;
		}
	}
}

/*************
 *Function Name: findNode()
 *Function Description: searches the tree for a given key
 *Parameters In: A tree full of data, a key to be found
 *Parameters output: returns the node that is found
 *Errors: N/A
 *************/
TreeNode *findNode(AVL *tree, char* key) {
	TreeNode *current = tree->root;
	int flag = 0;

	//progressing through the tree
	while(current != NULL && flag == 0) {
		//checking for a non matching key
		if (strcmp(current->key,key) != 0){
			//move a left or right based off of key
			if(strcmp(current->key,key) < 0)
				current = current->right;
			else
				current = current->left;
		//matching key
		} else {
			current->occurances++;
			flag = 1;
		}
	}

	return current;
}

/*************
 *Function Name: findAll()
 *Function Description: searches through the tree for all nodes above the given frequency
 *Parameters In: A tree to search through, a frequency to find nodes over
 *Parameters output: N/A
 *Errors: N/A
 *************/
void findAll(TreeNode *tree, int freq){
	//progress left though the tree
	if (tree->left) findAll(tree->left,freq);
	if(tree->occurances > freq) printf(" %s: %d\n",tree->key,tree->occurances);
	//progress right through the tree
	if (tree->right) findAll(tree->right,freq);
}

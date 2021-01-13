#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h>     
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "charBST.h"
//Max quant is the largest quantity that any node has. Is used for formatting
int maxquant = 1;
//Makes a bst node with the give inputs of name, right, and left. Sets default quantity to 1
struct BSTNode* BSTNode(char* name, struct BSTNode* right, struct BSTNode* left) {
	struct BSTNode* node = (struct BSTNode*) malloc(sizeof(struct BSTNode));
	node-> name = name;
	node->right = right;
	node->left = left;
	node->quantity = 1;
}
//Recursively adds input name to BST. head is used to traverse the BST
struct BSTNode* addChar(struct BSTNode* head, char* buff) {
	if(head == NULL) {

		return BSTNode(buff, NULL, NULL);
	
	}
	int strcmpResult = strcmp(getName(head), buff);
	//If node head has same value as the value we are looking for, buff, increment the node
	if(strcmpResult == 0) {
		incrementWord(head);
		if(head->quantity > maxquant) {
			maxquant = head-> quantity;

		}

		return head;
	}
		//Add left
	if(strcmpResult > 0) {

		head->left = addChar(head->left, buff);
	} 
	//Add right
	if(strcmpResult < 0) {
		head->right = addChar(head->right, buff);
	}
 
	return head;

}
//Increase the quantity of input node head by 1
void incrementWord(struct BSTNode* head) {
	head->quantity = head->quantity + 1;
}
//Sets nodes left node to left
void addLeft(struct BSTNode* node, struct BSTNode* left) {
	node->left = left;
}
//Sets nodes right node to right
void addRight(struct BSTNode* node, struct BSTNode* right) {
	node->right = right;
}
//Returns heads right node
struct BSTNode* getRight(struct BSTNode* head) {
	return head->right;
}
//Returns heads left node							
struct BSTNode* getLeft(struct BSTNode* head) {
	return head->left;                             												
}
//Returns name of given node
char* getName(struct BSTNode* node) {
	return node->name;
}	
//Recursivly calls the print node helper		
void printNode(struct BSTNode* node, int length, int file) {
	printNodeHelp(node, length, file);

}

//Prints the node and its value to output.txt
void printNodeHelp(struct BSTNode* node, int length, int file) {                                                                                                                                             
	//Base case
	if(node == NULL) {
		return;
	}              
	//Calls left Node first because left node is alphabetically before
	printNodeHelp(getLeft(node), length, file);
	char buffer[length+50];
	int space = length - strlen(getName(node));
	int spaceNum = 0;
	int max = maxquant;
	//Finds spacing for numbers
	while(max != 0) {
		max = max / 10;
		spaceNum++;
	}	
	//Makes buffer proper formatting for writing to file
	sprintf(buffer,"%s%*s : %*d", getName(node),space,"",spaceNum, node->quantity);

	//Writes to file and makes a new line
	write(file, buffer, strlen(buffer));
	errno = 0;
	if(errno != 0) {
	//Error handling for if file does not open
        	char buf[1000];
        	sprintf(buf,"Could not write to file output.txt with errno: %i\n", errno);
        	write(STDERR_FILENO, buf, strlen(buf));												
		return;
	}
	
	write(file, "\n", 1);
	errno = 0;
	if(errno != 0) {
	//Error handling for if file does not open
		char buf[1000];
		sprintf(buf,"Could not open file output.txt with errno: %i\n", errno);
		write(STDERR_FILENO, buf, strlen(buf));												
	}


	printNodeHelp(getRight(node), length, file);                                                                                                                                                                                    
                                                                                            
}	
//Frees memory of the tree
void freeNodes(struct BSTNode* node) {
	if(node == NULL) {
		return;
	}
	freeNodes(node->right);
	freeNodes(node->left);
	free(node->name);
	free(node);
}			

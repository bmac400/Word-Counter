#include <stdio.h>
#include <stdlib.h>

struct BSTNode {
	char* name;
	int quantity;
	struct BSTNode* right;
	struct BSTNode* left;

};

struct BSTNode* BSTNode(char* name, struct BSTNode* right, struct BSTNode* left);

struct BSTNode*  addChar(struct BSTNode* head, char* name);

void incrementWord(struct BSTNode* head);

void addLeft(struct BSTNode* node, struct BSTNode* left);

void addRight(struct BSTNode* node, struct BSTNode* right);

struct BSTNode* getRight(struct BSTNode* head);
struct BSTNode* getLeft(struct BSTNode* head);
char* getName(struct BSTNode* node);
											
void printNode(struct BSTNode* head, int length, int file);

void printNodeHelp(struct BSTNode* node, int length, int file);

void freeNodes(struct BSTNode* node);

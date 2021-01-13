#include "charBST.h"
#include <stdio.h>
#include <stdlib.h>
extern struct hashItem* hashtable[26];
struct hashItem {
	int key;
	struct BSTNode* node;	
};

int getKeyFromLetter(char firstLetter);

struct BSTNode* findNode(int key);

struct BSTNode* findNodeFromLetter(char letter);

struct hashItem** getArray();

void addWord(char* word);

void printTable(int length);
void freeTable();			

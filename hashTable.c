#include "hashTable.h"
#include <fcntl.h>   
#include <unistd.h>  
#include <stdio.h>   
#include <ctype.h>
#include <string.h>
#include <errno.h>
//#include "charBST.h"



struct hashItem* hashtable[26];
//Makes hash item with inputs of key and node.
struct hashItem* hashItem(int key, struct BSTNode* node) {
	struct hashItem* item = (struct hashItem*) malloc(sizeof(struct hashItem));
	item->node = node;
	item->key = key;
}
//Returns the key of the input firstLetter
int getKeyFromLetter(char firstLetter){
	int asciival = firstLetter;
	return asciival - 97;
}
//Returns the BST of the input key
struct BSTNode* findNode(int key) {
	return hashtable[key]->node;
}
//Returns the BST of the input letter
struct BSTNode* findNodeFromLetter(char letter) {
	return findNode(getKeyFromLetter(letter));
}
//Returns the hash table
struct hashItem** getArray() {
	return hashtable;
}
//Adds input word to the respective binary search tree
void addWord(char* word) {
	char* input = strdup(word);
	//If no node or hash table item has been made yet, make new has node
	if(hashtable[getKeyFromLetter(word[0])] == NULL) {
				
		hashtable[getKeyFromLetter(word[0])] = hashItem(getKeyFromLetter(word[0]), BSTNode(input,NULL,NULL));

	} else {

		hashtable[getKeyFromLetter(word[0])]->node = addChar(findNodeFromLetter(word[0]), input);

	}
}
//Prints table to output.txt, by calling printNode on every hash item. Open and close output.txt
void printTable(int length) {
	errno = 0;
	int file = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(errno != 0) {
	//Error handling for if file does not open
		char buf[1000];
		sprintf(buf,"Could not open file output.txt with test errno: %i\n", errno);
		write(STDERR_FILENO, buf, strlen(buf));												
		return;
	}
	for(int x = 0; x < 26; x++) {
		if(hashtable[x] != NULL) {
			printNode(hashtable[x]->node, length, file);
		}
	}
	close(file);
}
//Free hashtables memory
void freeTable() {
	for(int x = 0; x<26; x++) {
		if(hashtable[x] == NULL) {
			continue;
		}
		freeNodes(hashtable[x]->node);
		free(hashtable[x]);
	}
}			

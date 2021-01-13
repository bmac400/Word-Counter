#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "hashTable.h"
void parseFile(char* fileName);
int largestWord = 0;

int main(int argc, char* argv[], char* envp[]) {

	//Adds file at enviromental variable word freak to hash table
	char* env = getenv("WORD_FREAK");
	if(env != NULL) {

		parseFile(env);
	}
	//Adds all command line arguements to hash table
	int i = 1;
	while(argv[i] != NULL) {
		parseFile(argv[i]);
		i++;
	}
	//Handles std input
	parseFile("0");
	

	printTable(largestWord);
	freeTable();

}
//Parse file
//Takes a file and adds all words to the hash table
void parseFile(char* fileName) {
	int file;
	errno = 0;
	if(strcmp(fileName, "0") != 0) {
		file = open(fileName,O_RDONLY);
	} else {
		file = 0;
		errno = 0;
	}
	if(errno != 0) {
	//Error handling for if file does not open
		char what[1000];
			sprintf(what,"\nCould not open file %s with errno: %i\n", fileName, errno);
		write(STDERR_FILENO, what, strlen(what));												
		return;
	}
	char buffer[255];
	int bytesSize = 1;
	int bytesRead;
	char word[255];
	int wordPos = 0;
	//While there is still info not read in file to be handled
	while(bytesSize != 0) {
		bytesSize = read(file, buffer, 255);
		bytesRead = 0;
		//While there is still text that we read in the chunk we are in
		while(bytesRead < bytesSize) {
			buffer[bytesRead] = tolower(buffer[bytesRead]);
			//Ensure it is in the alphabet, then add character
			if(isalpha(buffer[bytesRead]) != 0) {
				word[wordPos] = buffer[bytesRead];
				wordPos++;
				bytesRead++;
			} else {
				//If its not in the alphabet, then add the current buffer as a word
				if(wordPos > largestWord) {
					largestWord = wordPos;
				}
				word[wordPos] = '\0';
				//If empty don't add word/ causes error
 				if(strcmp("",word)==0) {
					
				} else {	
					addWord(word);
					wordPos = 0;
					
				}
				bytesRead++;
			}
		}
	
	}
	//If word is not empty yet and has not been added yet(wordPos != 0) 
	if(wordPos != 0 && strcmp(word,"") != 0) {
		addWord(word);
	}
	//If file is stdin, do not close(ie exit function)
	if(strcmp("0", fileName) == 0){
		return;
	}
//	free(buffer);
	close(file);
}																						

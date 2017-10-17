/* University of Central Florida
CIS3360 - Fall 2017
Program Author: Vincent Phan, Tyler McFadden */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void vigify(char *text, char *text2, char *key, char *iv) {	// function to apply the Vigenere cipher in CBC mode
	int temp, x, i, len = strlen(key), blocks = strlen(text)/len;
	for (x = 0; x < blocks; x++) {
        if (x == 0) {
           for (i = 0; i < len; i++) {
               temp = (text[i] + iv[i] + key[i] - 291) % 26;
               text2[i] = temp + 97;
           }
        } else{
           for (i = 0; i < len; i++) {
               temp = (text[i + len*x] + text2[i + len*(x-1)] + key[i] - 291) % 26;
               text2[i + len * x] = temp + 97;
           }    
        }
    }
    
    printf("\n\nCipher Text:\n\n");
    for (i = 1; i <= strlen(text); i++) {
		printf("%c", text2[i-1]);
		if (i%80 == 0) {
			printf("\n");
			
		}
	}
	
	printf("\n");
}

int main(int argc, char *argv[] ){

	char **arguments;
	int index;
	char temp[5000];
	char unciphered[5000];
	char plainText[5000];
	char cipherText[5000];
	int i = 0;
	int plainLen = 0;
	int leftover = 0;
	int counter = 0;
	
	arguments = malloc(sizeof(char*)*(argc+1));// plus one extra which will mark the end of the array
	for (index = 0; index < argc; ++index){
		arguments[index] = malloc(strlen(*argv)+1 ); // add one for the \0
		strcpy(arguments[index], *argv);
		++argv;
	}
	arguments[index] = NULL;// end of array so later you can do while (array[i++]!=NULL)
	
	int keyword = (int)strlen(arguments[2]);
	
	
	FILE* input = fopen(arguments[1],"r");/*Opens file in read mode*/
	
	if (input) {//Scans and inputs file into an array
		while (fscanf(input, "%s", temp)!=EOF){
			strcat(unciphered, temp);
		}
   		fclose(input);
	}
	
	size_t len = strlen(unciphered);//Turns array into plainText and lowercased array only
	for(i = 0; i < len; i++){
		if(isalpha(unciphered[i])){
			plainText[plainLen] = unciphered[i];
			if(isupper(plainText[plainLen])){
			plainText[plainLen]= plainText[plainLen] +32;
			}
			plainLen++;
		}
	}
	
	
	//Output Displays plainText array
	printf("CBC Vigenere by Vincent Phan and Tyler McFadden\nPlaintext file name: %s\nVigenere keyword: %s\nInitializion vector: %s\n\nClean Plaintext:\n\n", arguments[1], arguments[2], arguments[3]);
	for(i = 1; i <= plainLen; i++){
			printf("%c", plainText[i-1]);
			if (i%80 == 0) {
				printf("\n");
			}
		}
		
	if((plainLen % keyword) != 0){//determines padding
		leftover = keyword - (plainLen % keyword);
		int	temporary = plainLen + leftover;//diagnostic
		for(counter = plainLen; counter < temporary; counter++){
			plainText[counter] = 'x';
		}
	}

	vigify(plainText, cipherText, arguments[2], arguments[3]);
	
	printf("\nNumber of characters in clean plaintext file: %d\n", plainLen);
	printf("Block size = %d\n", keyword);
	printf("Number of pad characters added: %d\n", leftover);
	return 0;
}

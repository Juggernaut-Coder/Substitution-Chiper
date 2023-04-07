/* Incude the standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARRAY_SIZE 256 /* Define maximum array size */
#define ENCRYPT(numeric_char,mask) (numeric_char^mask)      

enum op{
    encrypt = 1,
    decrypt = 2
};

int main (void) {

    int operation;
    unsigned int mask = 0xa5;
    char buffer[MAX_ARRAY_SIZE];
    unsigned int numeric_seq[MAX_ARRAY_SIZE];  
    char *start = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%&():;?.,/";
    char *sub = ":;?.,/0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%&()";
    printf("What operation would you like to perform (1 - Encrypt, 2 - Decrypt)?\n");
    scanf("%d%*c", &operation);
    if(operation == encrypt) {
        // Encrypt
        printf("So you want to encrypt the message\n");
        printf("Please enter you message:\n");
        fgets(buffer, MAX_ARRAY_SIZE , stdin); 
        for(int i = 0; i < strlen(buffer)-1; i++) {
            if(buffer[i] != ' ') { // ignore space characters
                char *e = strchr(start, toupper(buffer[i])); // find the first occurenence of buffer[i] char in string start
                int index = (int)(e-start); // find the index of the first occurence of buffer[i] in start
                buffer[i] = sub[index];   // copy sub[index] to buffer[i]
            }
            numeric_seq[i] = ENCRYPT((int)buffer[i],mask); // encrypt using bitwise XOR
            printf("%u ",numeric_seq[i]); 
        }
        printf("\n");
    } else if   (operation == decrypt) {
       // Decrypt
        printf("So you want to decrypt the message\n");
        printf("Please enter you message:\n");
        fgets(buffer, MAX_ARRAY_SIZE , stdin);
        char *token;
        char *delim = " ";
        int numeric_seq_index = 0;
        token = strtok(buffer, delim); // parse the string omitting the delimiter
        while(token != NULL) {
            numeric_seq[numeric_seq_index++] = atoi(token); // convert string to integer and copy it to numeric_seq array
            token = strtok(NULL,delim); 
        }
        int numeric_seq_size = numeric_seq_index; // get numeric_seq array size
        for(int i = 0; i < numeric_seq_size; i++) { 
            buffer[i] = (char) ENCRYPT(numeric_seq[i],mask); // decrypt using bitwise XOR
            if(buffer[i] != ' ') { 
                char *e = strchr(sub, toupper(buffer[i])); // find the first occurenence of buffer[i] char in string sub
                int index = (int)(e-sub); // find the index of the first occurence of buffer[i] in sub
                buffer[i] = start[index]; // copy start[index] to buffer[i]
            }
        }
        printf("The decrypted message is:\n%s\n",buffer);

    } else {
        printf("You do not know what you want!\n");
    }
    exit(EXIT_SUCCESS);
}

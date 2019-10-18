/*
 * Filename: main.c
 * Author: Justin Lee
 * Date: 17 October 2019
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "projStrings.h"
#include "hashTable.c"

/*
 * Function Name: main()
 * Function Prototype: int main(int argc, char *argv[]);
 * Description: The main driver of this program.   The main function
 *              will read in the inputted HTTP header file and return
 *              the number of times that each header occurs in the file
 * Parameters:  argc - the number of arguments
 *              argv - the array containing arguments.  namely
 *                     argv[0] will be the program name
 *                     argv[1] will be the path to the input HTTP header file
 * Side Effects:  -Prints the result to stdout on successfull read and search
 *                -Prints to stderr if there was an error reading the file or 
 *                   with the specified file path
 * Return Value: EXIT_FAILURE on error
 *               EXIT_SUCCESS otherwise
 *
 */

int main(int argc, char *argv[]){
    //if the number of arguments is incorrect
    if(argc != 2) {  //we print the usage error message and return
        fprintf(stderr, USAGE_MESSAGE);
        return EXIT_FAILURE;
    }
        /*  This section equivalent to having a function that takes an input string of 
	 *  the file path and returning a pointer to the opened file */ 
    //We will now attempt to build a stat for the specified file
    //This is so that we can determine if the file exists, and also that the file is not a directory
    errno = 0;
    struct stat buf;
    stat(filename, &buf);
    if(errno != 0){ //return error if building stat fails, i.e file does not exist
        fprintf(stderr, FILE_DNE);
	return EXIT_FAILURE;
    }
    if(S_ISDIR(buf.st_mode) == 1){ //return error if file is a directory
        fprintf(stderr, FILE_DIR);
	return EXIT_FAILURE;
    }

    errno = 0;
    //We will now attempt to open the file
    FILE *fp = fopen(filename, "r");
    if(errno != 0){ //returns error if the file cannot be opened
        fprintf(stderr, FILE_NOPEN);
	return EXIT_FAILURE;
    }
        /* End returning a FILE pointer *fp */


    //Now that the file is open and fp points to it, we can parse the file
    //in order to achieve this, we will go line by line through the file 
    //and we will attempt to extract the header from each line, and 
    //insert / search for it in a hash table.
    
    //The purpose of the hash table is so that we can keep track of the number
    //of occurences and search/insert each word in O(1) time
    


    //My implementation of a HashTable is technically a hash Map
    // key = header  value = number of occurences
    struct HashTable ht;  
    
    //scan the file line by line, if the file is openable, the program assumes
    //it's a valid file of headers.   As we scan each line, we are determining
    //if each line indeed contains a header, and if it does, it determines if 
    //we need to increment an existing counter for this header or create
    //a new slot in the hashtable
    char *line = NULL;
    struct Node *temp;
    size_t len = 0;
    char *colPtr; //searches for the first occurence of ':' to check for header
                  //assuming the file is formatted correctly, this should work
		  //only edge case when the first line of the header block has
		  //a colon in it...
    while(getline(&line, &len, fp) != -1){  //scanning line by line of the file
        colPtr = strchr(line, ':');  //search for the first occurence of ':'
	 //the idea being that we can extract the word because it is before ':'
        if(colPtr != NULL){
	    char key[sizeof(line)];
	    memset(key, '\0', sizeof(key));
            strncpy(key, line, (int)(colPtr - line));
	    temp = search(key, &ht);
	    if(temp == NULL){
                insert(key, &ht);
            }
        }
    }

    //at this point, the hashMap is filled, so we need to iterate through the 
    //elements.  we will also free memory here.
    struct Node *next;
    for(int i=0; i<LENGTH; i++){
        temp = ht.hashArray[i];
	while(temp != NULL){
            printf(STR_RESULT, temp->key, temp->occurences);
	    next = temp->next;
	    delete temp;
	    temp = next;
        }

    }

    return EXIT_SUCCESS;
}

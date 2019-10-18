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
 *              the number of times that the specified headers occur
 *              in the file
 * Parameters:  argc - the number of arguments
 *              argv - the array containing arguments.  namely
 *                     argv[0] will be the program name
 *                     argv[1] will be the path to the input HTTP header file
 *                     additional arguments will be the search strings
 * Side Effects:  -Prints the result to stdout on successfull read and search
 *                -Prints to stderr if there was an error reading the file or 
 *                   with the inputs
 * Return Value: EXIT_FAILURE on error
 *               EXIT_SUCCESS otherwise
 *
 */

int main(int argc, char *argv[]){
    //if there are not enough arguments, i.e file name or search strings not specified
    if(argc < 3) {  //we print the usage error message and return
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
    //in order to achieve this, we will go line by line through the file, and then 
    //compare the line to the search string.   We will add all the search strings to a hashmap
    //for O(1) search



    return EXIT_SUCCESS;
}

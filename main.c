/*
 * Filename: main.c
 * Author: Justin Lee
 * Date: 17 October 2019
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
 *                     additional arguments will be which headers to search for
 * Side Effects:  -Prints the result to stdout on successfull read and search
 *                -Prints to stderr if there was an error reading the file
 * Return Value: EXIT_FAILURE on error
 *               EXIT_SUCCESS otherwise
 *
 */



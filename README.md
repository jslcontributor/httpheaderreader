HTTP header reader C Project by Justin Lee:

Description:  Reads in a file containing well formed HTTP headers and their
              values.   Determines the number of time each header occurs


How to Compile:  A Makefile has been provided.  You can compile by typing make

How to Run:  In the command line type './main (filepath)'

How this Program works:
 - Checks if the specified filepath exists, is not a directory, and is openable
 - Opens the file and parses the file line by line
 - At each line, checks for a colon ':' and extracts the word before the colon
 - Checks if this word exists in the HashMap, if so then increment it's value,
   if not, then insert node into HashTable with key = word and 
   value = number of occurences = 1 if it's just being inserted
 - After reading each line, iterates through the HashMap and prints each 
   header word and the number of occurences
 - Frees Memory

How this Program was tested:
 - Black box testing
 - GDB



Features that could use improvement for ultimate robustness and limitations:
1. Running more tests is never the worst idea

2. Because the code strchr for the : and extracts the word before the : if
   strchr was successful, if a non-header line like the first line on the
   given file "<file start>" contains a colon, then  irrelevant data will be
   added to the hashMap.  i.e assumes that : is always the delimiter and only
   occurs after the header

3. Assumes that each line only has 200 chars worth of relevant information
   and that each header is less than 100 chars

4. HashMap is static in size, does not handle rehashing and increasing the size

5. Very slight, but consistent and non-scaling memory leak 

6. Assumes that if the file is able to be opened, is formatted correctly

7. Could sort the result

Justifications for above:
1.  I will test more, but I am seeking more clarification.  At the moment, it
    does work if the assumptions are 100% correct

2.  Seems like this is the accurate format, although again not sure if it's
    entirely impossible for a non-header line to contain a :

3.  This is a dangerous assumption, true, but I couldn't find any headers
    that are longer than 100 characters, but if it is then the result will
    still be printed, just will be chopped off 

4.  HashMap is size 30.  Because you scan each line and search in the hashmap,
    this will still save at least an order of magnitude of time even on really
    big inputs

5.  Memory leak is consistent at all scales.  I read that for windows, small
    memory leaks are acceptable.

6.  For production code, probably should make sure the file parsing is extra
    robust, but for this purpose we know what type of file we are using

7.  Decreases performance









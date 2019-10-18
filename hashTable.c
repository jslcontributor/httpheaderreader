/* Filename: hashTable.c
 * Author: Justin Lee
 * Date: 17 October 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 30 //hashmap is fixed length


/* Purpose of File:
 *
 * This is an implementation of a HashMap.  We are using a HashMap in order 
 * to store and check the occurences of each header we encounter.  Using
 * a HashMap allows us to have constance time search and insert.
 *
 * Key = char *key = header
 * Value = int occurences = number of occurences
 *
 * This implementation of a HashMap handles collisions by storing data
 * in an array of linkedlist
 */



//Node Object for the hashMap, stores key and value(occurences) as well as 
//a pointer to the next Node to give Nodes a linkedlist capability
struct Node{
    char *key;
    int occurences;
    struct Node *next;
};

//Defines a Hashtable "object"
struct HashTable{
    struct Node *hashArray[LENGTH];
};

//hashing function to get index from key.  very simple calculation
int hashIndex(char *key) {
    int totalValue = 0;
    while(*key != '\0'){
        totalValue += (int)( *key);
	++key;
    }
    return totalValue % LENGTH;

}

//initializes the elements of the array container in the HashTable to NULL
void HashTableMemSet(struct HashTable *ht){
    for(int i=0; i<LENGTH; i++){
        ht->hashArray[i] = NULL;
    }
}

//our search function increments the value(occurences) upoon a succesful
//search of the key in order to document each occurence
struct Node *search(char *key, struct HashTable *ht){
    int index = hashIndex(key);
    struct Node *ptr = ht->hashArray[index];
    while(ptr != NULL){
        if( strcmp(ptr->key, key) == 0){ //i.e the strings are equal
	    ++(ptr->occurences); //we increment occurences (i.e value)
    //to keep track of how many times we searched for the word
	    return ptr;
        }
	ptr = ptr->next;
    }
    return NULL;
}

void insert(char *key, struct HashTable *ht){ //assumes no duplicates
    struct Node *neww = (struct Node*) malloc(sizeof(struct Node));
    neww->key = (char*) malloc(sizeof(key));
    strcpy(neww->key, key);
    neww->occurences = 1; //we are inserting when we first occur a new word
    neww->next = NULL;
    int index = hashIndex(key);  //index we need to insert at

    if(ht->hashArray[index] == NULL){ //i.e no linked list head here
        ht->hashArray[index] = neww;   //then make one
    }
    else{ //else then there is a linked list head so traverse to the end 
	  // and add  the new node there
        struct Node *ptr = ht->hashArray[index];
	while(ptr-> next != NULL){
	    ptr = ptr->next;
	}
	ptr->next = neww;
    }

}

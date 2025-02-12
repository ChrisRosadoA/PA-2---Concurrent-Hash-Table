#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashdb.h"

#define MAX_LINE_LENGTH 1000
void display(hashRecord* t);

int main() {
    FILE* file;
    char line[MAX_LINE_LENGTH];
    char* token;
    char* nextToken;
    const char delimiters[] = ",";
    
    //Used for executing the appropiate functions 
    char* commandStr;
    char* commandUserName;
    char* commandValue;
    int value;

     //creating and initializing the table
     tableSize = computeTableSize(15, 0.7);
     concurrentHashTable = createTable();

     if (concurrentHashTable == NULL)
         exit(1);

    //char command[MAX_LINE_LENGTH]; // Variable to store the command

    // Open the file using fopen_s
    errno_t err = fopen_s(&file, "commands.txt", "r");
    if (err != 0) {
        fprintf(stderr, "Error opening the file.\n");
        return 1;
    }
    
    // Read line by line
    while (fgets(line, sizeof(line), file)) {
        
        // Get the first token
        token = strtok_s(line, delimiters, &nextToken);

        //THREADS
        if (strcmp(token, "threads") == 0) {
            commandStr = "threads";
            //printf("Command stored: %s\n", commandStr);


            //Traverses to the next token
            token = strtok_s(NULL, delimiters, &nextToken);

            //Convert Value from String to int
            value = atoi(token);

            //******Place "Threads" Function Here or use the value as needed******
        }

        //INSERT
        else if (strcmp(token, "insert") == 0) {
                commandStr = "insert";
                //printf("Command stored: %s\n", commandStr);
                
            
            //Traverses to the next token & Store Name found after insert command
            token = strtok_s(NULL, delimiters, &nextToken);
            commandUserName = token;

            /*printf("Username is: ");
            printf(commandUserName);
            printf("\n");*/

            token = strtok_s(NULL, delimiters, &nextToken);

            //Convert Value from String to int
            value = atoi(token);

            /*printf("Value is: %d", value);
            printf("\n");*/

            //******Place "insert" Function Call Here******
            insert(commandUserName,value);
          
        }

        //DELETE
        else if (strcmp(token, "delete") == 0) {
            commandStr = "delete";
            //printf("Command stored: %s\n", commandStr);

            token = strtok_s(NULL, delimiters, &nextToken);
            commandUserName = token;

            /*printf("Username to be deleted is: ");
            printf(commandUserName);
            printf("\n");*/

            //*****Place "delete" Function Here******
            deleteItem(commandUserName);
        }
  
        //PRINT
        else if (strcmp(token, "print") == 0) {
        
            //***Place "print" Function Here***
     file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file.\n");
        return 1;
    }

    //Print to output.txt Unsorted
    printf("Hash Table Contents:\n");
    for (int i = 0; i < tableSize; i++) {
        hashRecord* entry = concurrentHashTable[i];
        while (entry != NULL) {
            display(entry);
            entry = entry->next;
        }
    }
    // Close the file
    fclose(file);
     
        }
            
        //SEARCH
        else if (strcmp(token, "search") == 0) {
            
            token = strtok_s(NULL, delimiters, &nextToken);
            commandUserName = token;

            //******Place "search" Function Here******
            search(commandUserName);

        }  
            
        else {
            printf("Invalid command!");
        }
     
    }
    // Close the file
    fclose(file);

    printf("\nAll commands in file have been processed!");

    return 0;
}


//Functions
void display(hashRecord* t)
{
  while(t!=NULL)
  {
    printf("\n%x,%s,%d ", t->hash, t->name, t->salary);
    t= t->next;
  }
}


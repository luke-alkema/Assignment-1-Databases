/*
* 
*  FILE				:	 	
*  PROJECT			:	 Assignment 1: E-commerce Inventory Management System
*  PROGRAMMER		:	 Kalina Cathcart (7163611)
*  FIRST VERSION	:	 2024 - 09 - 11
*  DESCRIPTION		:	 This program reads and writes profuct inventory data into multiple types of files (CSV, random access, & sequential). 
* 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>




// function prototypes


// global constants
#define MAX_STRING_LENGTH 100
#define MAX_BUFFER_LENGTH 500




int main(void)
{

	
	FILE* filePointer = NULL;																				// File pointer to navigate files with 
	char bufferString[MAX_BUFFER_LENGTH];																	// Buffer to hold each line of the file
	const char* newProductToInsert = "5, Emergency Disco Ball, Travel Accessories, 85, 29.99";			    // Holds string of data to be inserted into CSV file 
	const char* updatedProductInformation = "3, Rival Bracelet, Accessories, 215, 5.99";					// Holds string of data to update a current line with in the CSV file 

	// CSV file 
		// - standard C libraries only 
		// - make sure can handle special characters
	    // - error handling 

	// opens .csv file for Reading and writing, in a manner that preserves the existing data within (no truncation). The file pointer will begin at the beginning of the file
	filePointer = fopen("CSVInventory.csv", "r+");
	if (filePointer == NULL)
	{

		printf("ERROR: File cannot be opened for reading operations\n");
		return -1;

	}

	// Display data within the file 
	displayFileData(bufferString, filePointer); 




		// Create - add new line 
	printf("Adding new product to file.");
	// Move the file pointer to the end of the file 
	fseek(filePointer, 0, SEEK_END);

	// Write in the new line of data into the file
	fprintf(filePointer, "%s", newProductToInsert);



		// Read  - pull data to read from a line 
	printf("Pulling product 3 from file to read.");



		// Update (Write) - modify existing information 
	printf("Modifying line 3's information.");


		// Delete - remove product from the file 
	printf("Deleting line 1's information.");

	// Redisplay data from file after alterations 
	displayFileData(bufferString, filePointer); 

	// closes file 
	if (fclose(filePointer) != 0)
	{

		// the closing of the file failed
		printf("ERROR: Cannot close opened file.\n");
		return -1;

	}











	// Random Access file 
		// -  


		// Create - add new line  

		// Read  - pull data to read from a line 

		// Update (Write) - modify existing information 

		// Delete - remove product from the file 











	// Sequential file 
		// - 
		 
		
		// Create - add new line  

		// Read  - pull data to read from a line 

		// Update (Write) - modify existing information 

		// Delete - remove product from the file 












	return 0; 

}


// Function Name: displayFileData()
// Purpose: Moves file pointer to beginning of file. Using a while loop, it displays every line present in a file. 
// Parameters: bufferString to hold pulled data, filepointer to navigate files 
// Return Values: none
//

void displayFileData(char bufferString[], FILE* filePointer)
{

	// Move filepointer to the beginning of the file 
	fseek(filePointer, 0, SEEK_SET); 

	// Read and Display all data from file 
	printf("Displaying Data withing the file: \n");

	// While Loop: As long as there is a line of data to print, the next line will be displayed in the terminal. When there are no more lines of data, the loop ends. 
	while (fgets(bufferString, sizeof(bufferString), filePointer))
	{

		printf("\t%s", bufferString);

	}

}

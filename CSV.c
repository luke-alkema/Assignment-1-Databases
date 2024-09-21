/*
*  FILE				:	 CSV.c
*  PROJECT			:	 Assignment 1: E-commerce Inventory Management System
*  PROGRAMMER		:	 Luke Alkema
*  FIRST VERSION	:	 2024 - 09 - 17
*  DESCRIPTION		:	 This program reads and writes product inventory data into multiple types of files (CSV, random access, & sequential).
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)


// function prototypes
void displayFileData(fileName);
int addNewProduct(char* newProduct, char* filename);
int deleteProductLine(int lineNumber, char* fileName);
int updateProduct(int lineNumber, char* fileName, char* newProductInformation);

// global constants
#define MAX_STRING_LENGTH 100
#define MAX_NUMBER_OF_PROUDCTS 40
#define SUCCESS 1
#define FAILURE -1
#define NUMBER_OF_COMMAS 4






int main(void)
{
	

	char fileName[MAX_STRING_LENGTH] = "CSVInventory.csv";	// File pointer to navigate files with 
	const char* newProductToInsert = "5, Emergency Disco Ball, Food, 85, 29.99";	// Holds string of data to be inserted into CSV file 
	const char* otherProductToInsert = ",,,,";
	// Holds string of data to update a current line with in the CSV file 
	const char* updatedProductInformation = "3, Rival Bracelet, Clothing, 215, 5.99";

	//adds two products and then displays them
	addNewProduct(newProductToInsert, fileName);
	addNewProduct(otherProductToInsert, fileName);
	displayFileData(fileName);


	// Update - modify line 2 existing information  and display again
	printf("\nModifying line 2's information: \n");
	updateProduct(2, fileName, updatedProductInformation);
	displayFileData(fileName);



	// Delete - remove product from line 2 from the file 
	printf("Deleting line 2's information.\n");
	deleteProductLine(2, fileName);





	// Redisplay data from file after alterations 
	displayFileData(fileName);



	return 0;

}
// Function Name: checkFormat()
// Purpose: Makes sure the string passed in has exactly 4 commas. 
// Parameters: line. String that is going to be checked
// Return Values: True or False (0,1)
//
int checkFormat(char* line)
{
	int comma_count = 0;

	// Loop through the string to count commas
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == ',')
		{
			comma_count++;
		}
	}
	if (comma_count != 4)
	{
		printf("Ensure data is in the proper CSV Format!");
	}
	// Return true if there are exactly 4 commas, otherwise false 
	return (comma_count == 4);

}




// Function Name: displayFileData()
// Purpose: Moves file pointer to beginning of file. Using a while loop, it displays every line present in a file. 
// Parameters: bufferString to hold pulled data, filepointer to navigate files 
// Return Values: none
//

void displayFileData(char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		printf("ERROR: The file %s cannot be opened for reading!\n", fileName);
		return FAILURE;
	}
	char bufferString[MAX_STRING_LENGTH];
	// Move filepointer to the beginning of the file 
	fseek(file, 0, SEEK_SET);

	// Read and Display all data from file 
	printf("\nDisplaying Data withing the file: \n");

	// While Loop: As long as there is a line of data to print, the next line will be displayed in the terminal. When there are no more lines of data, the loop ends. 
	while (fgets(bufferString, sizeof(bufferString), file))
	{

		printf("\t%s", bufferString);

	}
	printf("\n");

	if (fclose(file) != 0)
	{
		printf("Error closing the file: %s\n", fileName);
	}
}

// Function Name: addNewProduct()
// Purpose: This function adds a new product to the end of a .csv file.
// Parameters: Takes the newProduct to insert, and the file to insert it in
// Return Values: int: True or False 
//
int addNewProduct(char* newProduct, char* filename)
{
	FILE* file = fopen(filename, "a");
	if (file == NULL)
	{
		printf("ERROR: The file %s cannot be opened for appending!\n", filename);
		return FAILURE;
	}
	if (checkFormat(newProduct) != SUCCESS)
	{
		return FAILURE;
	}
	printf("Adding \"%s\" to end of file.\n", newProduct);
	// Move the file pointer to the end of the file 
	fseek(file, 0, SEEK_END);

	// Write in the new line of data into the file
	fprintf(file, "%s\n", newProduct);
	if (fclose(file) != 0)
	{
		printf("Error closing the file: %s\n", filename);
	}

	return SUCCESS;
}


// Function Name: deleteProductLine()
// Purpose: This function deletes the line specified from a .csv file
// Parameters: Takes the line to delete and the file to delete it from
// Return Values: int True or False
//
int deleteProductLine(int lineNumber, char* filename)
{
	int currentLineNumber = 0;
	char buffer[MAX_STRING_LENGTH];
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("ERROR: The file %s cannot be opened for reading!\n", filename);
		return FAILURE;
	}
	FILE* tempFile = tmpfile();
	if (tempFile == NULL)
	{
		printf("ERROR: Could create a temporary file!\n", filename);
		if (fclose(file) != 0)
		{
			printf("Error closing the file: %s\n", filename);
		}
		return FAILURE;
	}
	//Copy the file into a temporary file, but don't copy the specified line
	while (fgets(buffer, MAX_STRING_LENGTH, file))
	{
		currentLineNumber++;
		if (currentLineNumber == lineNumber)
		{
			continue;  //don't copy deleted line
		}
		else
		{
			fputs(buffer, tempFile); //keep other lines the same
		}
	}
	if (currentLineNumber < lineNumber) {
		printf("Error: Specified line number does not exist!\n");
;
		if (fclose(tempFile) != 0)
		{
			printf("Error closing the temporary file");
		}

		if (fclose(file) != 0)
		{
			printf("Error closing the file: %s\n", filename);
		}
		return FAILURE;
	}


	if (fclose(file) != 0)
	{
		printf("Error closing the file: %s\n", filename);
	}



	file = fopen(filename, "w"); 
	if (file == NULL)
	{
		printf("ERROR: The file %s cannot be opened for writing!\n", filename);
		return FAILURE;
	}
	rewind(tempFile); //clear End of file flag and reset the file pointer to beginning

	//Copy the content of the temporary file back into the original file
	while (fgets(buffer, MAX_STRING_LENGTH, tempFile))
	{
		fputs(buffer, file);
	}

	if (fclose(file) != 0)
	{
		printf("Error closing the file: %s\n", filename);
	}
	if (fclose(tempFile) != 0)
	{
		printf("Error closing the temporary file\n");
	}


	return;
}

// Function Name: updateProduct()
// Purpose: Change a product line anywhere in the csv file to updated information
// Parameters: lineNumber to delete, filename to delete from, and the string to replace it.
// Return Values: int True or False (pass or fail)
//
int updateProduct(int lineNumber, char* filename, char* newProductInformation)
{
	int currentLineNumber = 0;
	char buffer[MAX_STRING_LENGTH];
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("ERROR: The file %s cannot be opened for reading!\n", filename);
		return FAILURE;
	}
	FILE* tempFile = tmpfile();
	if (tempFile == NULL)
	{
		printf("ERROR: Could create a temporary file!\n", filename);
		if (fclose(file) != 0)
		{
			printf("Error closing the file: %s\n", filename);
		}
		return FAILURE;
	}

	//copy original file into a temporary file
	while (fgets(buffer, MAX_STRING_LENGTH, file))
	{
		currentLineNumber++;
		if (currentLineNumber == lineNumber)  //If the line number is the one specified
		{
			if (checkFormat(newProductInformation)) //make sure new information is formatted correctly
			{
				fprintf(tempFile, "%s\n", newProductInformation); //write the new information to the file
			}
			else
			{
				fputs(buffer, tempFile); //if the format is wrong, keep the old information
			}
		}
		else
		{
			fputs(buffer, tempFile); //keep other lines the same
		}
	}
	//If Line number never reaches the one specified, they tried to change a line that doesn't exist
	if (currentLineNumber < lineNumber) {
		printf("Error: Specified line number does not exist!\n");
		fclose(tempFile);
		fclose(file);
		return FAILURE;
	}

	fclose(file);
	file = fopen(filename, "w"); //reopen original file this time to overwrite
	if (file == NULL)
	{
		printf("ERROR: The file %s cannot be opened for writing!\n", filename);
		return FAILURE;
	}

	rewind(tempFile); //reset the file pointer

	//copy contents from the temporary file into the original file (with the changes)
	while (fgets(buffer, MAX_STRING_LENGTH, tempFile))
	{
		fprintf(file, buffer);
	}


	if (fclose(file) != 0)
	{
		printf("Error closing the file: %s\n", filename);
	}

	if (fclose(tempFile) != 0)
	{
		perror("Error closing file");
	}
	return SUCCESS;
}


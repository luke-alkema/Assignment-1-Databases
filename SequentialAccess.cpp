/*
* FILE			: SequentialAccess.c
* PROJECT		: Assignment 1: E-commerce Inventory Management System
* PROGRAMMER	: Evan Jolliffe
* FIRST VERSION	: Sept 18th 2024
* DESCRIPTION	: This program reads and writes Products information to a file. It allows the user to add, delete, update, print Products
*				information. This "database" relies on the product having a valid productID to perform all operations.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFile.h"
#pragma warning (disable: 4996)













/*
* Function		:readFromFile()
* Description	:This function reads the "Database" from the file and copies it into the "tempDatabase" in heap memory.
* Parameters	:FILE* filePointer: Pointer to the file containing the Database.
*				 struct Products*: Pointer to an array of Products in heap memory. Database to be copied into the array.
* Returns		:No Returns.
*/

void readFromFile(FILE* filePointer, struct Products* tempProducts)
{

	fseek(filePointer, 0, SEEK_SET); //Setting the file pointer

	struct Products temp = { 0 }; //Creating a temporary struct

	for (int i = 0; i <= DATABASESIZE; i++) //Loops through file 
	{

		fread(&temp, sizeof(struct Products), 1, filePointer); //Reads from file
		if (temp.productID > 0) //If the ID is a valid ID
		{

			tempProducts[i] = temp; //Places product into temporary array

		}

	}

}



/*
* Function		:printMemory()
* Description	:This function prints all the Products stored in memory.
				It checks to see if the array element has a valid productID and prints the contents.
* Parameters	:struct Products* tempProducts: a pointer to the array of Products to be printed.
* Returns		:No Returns.
*/

void printMemory(struct Products* tempProducts)
{

	for (int i = 0; i <= DATABASESIZE; i++) //Loops through file
	{

		if (tempProducts[i].productID > 0) //If ID is a valid value
		{

			printf("Product Id: %d\nProduct Name: %s\nProduct Catagory: %s\nQuantity: %d\nPrice: %.2f\n"
				, tempProducts[i].productID, tempProducts[i].productName, tempProducts[i].productCategory, tempProducts[i].productQuantity
				, tempProducts[i].productPrice); //Print product information

		}

	}

}



/*
* Function		:writeToFile()
* Description	:This function writes the temporary Database to the database file. It checks to see if the array inded has a valid
*				productID and prints the element to the file.
* Parameters	:FILE* fp: Pointer to the file to be written to.
*				struct Products* tempProducts: A pointer to the array of Products to be written to the file.
* Returns		:int : and Integer number returning the number of elements written to the file.
*/

int writeToFile(FILE* fp, struct Products* tempProducts)
{

	fseek(fp, 0, SEEK_SET); //Sets file pointer

	struct Products temp = { 0 }; //Creates a temporary struct

	int counter = 0;

	for (int i = 0; i <= DATABASESIZE; i++) //Loops through file
	{

		temp = tempProducts[i]; //Sets values in temporary arrays

		if (temp.productID != 0) //If ID is a valid value
		{

			fwrite(&temp, sizeof(struct Products), 1, fp); //Write product information
			counter++;

		}

	}

	return counter;

}



/*
* Function		:addProduct()
* Description	:This function adds a newProduct to the array of Products in heap memory. It checks if newProduct has a valid productId
*				and then writes it into the first available element in the array.
* Parameters	:struct Products* tempProducts: Pointer to the array of Products in heap memory (temporary database).
*				struct Products newProduct: Contains a new Products to be added to the temp database.
* Returns		:int : and integer number indicating Success or Error.
*/

int addProduct(struct Products* tempProducts, struct Products newProduct)
{

	if (newProduct.productID == 0) //If new product is empty
	{

		return ERROR;

	}

	for (int i = 0; i <= DATABASESIZE; i++) //Loops through file
	{

		if (tempProducts[i].productID < 1) //If spot in array is empty
		{

			tempProducts[i] = newProduct; //Write product to spot in array
			return SUCCESS;

		}

	}

	return ERROR; //If writing product failed

}



/*
* Function		:deleteProduct()
* Description	:This function deletes a Product from the temporary Database using the ProductsID number.
				This function does not check for recurring productIDs.
* Parameters	:struct Products* tempProducts: Pointer to the temporary database.
*				int productID: integer number containing the productID to be deleted.
* Return		:int : an Integer value indicating Success or Error
*/

int deleteProduct(struct Products* tempProducts, int productId)
{

	for (int i = 0; i <= DATABASESIZE; i++) //Loops through file
	{

		if (tempProducts[i].productID == productId) //If product ID is equal to that of product to be deleted
		{

			//Empties that product's spot in the array
			tempProducts[i].productID = 0;
			strcpy(tempProducts[i].productName, "\0");
			strcpy(tempProducts[i].productCategory, "\0");
			tempProducts[i].productQuantity = 0;
			tempProducts[i].productPrice = 0;

			return SUCCESS;

		}

	}

	return ERROR; //If product could not be deleted

}



/*
* Function		:updateProduct()
* Description	:This function updates and existing Product in the temp database with new information. It searches through the
*				temp database for a matching productID and then writes over the element with the new information.
* Parameters	:struct Products* tempProducts: Pointer to the temp database
*				struct Products updatedProduct: A Products containing the new information to update the Product element with.
* Returns		:int : and Integer indicating Success or Error.
*/

int updateProduct(struct Products* tempProducts, struct Products updatedProduct)
{

	for (int i = 0; i <= DATABASESIZE; i++) //Loops through file
	{

		if (tempProducts[i].productID == updatedProduct.productID) //If ID is equal to that of product to be updated
		{

			//Update product information
			strcpy(tempProducts[i].productName, updatedProduct.productName);
			strcpy(tempProducts[i].productCategory, updatedProduct.productCategory);
			tempProducts[i].productQuantity = updatedProduct.productQuantity;
			tempProducts[i].productPrice = updatedProduct.productPrice;

			return SUCCESS;

		}

	}

	return ERROR; //If product could not be updated.

}
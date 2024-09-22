/*
* FILE			: RandomAccess.c
* PROJECT		: Assignment 1: E-commerce Inventory Management System
* PROGRAMMER	: Jacob Atienza
* FIRST VERSION	: Sept 18th 2024
* DESCRIPTION	: This program reads and writes Products information to a file. It allows the user to add, delete, update, print Products
*				information. This "database" relies on the product having a valid productID to perform all operations.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "headerFile.h"

#pragma warning (disable: 4996)


int updateProductRA(Products updatedProduct, FILE* fp);
int searchForID(FILE* fp, int productId);
int isError(int errorCode);












/*
* Function		:isError(int errorCode)
* Description	:This function takes the error codes returned by the functions and returns an error code
* Parameters	:int errorCode, an integer representing the error code constant
* Returns		:void
*/

int isError(int errorCode)
{

	switch (errorCode)
	{

	case ERROR:
	{

		printf("ERROR: Requested operation resulted in an error\n");
		return ERROR;
		break;

	}
	case NOT_USED:
	{

		printf("ERROR: The ID given does not match any product id\n");
		return NOT_USED;
		break;

	}
	case IS_USED:
	{

		printf("ERROR: The ID given is already in use by another product\n");
		return IS_USED;
		break;

	}
	case SUCCESS:
	{

		return SUCCESS;
		break;

	}
	case PRODUCT_STANDARD:
	{

		return PRODUCT_STANDARD;
		break;

	}
	default:

		printf("ERROR: Unknown Error Occurred\n");
		return UNKNOWN_ERROR;
		break;
	}
}



/*
* Function		:printByProductId(int productId, FILE* fp)
* Description	:This function prints the attributes info for a given product ID.
* Parameters	:int productId, an integer representing the product ID
*				:FILE* fp, a file pointer to the database file
* Returns		:int, an integer representing the success or error code
*/

int printByRAProductID(int productId, FILE* fp)
{

	int idStatus = 0;
	Products tempProduct = { 0 };



	idStatus = searchForID(fp, productId);

	if (idStatus == ERROR)
	{

		return ERROR;

	}
	else if (idStatus == NOT_USED)
	{

		return NOT_USED;

	}



	fseek(fp, sizeof(Products) * (productId - 1), SEEK_SET);
	fread(&tempProduct, sizeof(Products), 1, fp);
	printf("Product Id: %d\n", tempProduct.productID);
	printf("Product Name: %s\n", tempProduct.productName);
	printf("Product Category: %s\n", tempProduct.productCategory);
	printf("Product Quantity: %d\n", tempProduct.productQuantity);
	printf("Product Price: %.2f\n", tempProduct.productPrice);

	return SUCCESS;

}



/*
* Function		:searchForId(FILE* fp, int productId)
* Description	:This function searches for a product by its id in the database file.
* Parameters	:FILE* fp, a file pointer to the database file
*				:int productId, an integer representing the product id to be searching for
* Returns		:int, an integer representing the status of the product id (used, not used, or error)
*/

int searchForID(FILE* fp, int productID)
{

	Products product = { 0 };

	if (productID <= 0)
	{

		return ERROR;

	}



	fseek(fp, sizeof(Products) * (productID - 1), SEEK_SET);

	if (fread(&product, sizeof(Products), 1, fp) != 1)
	{

		return NOT_USED;

	}
	if (product.isDeleted == true)
	{

		return NOT_USED;

	}


	return IS_USED;

}



/*
* Function		:addProduct(Products newProduct, FILE* fp)
* Description	:This function adds a new product to the database file. Also performs validation for the product fields
* Parameters	:Products newProduct, a structure representing the new product
*				:FILE* fp, a file pointer to the database file
* Returns		:int, an integer representing the success or error code
*/

int addProductRA(Products newProduct, FILE* fp)
{

	if (searchForID(fp, newProduct.productID) == IS_USED)
	{

		return IS_USED;

	}



	//Make sure product information is valid according to specifications
	if (newProduct.productName != NULL && newProduct.productCategory != NULL
		&& newProduct.productQuantity >= 0 && newProduct.productPrice > 0)
	{

		fseek(fp, sizeof(Products) * (newProduct.productID - 1), SEEK_SET);
		fwrite(&newProduct, sizeof(Products), 1, fp);
		return SUCCESS;

	}

	return PRODUCT_STANDARD;

}



/*
* Function		:deleteProduct(int productId, FILE* fp)
* Description	:This function deletes a product from the database file by marking it as deleted. and setting the values to the minimum
* Parameters	:int productId, an integer representing the product id
*				:FILE* fp, a file pointer to the database file
* Returns		:int, an integer representing the success or error code
*/

int deleteProductRA(int productID, FILE* fp)
{

	Products productToBeDeleted = { productID, "DELETED", "DELETED", 0, 0, true };

	if (searchForID(fp, productID) == IS_USED)
	{

		if (updateProductRA(productToBeDeleted, fp) == ERROR)
		{

			return ERROR;

		}

		return SUCCESS;

	}

	return ERROR;

}



/*
* Function		:updateProduct(Products updatedProduct, FILE* fp)
* Description	:This function updates the information of an existing product in the database file.
* Parameters	:Products updatedProduct, a structure representing the updated product
*				:FILE* fp, a file pointer to the database file
* Returns		:int, an integer representing the success or error code
*/

int updateProductRA(Products updatedProduct, FILE* fp)
{

	fseek(fp, sizeof(Products) * (updatedProduct.productID - 1), SEEK_SET);
	if (fwrite(&updatedProduct, sizeof(Products), 1, fp) != 1)
	{

		return ERROR;

	}

	return SUCCESS;

}
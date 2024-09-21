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
#pragma warning (disable: 4996)



#define FILENAME "RandomAccessFile.dat"
#define STRINGSIZE 50
#define SUCCESS 0
#define ERROR 1
#define NOT_USED 2
#define IS_USED 3
#define PRODUCT_STANDARD 4
#define UNKNOWN_ERROR 5



// Structure: Products
// Description: Contains fields describing information related to a product listed in the file. 

typedef struct Products 
{

	int productId;
	char productName[STRINGSIZE];
	char productCategory[STRINGSIZE];
	int productQuantity;
	double productPrice;
	bool isDeleted;

}Products;



//Function Prototypes
int addProduct(Products newProduct, FILE* fp);
int deleteProduct(int productId, FILE* fp);
int updateProduct(Products updatedProduct, FILE* fp);
int printByProductId(int productId, FILE* fp);
int searchForId(FILE* fp, int productId);
void isError(int errorCode);





int main() 
{

	FILE* fp = NULL;

	Products defaultLaptop = { 1, "Laptop", "Electronics", 40, 2200.78, false };
	Products smartPhone = { 2, "Smartphone", "Electronics", 50, 999.99, false };
	Products updatedProduct = { 1, "Dell Laptop", "Electronics", 35, 2256.34, false };
	int productToDelete = 1;


	if ((fp = fopen(FILENAME, "r+b")) == NULL) 
	{

		printf("ERROR: Failed to open file, closing program.\n");
		return 0;

	}

	// Add new products
	isError(addProduct(defaultLaptop, fp));
	isError(addProduct(smartPhone, fp));

	//Display products
	isError(printByProductId(defaultLaptop.productId, fp));
	isError(printByProductId(smartPhone.productId, fp));

	//Update Laptop to Dell Laptop
	isError(updateProduct(updatedProduct, fp));

	//Display new output
	isError(printByProductId(1, fp));

	//Delete Smartphone
	isError(deleteProduct(smartPhone.productId, fp));
	//Show it wont print
	isError(printByProductId(2, fp));

	fclose(fp);
	return 1;

}





/*
* Function		:isError(int errorCode)
* Description	:This function takes the error codes returned by the functions and returns an error code
* Parameters	:int errorCode, an integer representing the error code constant
* Returns		:void
*/

void isError(int errorCode) 
{

	switch (errorCode) 
	{

		case ERROR: 
		{

			printf("ERROR: Requested operation resulted in an error\n");
			exit(ERROR);
			break;

		}
		case NOT_USED: 
		{

			printf("ERROR: The ID given does not match any product id\n");
			exit(NOT_USED);
			break;

		}
		case IS_USED: 
		{

			printf("ERROR: The ID given is already in use by another product\n");
			exit(IS_USED);
			break;

		}
		case SUCCESS: 
		{

			return SUCCESS;

		}
		case PRODUCT_STANDARD: 
		{

			exit(PRODUCT_STANDARD);

		}
		default:

			printf("ERROR: Unknown Error Occurred\n");
			exit(UNKNOWN_ERROR);
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

int printByProductId(int productId, FILE* fp) 
{

	int idStatus = 0;
	Products tempProduct = { 0 };



	idStatus = searchForId(fp, productId);

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
	printf("Product Id: %d\n", tempProduct.productId);
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

int searchForId(FILE* fp, int productId) 
{

	Products product = { 0 };

	if (productId <= 0) 
	{

		return ERROR;

	}



	fseek(fp, sizeof(Products) * (productId - 1), SEEK_SET);

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

int addProduct(Products newProduct, FILE* fp) 
{

	if (searchForId(fp, newProduct.productId) == IS_USED) 
	{

		return ERROR;

	}



	//Make sure product information is valid according to specifications
	if (newProduct.productName != NULL && newProduct.productCategory != NULL 
		&& newProduct.productQuantity >= 0 && newProduct.productPrice > 0) 
	{

		fseek(fp, sizeof(Products) * (newProduct.productId - 1), SEEK_SET);
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

int deleteProduct(int productId, FILE* fp) 
{

	Products productToBeDeleted = { productId, "DELETED", "DELETED", 0, 0, true };

	if (searchForId(fp, productId) == IS_USED) 
	{

		if (updateProduct(productToBeDeleted, fp) == ERROR) 
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

int updateProduct(Products updatedProduct, FILE* fp) 
{

	fseek(fp, sizeof(Products) * (updatedProduct.productId - 1), SEEK_SET);
	if (fwrite(&updatedProduct, sizeof(Products), 1, fp) != 1) 
	{

		return ERROR;

	}

	return SUCCESS;

}
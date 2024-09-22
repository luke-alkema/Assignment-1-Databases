/*
* FILE			: headerFile.h
* PROJECT		: Assignment 1: E-commerce Inventory Management System
* PROGRAMMER	: // 
* FIRST VERSION	: Sept 18th 2024
* DESCRIPTION	: This file holds the struct for products. See product struct description for more details 
*/

#pragma once



#ifndef HEADER_FILE  
#define HEADER_FILE 



// Global Constants
#define MAX_STRING_LENGTH 100
#define MAX_NUMBER_OF_PRODUCTS 40

#define FILENAME_CSV "CSVInventory.csv"
#define FILENAME_RANDOM "RandomAccessFile.dat"
#define FILENAME_SEQUENTIAL "SequentialFile.dat"

#define DATABASESIZE 100
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

	int productID;
	char productName[STRINGSIZE];
	char productCategory[STRINGSIZE];
	int productQuantity;
	double productPrice;
	bool isDeleted;

}Products;



// function prototypes: CSV 
int displayCSVFile(const char* filename);
int addNewProductCSV(const char* newProduct, const char* filename);
int deleteProductLineCSV(int lineNumber, const char* fileName);
int updateProductCSV(int lineNumber, const char* fileName, const char* newProductInformation);
int checkFormatCSV(const char* line);


//Function Prototypes: Random Access 
int addProductRA(Products newProduct, FILE* fp);
int deleteProductRA(int productId, FILE* fp);
int updateProductRA(Products updatedProduct, FILE* fp);
int printByRAProductID(int productId, FILE* fp);
int searchForID(FILE* fp, int productId);
int isError(int errorCode);


//Function Prototypes: Sequential Access 
void readFromFile(FILE* filePointer, struct Products* tempProducts);
void printMemory(struct Products* tempProducts);
int writeToFile(FILE* fp, struct Products* tempProducts);
int addProduct(struct Products* tempProducts, struct Products newProduct);
int deleteProduct(struct Products* tempProducts, int productId);
int updateProduct(struct Products* tempProducts, struct Products updatedProduct);

//Function Prototypes: Main 
void csvOperations();
void randomAccessOperations();
void sequentialAccessOperations();
int mainMenu();




#endif //HEADER_FILE 
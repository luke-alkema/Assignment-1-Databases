/*
* FILE			: main.c
* PROJECT		: Assignment 1: E-commerce Inventory Management System
* PROGRAMMER	: Kalina Cathcart
* FIRST VERSION	: Sept 21 2024
* DESCRIPTION	: This file holds the main program to run the other functions. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headerFile.h"



#pragma warning(disable: 4996)




int main(void) 
{

    // Call main Menu function 
    mainMenu(); 


    //Program End
    return 0; 

}




// Function Name: mainMenu()
// Purpose: Shows menu to user and allows user to choose which file operations to perform 
// Parameters: none
// Return Values: integer noting success or failure

int mainMenu(void)
{

    int choice = 0; // holds user's menu selection
    char bufferString[STRINGSIZE]; // buffer for user input



    do
    {

        // Display menu 
        printf("\n\nWelcome to Assignment 1 File Operations Program\n");
        printf("Select operation:\n");
        printf("1. CSV Operations\n");
        printf("2. Random Access Operations\n");
        printf("3. Sequential Access Operations\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");

        // Retrieve user choice if present
        if (fgets(bufferString, sizeof(bufferString), stdin) != NULL)
        {

            sscanf(bufferString, "%d", &choice);

        }


        switch (choice)
        {

        case 1:
            printf("Performing CSV file operations...\n");
            csvOperations();
            break;

        case 2:
            printf("Performing Random Access file operations...\n");
            randomAccessOperations();
            break;

        case 3:
            printf("Performing Sequential Access file operations...\n");
            sequentialAccessOperations();
            break;

        case 4:
            printf("Exiting File Operations Program...\n");
            break;

        default:
            printf("ERROR: Invalid choice. Please try again.\n");
            break;

        }

    } while (choice != 4);


    return 0;


}




// Function Name: csvOperations()
// Purpose: Shows user CSV CRUD operations in use on the CSV file 
// Parameters: none
// Return Values: none

void csvOperations()
{



    char fileName[MAX_STRING_LENGTH] = "CSVInventory.csv";								// File pointer to navigate files with 
    const char* newProductToInsert = "5, Emergency Disco Ball, Food, 85, 29.99";		// Holds string of data to be inserted into CSV file 
    const char* otherProductToInsert = ",,,,";											// Secondary line of data to be inserted, this is used to show empty product data 
    const char* updatedProductInformation = "3, Rival Bracelet, Clothing, 215, 5.99";	// Holds string of data to update a current line with in the CSV file 



    //adds two products and then displays them
    addNewProductCSV(newProductToInsert, fileName);
    addNewProductCSV(otherProductToInsert, fileName);
    displayCSVFile(fileName);



    // Update - modify line 2 existing information  and display again
    printf("\nModifying line 2's information: \n");
    updateProductCSV(2, fileName, updatedProductInformation);
    displayCSVFile(fileName);



    // Delete - remove product from line 2 from the file 
    printf("Deleting line 2's information.\n");
    deleteProductLineCSV(2, fileName);



    // Redisplay data from file after alterations 
    displayCSVFile(fileName);


}



// Function Name: randomAccessOperations()
// Purpose: Shows user Random Access CRUD operations in use on the Random Access file 
// Parameters: none
// Return Values: none

void randomAccessOperations()
{


    FILE* fp = NULL;

    Products defaultLaptop = { 1, "Laptop", "Electronics", 40, 2200.78, false };
    Products smartPhone = { 2, "Smartphone", "Electronics", 50, 999.99, false };
    Products updatedProduct = { 1, "Dell Laptop", "Electronics", 35, 2256.34, false };
    int productToDelete = 1;


    if ((fp = fopen(FILENAME_RANDOM, "r+b")) == NULL)
    {

        printf("ERROR: Failed to open file, closing program.\n");
      

    }

    // Add new products
    isError(addProductRA(defaultLaptop, fp)); 
    isError(addProductRA(smartPhone, fp)); 

    //Display products
    isError(printByRAProductID(defaultLaptop.productID, fp));
    isError(printByRAProductID(smartPhone.productID, fp));

    //Update Laptop to Dell Laptop 
    isError(updateProductRA(updatedProduct, fp)); 

    //Display new output
    isError(printByRAProductID(1, fp)); 

    //Delete Smartphone
    isError(deleteProductRA(smartPhone.productID, fp)); 
    //Show it wont print
    isError(printByRAProductID(2, fp)); 


    // Check if file is NULL before attempting to close 
    if (fp != NULL && fclose(fp) == 0) 
    { 

        printf("File closed successfully! Thank you!\n");

    }




}



// Function Name: sequentialAccessOperations()
// Purpose: Shows user Sequential Access CRUD operations in use on the Sequential Access  file 
// Parameters: none
// Return Values: none

void sequentialAccessOperations()
{


    FILE* fp = { NULL };



    //Creating sample products
    struct Products* tempProducts = (struct Products*)malloc(sizeof(struct Products[DATABASESIZE]));
    struct Products newProduct = { 1, "Laptop", "Electronics", 40, 2200.78 };
    struct Products updatedProduct = { 1, "Dell Laptop", "Electronics", 35 , 2256.34 };
    int productToDelete = 0;




    if ((fp = fopen(FILENAME_SEQUENTIAL, "r+b")) == NULL) //If file fails to open 
    {

        printf("ERROR: Failed to Open file; closing program");

    }



    readFromFile(fp, tempProducts); //Reads file information into an array of structs

    if (addProduct(tempProducts, newProduct) == ERROR) //Add products to database
    {

        printf("ERROR: There was a problem adding your product to the Database..."); //If products were unable to be added

    }



    if (deleteProduct(tempProducts, productToDelete) == ERROR) //Deletes a product
    {

        printf("ERROR: There was a problem deleting your product from the Database..."); //If product was not able to be deleted

    }



    if (updateProduct(tempProducts, updatedProduct) == ERROR) //Updating an already existing product
    {

        printf("ERROR: There was a problem with updating your product in the Database..."); //If product was not able to be updated

    }



    printMemory(tempProducts); //Print current products

    if (writeToFile(fp, tempProducts) < 1) //Write any changes to the file
    {

        printf("ERROR: Nothing was written to the file. (Is there anything in memory?)"); //If nothing was changed

    }



    // Check if file is NULL before attempting to close 
    if (fp != NULL && fclose(fp) == 0) 
    { 

        printf("File closed successfully! Thank you!\n");

    }

    free(tempProducts); //Free used space

}
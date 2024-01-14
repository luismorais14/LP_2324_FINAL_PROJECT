/**
 * @file main.c
 * @brief Main program file for the Company Management System.
 * @author Luís Morais & Cláudio Coelho
 * @date 24-11-2023
 * 
 * @brief The C program consists of developing a business directory application that allows users to 
 * discover, evaluate and interact with industrial and service companies located in a given geographical region.
 * This project aims to connect consumers with local businesses and promote economic activity.
 * 
 * @version 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "companies.h"
#include "input.h"
#include "admin.h"
#include "user.h"


#define FILENAME "companies.bin"

/**
 * @brief Main function to execute the program.
 * @return Returns EXIT_SUCCESS upon successful execution.
 */
int main(int argc, char** argv) { 
    // Initialize Companies, Company and BranchActivity structures
    Companies companies = {
        .companiesCounter = 0,
        .maxCompanies = 10,
    };
    
    Company company = {
       .classification = 0 
    };
        
    BranchActivity branch = {
        .maxBranch = 7,
        .branchCounter = 0
    };

    // Load data from the specified file
    loadData(&companies, &branch, FILENAME);
    
    // Execute the main menu functionality
    mainMenu(&companies, &branch);

    // Save data to the specified file
    saveData(&companies, &branch, FILENAME);
    
    // Free allocated memory for Companies and BranchActivity
    freeCompanies(&companies, &company, &branch);

    return (EXIT_SUCCESS);
}

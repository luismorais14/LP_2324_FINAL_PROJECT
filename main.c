/*
 * File:   main.c
 * Author: Luís Morais & Cláudio Coelho
 *
 * Created on 24 de novembro de 2023, 09:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "companies.h"
#include "input.h"

#define FILENAME "companies.bin"

/*
 *
 */


int main(int argc, char** argv) { 
    Companies companies = {
        .maxCompanies = 10,
        .companiesCounter = 0
    };
    
    BranchActivity branch = {
        .branchCounter = 0,
        .maxBranch = 7,
    };


    loadCompaniesFromFile(&companies, &branch, FILENAME);
    
    
    mainMenu(&companies, &branch, FILENAME);
    
    saveCompanies(&companies, &branch, FILENAME);

    freeCompanies(&companies, &branch);

    puts("End.");

    return (EXIT_SUCCESS);
}


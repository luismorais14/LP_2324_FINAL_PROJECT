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
        .companiesCounter = 0,
        .maxCompanies = 10
    };
        
    BranchActivity branch = {
        .maxBranch = 7,
        .branchCounter = 0
    };


    loadData(&companies, &branch, FILENAME);
    
    mainMenu(&companies, &branch, FILENAME);

    saveData(&companies, &branch, FILENAME);
    
    freeCompanies(&companies, &branch);

    return (EXIT_SUCCESS);
}
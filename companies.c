/**
 * @file companies.c
 * @brief Implementation of company-related functions.
 * @author Luís Morais & Cláudio Coelho
 * @date 24-11-2023
 */

#include "companies.h"
#include "input.h"
#include "tools.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "user.h"
#include "admin.h"
#include <ctype.h>
#include <time.h>

/**
 * @brief Convert a Category enum type to a string.
 * @param category The Category enum value.
 * @return A string representation of the Category.
 */
const char *convertTypeCategory(Category category) {
    switch (category) {
        case MICRO:
            return "Micro";
        case PME:
            return "PME";
        case GRANDE:
            return "Grande";
    }
}

/**
 * @brief Convert a Status enum type to a string.
 * @param status The Status enum value.
 * @return A string representation of the Status.
 */
const char *convertTypeStatus(Status status) {
    switch (status) {
        case INATIVO:
            return "Inativo";
        case ATIVO:
            return "Ativo";
    }
}

/**
 * @brief Verify the validity of an email address in a comment.
 * @param comment The comment containing the email address.
 * @return 1 if the email is valid, -1 otherwise.
 */
int emailVerification(Comment *comment) {
    char *atSymbol = strchr(comment->email, '@');
    char *dotSymbol = strchr(comment->email, '.');

    if (atSymbol == NULL || dotSymbol == NULL || atSymbol > dotSymbol) {
        puts(ERROR_INVALID_EMAIL);
        
        strcpy(comment->email, "");
        return -1;
    }
    return 1;
}

/**
 * @brief Verify the validity of a postal code.
 * @param zipCode The postal code to be verified.
 * @return 0 if the postal code is valid, -1 otherwise.
 */
int postalCodeVerification(char *zipCode) {
    if (strlen(zipCode) == 8 && isdigit(zipCode[0]) && isdigit(zipCode[1]) && isdigit(zipCode[2]) && isdigit(zipCode[3]) && zipCode[4] == '-' && isdigit(zipCode[5]) && isdigit(zipCode[6]) && isdigit(zipCode[7])) {
        return 0;
    }
    puts("Invalid postal code format. Please enter a new one.");
    return -1;
}

/**
 * @brief Search for a company based on its NIF in the list of companies.
 * @param companies The structure containing the list of companies.
 * @param number The NIF to search for.
 * @return The index of the company with the specified NIF or -1 if not found.
 */
int searchCompanyNif(Companies companies, int number) {
    int i;
    for (i = 0; i < companies.companiesCounter; i++) {
        if (companies.company[i].nif == number) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Search for a company based on its name in the list of companies.
 * @param companies The structure containing the list of companies.
 * @param name The name to search for.
 * @return The index of the company with the specified name or -1 if not found.
 */
int searchCompanyName(Companies companies, char *name) {
    int i;
    for (i = 0; i < companies.companiesCounter; i++) {
        if (strcmp(name, companies.company[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Search for a company based on its location in the list of companies.
 * @param companies The structure containing the list of companies.
 * @param location The location to search for.
 * @return The index of the company with the specified location or -1 if not found.
 */
int searchCompanyLocation(Companies companies, char *location) {
    int i;
    for (i = 0; i < companies.companiesCounter; i++) {
        if (strcmp(location, companies.company[i].location) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Print the details of a company and its associated branch.
 * @param company The company to print.
 * @param branch The branch associated with the company.
 */
void printCompany(Company company, Branch branch) {
    if (company.status == ATIVO && branch.status == ATIVO) {
        puts("----------------------------");
        printf("Name: %s\n", company.name);
        printf("Nif: %u\n", company.nif);
        printf("Adress: %s\n", company.adress);
        printf("Location: %s\n", company.location);
        printf("Postal Code: %s\n", company.postalCode);
        printf("Branch of Activity: %s\n", company.branch);
        printf("Category: %s\n", convertTypeCategory(company.companyCategory));
        puts("----------------------------");
    } else {
        puts("This company is inactive.");
    }
}

/**
 * @brief Check if a branch with the given name already exists in the list.
 * @param branch The structure containing the list of branches.
 * @param activity The name of the branch to check.
 * @return 1 if the branch already exists, -1 otherwise.
 */
int checkActivity(BranchActivity branch, char *activity) {
    int i;

    for (i = 0; i < branch.branchCounter; i++) {
        if (strcmp(branch.branch[i].branch, activity) == 0) {
            puts(ERROR_BRANCH_ALREADY_EXIST);
            return 1;
        } 
    }

    return -1;
}

/**
 * @brief Print the list of branches.
 * @param branch The structure containing the list of branches.
 */
void printBranches(BranchActivity branch) {
    int i;
    for (i = 0; i < branch.branchCounter; i++) {
        printf("%d- %s\n", i , branch.branch[i].branch);
    }
}

/**
 * @brief Edit the branch activity by choosing a branch to edit.
 * @param branch A pointer to the BranchActivity structure.
 * @return The index of the selected branch.
 */
int editBranch(BranchActivity *branch) {
    int option;
    
    do {
        puts("Chose the Branch you want to edit");
        printBranches(*branch);
        scanf("%d",&option);
    
    } while ( option < 0 || option > branch->branchCounter - 1);
    
    return option;
}

/**
 * @brief Clear the data of a company.
 * @param company The company to clear.
 */
void deleteCompanyData(Company *company) {
    strcpy(company->name, "");
    strcpy(company->adress, "");
    strcpy(company->branch, "");
    strcpy(company->postalCode, "");
    strcpy(company->location, "");
    company->nif = 0;
    company->status = INATIVO;
    company->companyCategory = EMPTY;
}

/**
 * @brief Calculate the average rating of a company based on its classifications.
 * @param company The company for which to calculate the average rating.
 * @return The average rating.
 */
float calculateAverageRating(Company *company) {
    if (company->classificationCounter > 0) {
        return (float) company->classification / company->classificationCounter;
    }
    return 0; 
}

/**
 * @brief List the titles of comments for a given company.
 * @param company The company for which to list comments.
 */
void listCommentsTitle(Company company) {
    int i;
    
    for (i = 0; i < company.commentsCounter; i++) {
        printf("%d - %s\n", i, company.comments[i].title);
    }
}

/**
 * @brief Clear the data of a comment in a company.
 * @param company The company containing the comment.
 * @param index The index of the comment to delete.
 */
void deleteCommentsData(Company *company, int index) {
    strcpy(company->comments[index].email, "");
    strcpy(company->comments[index].text, "");
    strcpy(company->comments[index].title, "");
    strcpy(company->comments[index].username, "");
    company->comments[index].status = INATIVO;
}

/**
 * @brief Remove a branch from the list.
 * @param branch A pointer to the BranchActivity structure.
 * @return The index of the removed branch.
 */
int removeBranch(BranchActivity *branch) {
    int option;
    
    do {
        puts("Choose the Branch you want to delete");
        printBranches(*branch);
        scanf("%d", &option);
    
    } while (option < 0 || option > branch->branchCounter - 1);
    
    return option;
}

/**
 * @brief Save company and branch data to a file.
 * @param companies The structure containing the list of companies.
 * @param branch The structure containing the list of branches.
 * @param filename The name of the file to save to.
 */
void saveData(Companies *companies, BranchActivity *branch, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(companies, sizeof(Companies), 1, fp);
    fwrite(branch, sizeof(BranchActivity), 1, fp);

    for (int i = 0; i < companies->companiesCounter; i++) {
        fwrite(&companies->company[i], sizeof(Company), 1, fp);
        fwrite(&branch->branch[i], sizeof(Branch), 1, fp);

        for (int j = 0; j < companies->company[i].commentsCounter; j++) {
            fwrite(&companies->company[i].comments[j], sizeof(Comment), 1, fp);
            
        }
    }

    fclose(fp);
}

/**
 * @brief Load company and branch data from a file.
 * @param companies The structure to store the list of companies.
 * @param branch The structure to store the list of branches.
 * @param filename The name of the file to load from.
 */
void loadData(Companies *companies, BranchActivity *branch, char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fp = fopen(filename, "wb");
        if (fp == NULL) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }
        fclose(fp);
        fp = fopen(filename, "rb");
        if (fp == NULL) {
            perror("Error opening file for reading");
            exit(EXIT_FAILURE);
        }
    }

    fread(companies, sizeof(Companies), 1, fp);
    fread(branch, sizeof(BranchActivity), 1, fp);

    companies->company = (Company *) malloc(companies->maxCompanies * sizeof(Company));

    branch->branch = (Branch *) malloc(branch->maxBranch * sizeof(Branch));

    for (int i = 0; i < companies->companiesCounter; i++) {
        fread(&companies->company[i], sizeof(Company), 1, fp);
        fread(&branch->branch[i], sizeof(Branch), 1, fp);
        
        companies->company[i].comments = (Comment *) malloc(companies->company[i].maxComments * sizeof(Comment));
        fread(companies->company[i].comments, sizeof(Comment), companies->company[i].commentsCounter, fp);
        
    }

    fclose(fp);
}

/**
 * @brief Frees the allocated memory for Companies, Company, and BranchActivity structures.
 *
 * This function deallocates the memory allocated for the Companies, Company, and BranchActivity structures
 * and sets the corresponding pointers to NULL to avoid dangling pointers.
 *
 * @param companies A pointer to the Companies structure.
 * @param company   A pointer to the Company structure.
 * @param branch    A pointer to the BranchActivity structure.
 */
void freeCompanies(Companies *companies, Company *company, BranchActivity *branch) {
    if (companies->company) {
        free(companies->company);
        companies->company = NULL;
    }

    if (branch->branch) {
        free(branch->branch);
        branch->branch = NULL;
    }
    
    if (company->comments) {
        free(company->comments);
        company->comments = NULL;
    }

    companies = NULL;
    branch = NULL;
    company = NULL;
}

/**
 * @brief List comments for a given company.
 * @param company The company for which to list comments.
 */
void listComments(Company company) {
    for (int i = 0; i < company.commentsCounter; i++) {
        puts("----------------------------");
        printf("\nUsername: %s\n", company.comments[i].username);
        printf("Title: %s\n", company.comments[i].title);
        printf("Comment: %s\n", company.comments[i].text);
        puts("----------------------------");
    }
}

/**
 * @brief Find the most searched companies based on user search counters.
 * @param companies The structure containing the list of companies.
 * @param size The size of the array to store the most searched companies.
 * @param array An array to store the indices of the most searched companies.
 */
void mostSearchedCompanies(Companies companies, int size, int *array) {
    int actualHighNumbers = 0, counter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < companies.companiesCounter; j++) {
            int searchCounter = companies.company[j].searchCounter;

            if (searchCounter > actualHighNumbers) {
                for (int h = 0; h < size; h++) {
                    if (j == array[h]) {
                        counter++;
                    }
                }
                if (counter == 0) {
                    actualHighNumbers = searchCounter;
                    array[i] = j;
                }
            }
        }
    }
}


void logFile(char *msg, char *filename) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d - %s\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, msg);

    fclose(fp);
}




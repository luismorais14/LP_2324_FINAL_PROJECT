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

const char *convertTypeStatus(Status status) {
    switch (status) {
        case INATIVO:
            return "Inativo";
        case ATIVO:
            return "Ativo";
    }
}

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

int postalCodeVerification(char *zipCode) {
    if (strlen(zipCode) == 8 && isdigit(zipCode[0]) && isdigit(zipCode[1]) && isdigit(zipCode[2]) && isdigit(zipCode[3]) && zipCode[4] == '-' && isdigit(zipCode[5]) && isdigit(zipCode[6]) && isdigit(zipCode[7])) {
        return 0;
    }
    puts("Invalid postal code format. Please enter a new one.");
    return -1;
}

int searchCompanyNif(Companies companies, int number) {
    int i;
    for (i = 0; i < companies.companiesCounter; i++) {
        if (companies.company[i].nif == number) {
            return i;
        }
    }
    return -1;
}

int searchCompanyName(Companies companies, char *name) {
    int i;
    for (i = 0; i < companies.companiesCounter; i++) {
        if (strcmp(name, companies.company[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

int searchCompanyLocation(Companies companies, char *location) {
    int i;
    for (i = 0; i < companies.companiesCounter; i++) {
        if (strcmp(location, companies.company[i].location) == 0) {
            return i;
        }
    }
    return -1;
}

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

void printBranches(BranchActivity branch) {
    int i;
    for (i = 0; i < branch.branchCounter; i++) {
        printf("%d- %s\n", i , branch.branch[i].branch);
    }
}

int editBranch(BranchActivity *branch) {
    int option;
    
    do {
        puts("Chose the Branch you want to edit");
        printBranches(*branch);
        scanf("%d",&option);
    
    } while ( option < 0 || option > branch->branchCounter - 1);
    
    return option;
}



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

float calculateAverageRating(Company *company) {
    if (company->classificationCounter > 0) {
        return (float) company->classification / company->classificationCounter;
    }
    return 0; 
}

void listCommentsTitle(Company company) {
    int i;
    
    for (i = 0; i < company.commentsCounter; i++) {
        printf("%d - %s\n", i, company.comments[i].title);
    }
}

void deleteCommentsData(Company *company, int index) {
    strcpy(company->comments[index].email, "");
    strcpy(company->comments[index].text, "");
    strcpy(company->comments[index].title, "");
    strcpy(company->comments[index].username, "");
    company->comments[index].status = INATIVO;
}

int removeBranch(BranchActivity *branch) {
    int option;
    
    do {
        puts("Choose the Branch you want to delete");
        printBranches(*branch);
        scanf("%d", &option);
    
    } while (option < 0 || option > branch->branchCounter - 1);
    
    return option;
}

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

void freeCompanies(Companies *companies, BranchActivity *branch) {
    if (companies->company) {
        free(companies->company);
        companies->company = NULL;
    }

    if (branch->branch) {
        free(branch->branch);
        branch->branch = NULL;
    }

    companies = NULL;
    branch = NULL;
}

void listComments(Company company) {
    for (int i = 0; i < company.commentsCounter; i++) {
        puts("----------------------------");
        printf("\nUsername: %s\n", company.comments[i].username);
        printf("Title: %s\n", company.comments[i].title);
        printf("Comment: %s\n", company.comments[i].text);
        puts("----------------------------");
    }
}

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




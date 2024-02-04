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
    if (strlen(zipCode) == 8 && isdigit((unsigned char) zipCode[0]) && isdigit((unsigned char) zipCode[1]) && isdigit((unsigned char) zipCode[2]) && isdigit((unsigned char) zipCode[3]) && (unsigned char) zipCode[4] == '-' && isdigit((unsigned char) zipCode[5]) && isdigit((unsigned char) zipCode[6]) && isdigit((unsigned char) zipCode[7])) {
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
        printf("Nif: %d\n", company.nif);
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
    }
    
    for (int i = 0; i < branch->branchCounter; i++) {
        fwrite(&branch->branch[i], sizeof(Branch), 1, fp);
    }
    
    for (int i = 0; i < companies->companiesCounter; i++) {
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
        companies->company[i].comments = (Comment *) malloc(companies->company[i].maxComments * sizeof(Comment));
    }
    
    for (int i = 0; i < branch->branchCounter; i++) {
        fread(&branch->branch[i], sizeof(Branch), 1, fp);
        
    }
    
    for (int i = 0; i < companies->companiesCounter; i++) {
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

/**
 * @brief Create a new branch of activity.
 * @param branch The structure holding information about branch activities.
 */
void createActivity(BranchActivity *branch) {
    if (branch->branchCounter == branch->maxBranch) {
        branch->branch = (Branch *) realloc(branch->branch, branch->maxBranch * 2 * sizeof (Branch));

        if (branch->branch != NULL) {
            branch->maxBranch *= 2;
        }
    }

    if (branch->branch != NULL) {
        puts("Enter the new branch name: ");
        cleanInputBuffer();
        if (fgets(branch->branch[branch->branchCounter].branch, MAX_BRANCH, stdin) == NULL) {
            puts("Invalid input. New branch creation failed.");
            cleanInputBuffer();
            branch->branchCounter--;
        } else {
            for (int i = 0; i < branch->branchCounter - 1; i++) {
                if (strcasecmp(branch->branch[i].branch, branch->branch[branch->branchCounter - 1].branch) == 0) {
                    puts(ERROR_BRANCH_ALREADY_EXIST);
                    return;
                }
            }
            branch->branch[branch->branchCounter].branch[strcspn(branch->branch[branch->branchCounter].branch, "\n")] = '\0';

            puts("New branch created successfully!\n");
            branch->branch[branch->branchCounter].status = ATIVO;
            branch->branchCounter++;
        }
    } else {
        puts("Memory reallocation failed. Unable to create a new branch.\n");
        branch->branchCounter--;
    }
}

/**
 * @brief Insert a new company into the system.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @return Returns the index of the newly inserted company.
 */
int insertCompany(Companies *companies, BranchActivity *branch) {
    int verification, nif = getNum(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    char tmpBranch[MAX_BRANCH];

    Company *company = &companies->company[companies->companiesCounter];

    if (companies->companiesCounter == companies->maxCompanies) {
        Company *pCompany;
        pCompany = (Company *) realloc(companies->company, companies->maxCompanies * 2 * sizeof (Company));

        if (pCompany != NULL) {
            companies->maxCompanies *= 2;
            companies->company = pCompany;
        }
    }

    if (branch->branchCounter != 0) {
        if (searchCompanyNif(*companies, nif) == -1) {
            company->nif = nif;
            readString(company->name, MAX_NAME, MSG_GET_NAME);
            readString(company->adress, MAX_ADRESS, MSG_GET_ADRESS);
            do {
                readString(company->postalCode, MAX_POSTAL_CODE, MSG_GET_POSTAL_CODE);

                size_t len = strlen(company->postalCode);

                if (len > 0 && company->postalCode[len - 1] == '\n') {
                    company->postalCode[len - 1] = '\0';
                }

                verification = postalCodeVerification(company->postalCode);
            } while (verification == -1);

            readString(company->location, MAX_LOCATION, MSG_GET_LOCATION);
            selectBranch(branch, tmpBranch);
            strcpy(company->branch, tmpBranch);
            company->companyCategory = getNum(MIN_CATEGORY, MAX_CATEGORY, MSG_GET_CATEGORY);
            company->status = ATIVO;

            company->maxComments = 5;
            company->commentsCounter = 0;
            company->comments = (Comment *) malloc(company->maxComments * sizeof (Comment));

            company->classificationCounter = 0;
            company->classification = 0;


            return companies->companiesCounter++;
        }
    } else {
        puts(ERROR_CREATE_BRANCH);
        return -2;
    }
    return -1;
}

/**
 * @brief Wrapper function to insert a new company into the system.
 * @param company The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 */
void insertCompanies(Companies *company, BranchActivity *branch) {
    if (insertCompany(company, branch) == -1) {
        puts(ERROR_COMPANY_ALREADY_EXIST);
        return;
    }
}

/**
 * @brief Update company information based on NIF.
 * @param company The structure holding information about a specific company.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompany(Company *company, BranchActivity *branch) {
    int verification, nif = getNum(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    char tmpBranch[MAX_BRANCH];

    company->nif = nif;
    readString((*company).name, MAX_NAME, MSG_GET_NAME);
    readString((*company).adress, MAX_ADRESS, MSG_GET_ADRESS);
    do {
        readString(company->postalCode, MAX_POSTAL_CODE, MSG_GET_POSTAL_CODE);

        size_t len = strlen(company->postalCode);

        if (len > 0 && company->postalCode[len - 1] == '\n') {
            company->postalCode[len - 1] = '\0';
        }

        verification = postalCodeVerification(company->postalCode);
    } while (verification == -1);

    readString((*company).location, MAX_LOCATION, MSG_GET_LOCATION);
    selectBranch(branch, tmpBranch);
    strcpy((*company).branch, tmpBranch);
    (*company).companyCategory = getNum(MIN_CATEGORY, MAX_CATEGORY, MSG_GET_CATEGORY);
    (*company).status = getNum(MIN_STATUS, MAX_STATUS, MSG_GET_STATUS);
}

/**
 * @brief Update company information based on NIF.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByNif(Companies *companies, BranchActivity *branch) {
    int value = searchCompanyNif(*companies, getNum(MIN_NIF, MAX_NIF, MSG_GET_NIF));

    if (value != -1) {
        updateCompany(&(*companies).company[value], branch);
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }
}

/**
 * @brief Update company information based on name.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByName(Companies *companies, BranchActivity *branch) {
    char tempName[MAX_NAME];

    puts(MSG_GET_NAME);
    if (scanf("%s", tempName) == 1) {
        unsigned int len = strlen(tempName) - 1;
        if (tempName[len] == '\n') {
            tempName[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }

    int value = searchCompanyName(*companies, tempName);

    if (value != -1) {
        updateCompany(&(*companies).company[value], branch);
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }

}

/**
 * @brief Update company information based on location.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByLocation(Companies *companies, BranchActivity *branch) {
    char tempLocation[MAX_NAME];

    puts(MSG_GET_NAME);
    if (scanf("%s", tempLocation) == 1) {
        unsigned int len = strlen(tempLocation) - 1;
        if (tempLocation[len] == '\n') {
            tempLocation[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }

    int value = searchCompanyLocation(*companies, tempLocation);

    if (value != -1) {
        updateCompany(&(*companies).company[value], branch);
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }
}

/**
 * @brief Update branch information.
 * @param branch The structure holding information about branch activities.
 */
void updateBranches(Companies *companies, BranchActivity *branch) {
    printf("%d", companies->company[0].status);
    printf("%d", branch->branch[0].status);
    if (branch->branchCounter > 0) {
        int value = editBranch(branch);
        
        char tmpBranch[MAX_BRANCH];
        strcpy(tmpBranch, branch->branch[value].branch);
        
        for (int i = 0; i < companies->companiesCounter; i++) {
            if (strcasecmp(companies->company[i].branch, tmpBranch) == 0) {
                cleanInputBuffer();  
                strcpy(companies->company[i].branch, tmpBranch);
            }
        }
        
        readString(branch->branch[value].branch, MAX_BRANCH, MSG_CREATE_BRANCH);
        branch->branch[value].status = ATIVO;
    } else {
        puts("There are no branches of activity available for editing. Please create one first.");
    }
}


/**
 * @brief Delete a company based on NIF.
 * @param companies The structure holding information about companies.
 */
void deleteCompanyNif(Companies *companies) {
    int i, index = searchCompanyNif(*companies, getNum(MIN_NIF, MAX_NIF, MSG_GET_NIF));

    if (index != -1) {
        if (companies->company[index].commentsCounter == 0) {
            for (i = index; i < companies->companiesCounter - 1; i++) {
                companies->company[i] = companies->company[i + 1];
            }

            deleteCompanyData(&companies->company[i]);

            companies->companiesCounter--;
        } else {
            companies->company[index].status = INATIVO;
        }
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }
}

/**
 * @brief Delete a company based on name.
 * @param companies The structure holding information about companies.
 */
void deleteCompanyName(Companies *companies) {
    char tmpName[MAX_NAME];
    int index, i;

    puts(MSG_GET_NAME);
    if (scanf("%s", tmpName) == 1) {
        unsigned int len = strlen(tmpName) - 1;
        if (tmpName[len] == '\n') {
            tmpName[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }

    index = searchCompanyName(*companies, tmpName);

    if (index != -1) {
        if (companies->company[index].commentsCounter == 0) {
            for (i = index; i < companies->companiesCounter - 1; i++) {
                companies->company[i] = companies->company[i + 1];
            }

            deleteCompanyData(&companies->company[i]);

            companies->companiesCounter--;
        } else {
            companies->company[index].status = INATIVO;
        }
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }
}

/**
 * @brief Delete a company based on location.
 * @param companies The structure holding information about companies.
 */
void deleteCompanyLocation(Companies *companies) {
    char tempLocation[MAX_NAME];
    int index, i;

    puts(MSG_GET_LOCATION);
    if (scanf("%s", tempLocation) == 1) {
        unsigned int len = strlen(tempLocation) - 1;
        if (tempLocation[len] == '\n') {
            tempLocation[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }

    index = searchCompanyLocation(*companies, tempLocation);

    if (index != -1) {
        if (companies->company[index].commentsCounter == 0) {
            for (i = index; i < companies->companiesCounter - 1; i++) {
                companies->company[i] = companies->company[i + 1];
            }

            deleteCompanyData(&companies->company[i]);

            companies->companiesCounter--;
        } else {
            companies->company[index].status = INATIVO;
        }
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }
}

/**
 * @brief Manage comments for a specific company based on NIF.
 * @param companies The structure holding information about companies.
 */
void manageCommentsNif(Companies *companies) {
    long long value = searchCompanyNif(*companies, getNum(MIN_NIF, MAX_NIF, MSG_GET_NIF));
    int option1, option2, i;

    if (value != -1) {
        if (companies->company[value].commentsCounter > 0) {
            puts("Select the title of the comment to hide/delete: ");
            listCommentsTitle(companies->company[value]);
            scanf("%d", &option1);

            puts("Choose what you want to do: ");
            puts("0- Delete Comment");
            puts("1- Hide Comment");
            scanf("%d", &option2);

            switch (option2) {
                case 0:
                    if (option1 >= 0 && option1 < companies->company[value].commentsCounter) {
                        for (i = option1; i < companies->company[value].commentsCounter - 1; i++) {
                            companies->company[value].comments[i] = companies->company[value].comments[i + 1];
                        }

                        deleteCommentsData(&companies->company[value], companies->company[value].commentsCounter - 1);

                        companies->company[value].commentsCounter--;
                    } else {
                        puts("Invalid comment index.");
                    }
                    break;
                case 1:
                    if (option1 >= 0 && option1 < companies->company[value].commentsCounter) {
                        companies->company[value].comments[option1].status = INATIVO;
                    } else {
                        puts("Invalid comment index.");
                    }
                    break;
            }
        } else {
            puts("There is no comments to hide/delete.");
        }
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Manage comments for a specific company based on name.
 * @param companies The structure holding information about companies.
 */
void manageCommetsName(Companies *companies) {
    char tempName[MAX_NAME];
    int option1, option2, i;

    cleanInputBuffer();
    readString(tempName, MAX_NAME, MSG_GET_NAME);

    int value = searchCompanyName(*companies, tempName);

    if (value != -1) {
        if (companies->company[value].commentsCounter > 0) {
            puts("Select the title of the comment to hide/delete: ");
            listCommentsTitle(companies->company[value]);
            scanf("%d", &option1);

            puts("Choose what you want to do: ");
            puts("0- Delete Comment");
            puts("1- Hide Comment");
            scanf("%d", &option2);

            switch (option2) {
                case 0:
                    if (option1 >= 0 && option1 < companies->company[value].commentsCounter) {
                        for (i = option1; i < companies->company[value].commentsCounter - 1; i++) {
                            companies->company[value].comments[i] = companies->company[value].comments[i + 1];
                        }

                        deleteCommentsData(&companies->company[value], companies->company[value].commentsCounter - 1);

                        companies->company[value].commentsCounter--;
                    } else {
                        puts("Invalid comment index.");
                    }
                    break;
                case 1:
                    if (option1 >= 0 && option1 < companies->company[value].commentsCounter) {
                        companies->company[value].comments[option1].status = INATIVO;
                    } else {
                        puts("Invalid comment index.");
                    }
                    break;
            }
        } else {
            puts("There is no comments to hide/delete.");
        }
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Manage comments for a specific company based on location.
 * @param companies The structure holding information about companies.
 */
void manageCommentsLocation(Companies *companies) {
    char tempLocation[MAX_NAME];
    int option1, option2, i;

    cleanInputBuffer();
    readString(tempLocation, MAX_LOCATION, MSG_GET_LOCATION);

    int value = searchCompanyLocation(*companies, tempLocation);

    if (value != -1) {
        if (companies->company[value].commentsCounter > 0) {
            puts("Select the title of the comment to hide/delete: ");
            listCommentsTitle(companies->company[value]);
            scanf("%d", &option1);

            puts("Choose what you want to do: ");
            puts("0- Delete Comment");
            puts("1- Hide Comment");
            scanf("%d", &option2);

            switch (option2) {
                case 0:
                    if (option1 >= 0 && option1 < companies->company[value].commentsCounter) {
                        for (i = option1; i < companies->company[value].commentsCounter - 1; i++) {
                            companies->company[value].comments[i] = companies->company[value].comments[i + 1];
                        }

                        deleteCommentsData(&companies->company[value], companies->company[value].commentsCounter - 1);

                        companies->company[value].commentsCounter--;
                    } else {
                        puts("Invalid comment index.");
                    }
                    break;
                case 1:
                    if (option1 >= 0 && option1 < companies->company[value].commentsCounter) {
                        companies->company[value].comments[option1].status = INATIVO;
                    } else {
                        puts("Invalid comment index.");
                    }
                    break;
            }
        } else {
            puts("There is no comments to hide/delete.");
        }
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Delete a branch of activity.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 */
void deleteBranch(Companies *companies, BranchActivity *branch) {
    if (branch->branchCounter > 0) {
        int value = removeBranch(branch);

        for (int i = 0; i < companies->companiesCounter; i++) {
            if (strcmp(companies->company[i].branch, branch->branch[value].branch) == 0) {
                puts("You cannot delete this branch of activity. You can only change the branch status to INACTIVE.");
                branch->branch[value].status = INATIVO;
                return;
            }
        }

        for (int j = value; j < branch->branchCounter - 1; j++) {
            strcpy(branch->branch[j].branch, branch->branch[j + 1].branch);
            branch->branch[j].status = branch->branch[j + 1].status;
        }

        branch->branchCounter--;
    } else {
        puts("There are no branches of activity available for removal. Please create one first.");
    }
}

/**
 * @brief List companies with higher average ratings.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void listHigherCompanies(Companies *companies, BranchActivity *branchActivity) {
    if (companies->companiesCounter > 0) {
        int i, j, index;

        for (i = 0; i < companies->companiesCounter; i++) {
            for (j = 0; j < branchActivity->branchCounter; j++) {
                if (strcmp(companies->company[i].branch, branchActivity->branch[j].branch) == 0) {
                    index = j;
                }
                if (calculateAverageRating(&companies->company[i]) > 4.5) {
                    printCompany(companies->company[i], branchActivity->branch[index]);
                    printf("Average rating: %.2f\n", calculateAverageRating(&companies->company[i]));
                    listComments(companies->company[i]);
                }
            }
        }

    } else {
        puts(ERROR_EMPY_LIST);
    }
}

/**
 * @brief List the most searched companies.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 * @param sizeOfTop The number of top companies to list.
 */
void listMostCompanies(Companies companies, BranchActivity branchActivity, int sizeOfTop) {
    int index;
    int size = companies.companiesCounter >= sizeOfTop ? sizeOfTop : companies.companiesCounter;
    int array[size];
    if (companies.companiesCounter > 0) {
        mostSearchedCompanies(companies, size, array);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < branchActivity.branchCounter; j++) {
                if (strcmp(companies.company[i].branch, branchActivity.branch[j].branch) == 0) {
                    index = j;
                    printCompany(companies.company[i], branchActivity.branch[index]);
                    printf("Average Rating: %.2f\n", calculateAverageRating(&companies.company[i]));
                    listComments(companies.company[array[i]]);
                }
            }
        }
    }
}


/**
 * @brief Display company information based on NIF.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void companyNif(Companies companies, BranchActivity branchActivity) {
    int index, i; 
    long long value = searchCompanyNif(companies, getNum(MIN_NIF, MAX_NIF, MSG_GET_NIF));
 
    for (i = 0; i < branchActivity.branchCounter; i++) {
        if (strcmp(companies.company[value].branch, branchActivity.branch[i].branch) == 0) {
            index = i;
        }
    }
    
    if (value != -1) {
        printCompany(companies.company[value], branchActivity.branch[index]);
        printf("Average rating: %.2f\n", (float) companies.company[value].classification);
        listComments(companies.company[value]);
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}


/**
 * @brief Display company information based on name.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void companyName(Companies companies, BranchActivity branchActivity) {
    int index, i;
    char tempName[MAX_NAME];

    cleanInputBuffer();
    readString(tempName, MAX_NAME, MSG_GET_NAME);

    int value = searchCompanyName(companies, tempName);
    
    for (i = 0; i < branchActivity.branchCounter; i++) {
        if (strcmp(companies.company[value].branch, branchActivity.branch[i].branch) == 0) {
            index = i;
        }
    }

    if (value != -1) {
        printCompany(companies.company[value], branchActivity.branch[index]);
        printf("Average rating: %.2f\n",(float) companies.company[value].classification);
        listComments(companies.company[value]);
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Display company information based on location.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void companyLocation(Companies companies, BranchActivity branchActivity) {
    int index, i;
    char tempLocation[MAX_NAME];

    cleanInputBuffer();
    readString(tempLocation, MAX_LOCATION, MSG_GET_LOCATION);

    int value = searchCompanyLocation(companies, tempLocation);

    for (i = 0; i < branchActivity.branchCounter; i++) {
        if (strcmp(companies.company[value].branch, branchActivity.branch[i].branch) == 0) {
            index = i;
        }
    }
    
    if (value != -1) {
        printCompany(companies.company[value], branchActivity.branch[index]);
        printf("Average rating: %.2f\n", (float) companies.company[value].classification);
        listComments(companies.company[value]);
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Select a branch of activity from the available options.
 * @param branch The structure holding information about branch activities.
 * @param selectedBranch Pointer to store the selected branch.
 */
void selectBranch(BranchActivity *branch, char *selectedBranch) {
    int option;
    
    do {
        puts("Select one of the following branches of activity:");
        printBranches(*branch);
        printf("Choose a branch [0-%d]: ", branch->branchCounter - 1);
        scanf("%d", &option);
    
    if (branch->branch != NULL && option >= 0 && option < branch->branchCounter) {
            strcpy(selectedBranch, branch->branch[option].branch);
        } else {
            puts("Invalid option. Please try again.");
        }
    
    } while (option < 0 || option >= branch->branchCounter);
}

/**
 * @brief Create a new comment for a company based on NIF.
 * @param companies The structure holding information about companies.
 */
void createCommentNif(Companies *companies) {
    int value = getNum(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    int index = searchCompanyNif(*companies, value);
    Comment *pComment = &companies->company[index].comments;
    
    if (index != -1) {
        if (companies->company[index].commentsCounter == companies->company[index].maxComments) {
            pComment = (Comment *) realloc(companies->company[index].comments, companies->company[index].maxComments * 2 * sizeof(Comment));
        
            if (pComment != NULL ) {
                companies->company[index].maxComments *= 2;
                companies->company[index].comments = pComment;
            }
        }
      
        do {
            readString(pComment->email, MAX_EMAIL, MSG_GET_EMAIL);
        } while (emailVerification(&companies->company[index].comments[companies->company[index].commentsCounter]) == -1);
        
        readString(pComment->username, MAX_USERNAME, MSG_GET_USER);
        readString(companies->company[index].comments[companies->company[index].commentsCounter].title, MAX_TITLE, MSG_GET_TITLE);
        readString(companies->company[index].comments[companies->company[index].commentsCounter].text, MAX_TEXT, MSG_GET_COMMENT);
        companies->company[index].comments[companies->company[index].commentsCounter].status = ATIVO;
        
        companies->company[index].commentsCounter++;

       
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Create a new comment for a company based on name.
 * @param companies The structure holding information about companies.
 */
void createCommentName(Companies *companies) {
    char tmpName[MAX_NAME];
    int index;
    
    cleanInputBuffer();
    
    readString(tmpName, MAX_NAME, MSG_GET_NAME);
    
    index = searchCompanyName(*companies, tmpName);
    
    Company *pComment = &companies->company[index].comments;
    
    if (index != -1) {
        if (companies->company[index].commentsCounter == companies->company[index].maxComments) {
            pComment = (Comment *) realloc(companies->company[index].comments, companies->company[index].maxComments * 2 * sizeof(Comment));
        
            if (pComment != NULL ) {
                companies->company[index].maxComments *= 2;
                companies->company[index].comments = pComment;
            }
        }
                
        do {
            readString(companies->company[index].comments[companies->company[index].commentsCounter].email, MAX_EMAIL, MSG_GET_EMAIL);
        } while (emailVerification(&companies->company[index].comments[companies->company[index].commentsCounter]) == -1);
        
        readString(companies->company[index].comments[companies->company[index].commentsCounter].username, MAX_USERNAME, MSG_GET_USER);
        readString(companies->company[index].comments[companies->company[index].commentsCounter].title, MAX_TITLE, MSG_GET_TITLE);
        readString(companies->company[index].comments[companies->company[index].commentsCounter].text, MAX_TEXT, MSG_GET_COMMENT);
        companies->company[index].comments[companies->company[index].commentsCounter].status = ATIVO;
        
        companies->company[index].commentsCounter++;
        
        
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Create a new comment for a company based on location.
 * @param companies The structure holding information about companies.
 */
void createCommentLocation(Companies *companies) {
    char tempLocation[MAX_NAME];
    int index;

    puts(MSG_GET_NAME);
    if (scanf("%s", tempLocation) != NULL) {
        unsigned int len = strlen(tempLocation) - 1;
        if (tempLocation[len] == '\n') {
            tempLocation[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
    
    index = searchCompanyLocation(*companies, tempLocation);
    
    Company *pComment = &companies->company[index].comments;
    
    if (index != -1) {
        if (companies->company[index].commentsCounter == companies->company[index].maxComments) {
            pComment = (Comment *) realloc(companies->company[index].comments, companies->company[index].maxComments * 2 * sizeof(Comment));
        
            if (pComment != NULL ) {
                companies->company[index].maxComments *= 2;
                companies->company[index].comments = pComment;
            }
        }
        
        do {
            readString(companies->company[index].comments[companies->company[index].commentsCounter].email, MAX_EMAIL, MSG_GET_EMAIL);
        } while (emailVerification(&companies->company[index].comments[companies->company[index].commentsCounter]) == -1);
        
        readString(companies->company[index].comments[companies->company[index].commentsCounter].username, MAX_USERNAME, MSG_GET_USER);
        readString(companies->company[index].comments[companies->company[index].commentsCounter].title, MAX_TITLE, MSG_GET_TITLE);
        readString(companies->company[index].comments[companies->company[index].commentsCounter].text, MAX_TEXT, MSG_GET_COMMENT);
        companies->company[index].comments[companies->company[index].commentsCounter].status = ATIVO;
        
        companies->company[index].commentsCounter++;
        
        
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Create a new classification for a company based on NIF.
 * @param companies The structure holding information about companies.
 */
void createClassificationNif(Companies *companies) {
    int nif = getNum(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    int index = searchCompanyNif(*companies, nif);
           
    if (index != -1) {     
        companies->company[index].classification += getNum(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
        companies->company[index].classificationCounter++;
    } else {
       puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Create a new classification for a company based on name.
 * @param companies The structure holding information about companies.
 */
void createClassificationName(Companies *companies) {
    char tmpName[MAX_NAME];
    int index;

    puts(MSG_GET_NAME);
    if (scanf("%s", tmpName) != NULL) {
        unsigned int len = strlen(tmpName) - 1;
        if (tmpName[len] == '\n') {
            tmpName[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
    
    index = searchCompanyName(*companies, tmpName);
    
   
    if (index != -1) {
        companies->company[index].classification = getNum(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
        companies->company[index].classificationCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

/**
 * @brief Create a new classification for a company based on location.
 * @param companies The structure holding information about companies.
 */
void createClassificationLocation(Companies *companies) {
    char tempLocation[MAX_NAME];
    int index;

    puts(MSG_GET_NAME);
    if (scanf("%s", tempLocation) != NULL) {
        unsigned int len = strlen(tempLocation) - 1;
        if (tempLocation[len] == '\n') {
            tempLocation[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
    
    index = searchCompanyLocation(*companies, tempLocation);
    
    
    if (index != -1) {
        companies->company[index].classification = getNum(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
    companies->company[index].classificationCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}




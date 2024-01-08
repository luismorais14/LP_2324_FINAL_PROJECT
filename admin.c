#include "companies.h"
#include "input.h"
#include "tools.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "user.h"
#include <ctype.h>

void companyNif(Companies companies, BranchActivity branchActivity) {
    int index, i; 
    long long value = searchCompanyNif(companies, getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF));
 
    for (i = 0; i < branchActivity.branchCounter; i++) {
        if (strcmp(companies.company[value].branch, branchActivity.branch[i].branch) == 0) {
            index = i;
        }
    }
    
    if (value != -1) {
        printCompany(companies.company[value], branchActivity.branch[index]);
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

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
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

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
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

void createActivity(BranchActivity *branch) {
    if (branch->branchCounter == branch->maxBranch) {
        branch->branch = (Branch *) realloc(branch->branch, branch->branchCounter * sizeof(Branch)); 
    }

    if (branch->branch != NULL) {
        puts("Enter the new branch name: ");
        cleanInputBuffer();
        if (fgets(branch->branch[branch->branchCounter].branch, MAX_BRANCH, stdin) == NULL) {
            puts("Invalid input. New branch creation failed.\n");
            cleanInputBuffer();
            branch->branchCounter--;
        } else {
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

int insertCompany(Companies *companies, BranchActivity *branch) {
    int verification, nif = getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    char tmpBranch[MAX_BRANCH];

    Company *company = &companies->company[companies->companiesCounter];

    if (companies->companiesCounter == companies->maxCompanies) {
        Company *pCompany;
        pCompany = (Company *) realloc(companies->company, companies->maxCompanies * 2 * sizeof(Company));

        if (pCompany != NULL ) {
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
            company->companyCategory = getInt(MIN_CATEGORY, MAX_CATEGORY, MSG_GET_CATEGORY);
            company->status = ATIVO;
            
            company->maxComments = 5;
            company->commentsCounter = 0;
            company->comments = (Comment *) malloc(company->maxComments * sizeof(Comment));
            
            company->classificationCounter = 0;
            

            return companies->companiesCounter++;
        }
    } else {
        puts(ERROR_CREATE_BRANCH);
        return;
    }
    return -1;
}

void insertCompanies(Companies *company, BranchActivity *branch) {
        if (insertCompany(company, branch) == -1) {
            puts(ERROR_COMPANY_ALREADY_EXIST);
            return;
        }
}  

void updateCompany(Company *company, BranchActivity *branch, char *filename) {
    int verification, nif = getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF);
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
    (*company).companyCategory = getInt(MIN_CATEGORY, MAX_CATEGORY, MSG_GET_CATEGORY);
    (*company).status = getInt(MIN_STATUS, MAX_STATUS, MSG_GET_STATUS);
}

void updateCompaniesByNif(Companies *companies, BranchActivity *branch, char *filename) {    
    int  value = searchCompanyNif(*companies, getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF));
    
    if (value != -1){
        updateCompany(&(*companies).company[value], branch, filename);
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }
}

void updateCompaniesByName(Companies *companies, BranchActivity *branch, char *filename) {    
    char tempName[MAX_NAME];

    puts(MSG_GET_NAME);
    if (scanf("%s", tempName) != NULL) {
        unsigned int len = strlen(tempName) - 1;
        if (tempName[len] == '\n') {
            tempName[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
    
    int value = searchCompanyName(*companies, tempName);
    
    if (value != -1){
        updateCompany(&(*companies).company[value], branch, filename);
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }
    
}

void updateCompaniesByLocation(Companies *companies, BranchActivity *branch, char *filename) {    
    char tempLocation[MAX_NAME];

    puts(MSG_GET_NAME);
    if (scanf("%s", tempLocation) != NULL) {
        unsigned int len = strlen(tempLocation) - 1;
        if (tempLocation[len] == '\n') {
            tempLocation[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }

    int value = searchCompanyLocation(*companies, tempLocation);
    
    if (value != -1){
        updateCompany(&(*companies).company[value], branch, filename);
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
        return;
    }
}

void updateBranches(BranchActivity *branch) {
    if (branch->branchCounter > 0) {
        int value = editBranch(branch);
    
        cleanInputBuffer();
        readString(&(*branch).branch[value] ,MAX_BRANCH , MSG_CREATE_BRANCH);
    } else {
        puts("There are no branches of activity available for editing. Please create one first.");
    }
}

void deleteCompanyNif(Companies *companies) {
    int i, index = searchCompanyNif(*companies, getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF));

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

void deleteCompanyName(Companies *companies) {
    char tmpName[MAX_NAME];
    int index, i;
    
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

void deleteCompanyLocation(Companies *companies) {
    char tempLocation[MAX_NAME];
    int index, i;

    puts(MSG_GET_LOCATION);
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

void manageCommentsNif(Companies *companies) {
    long long value = searchCompanyNif(*companies, getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF));
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

void manageCommetsName(Companies *companies) {
    char tempName[MAX_NAME];
    int option1, option2, i;

    puts(MSG_GET_NAME);
    if (scanf("%s", tempName) != NULL) {
        unsigned int len = strlen(tempName) - 1;
        if (tempName[len] == '\n') {
            tempName[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }

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

void manageCommentsLocation(Companies *companies) {
    char tempLocation[MAX_NAME];
    int option1, option2, i;

    puts(MSG_GET_NAME);
    if (scanf("%s", tempLocation) != NULL) {
        unsigned int len = strlen(tempLocation) - 1;
        if (tempLocation[len] == '\n') {
            tempLocation[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }

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
                }
            }
        }

    } else {
        puts(ERROR_EMPY_LIST);
    }
}

void listMostCompanies(Companies companies, BranchActivity branchActivity, int sizeOfTop) {
    int index;
    if (companies.companiesCounter > 0) {
        int size = companies.companiesCounter >= sizeOfTop ? sizeOfTop : companies.companiesCounter;
        int array[size];

        mostSearchedCompanies(companies, size, array);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < branchActivity.branchCounter; j++) {
                if (strcmp(companies.company[i].branch, branchActivity.branch[j].branch) == 0) {
                    index = j;

                    printCompany(companies.company[i], branchActivity.branch[j]);
                    printf("Average Rating: %.2f\n", calculateAverageRating(&companies.company[i]));
                    listComments(companies.company[array[i]]);
                }
            }
        }
    }
}
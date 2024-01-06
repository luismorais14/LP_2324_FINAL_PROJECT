#include "companies.h"
#include "input.h"
#include "tools.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


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
    } else {
        puts("This company is inactive.");
    }
}

void companyNif(Companies companies, Branch branch) {
    long long value = searchCompanyNif(companies, getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF));

    if (value != -1) {
        printCompany(companies.company[value], branch);
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

void companyName(Companies companies, Branch branch) {
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

    int value = searchCompanyName(companies, tempName);

    if (value != -1) {
        printCompany(companies.company[value], branch);
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

void companyLocation(Companies companies, Branch branch) {
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

    int value = searchCompanyLocation(companies, tempLocation);

    if (value != -1) {
        printCompany(companies.company[value], branch);
        companies.company[value].searchCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
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

void createActivity(BranchActivity *branch) {
    if (branch->branchCounter == branch->maxBranch) {
        branch->branch = (Branch *) realloc(branch->branch, branch->branchCounter * sizeof(Branch)); 
    }

    if (branch->branch != NULL) {
        puts("Enter the new branch name: ");
        if (scanf("%s", branch->branch[branch->branchCounter].branch) != 1) {
            puts("Invalid input. New branch creation failed.\n");
            cleanInputBuffer();
            branch->branchCounter--;
        } else {
            puts("New branch created successfully!\n");
            branch->branch[branch->branchCounter].status = ATIVO;
            branch->branchCounter++;
        }
    } else {
        puts("Memory reallocation failed. Unable to create a new branch.\n");
        branch->branchCounter--;
    }
}

int insertCompany(Companies *companies, BranchActivity *branch, char *filename) {
    int nif = getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF);
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
            readString(company->postalCode, MAX_POSTAL_CODE, MSG_GET_POSTAL_CODE);
            readString(company->location, MAX_LOCATION, MSG_GET_LOCATION);
            selectBranch(branch, tmpBranch);
            strcpy(company->branch, tmpBranch);
            company->companyCategory = getInt(MIN_CATEGORY, MAX_CATEGORY, MSG_GET_CATEGORY);
            company->status = getInt(MIN_STATUS, MAX_STATUS, MSG_GET_STATUS);

            return companies->companiesCounter++;
        }
    } else {
        puts(ERROR_CREATE_BRANCH);
        return;
    }
    return -1;
}

void insertCompanies(Companies *company, BranchActivity *branch, char *filename) {
        if (insertCompany(company, branch, filename) == -1) {
            puts(ERROR_COMPANY_ALREADY_EXIST);
            return;
        }
}  

void updateCompany(Company *company, BranchActivity *branch, char *filename) {
    int nif = getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    char tmpBranch[MAX_BRANCH];
    
    company->nif = nif;
    readString((*company).name, MAX_NAME, MSG_GET_NAME);
    readString((*company).adress, MAX_ADRESS, MSG_GET_ADRESS);
    readString((*company).postalCode, MAX_POSTAL_CODE, MSG_GET_POSTAL_CODE);
    readString((*company).location, MAX_LOCATION, MSG_GET_LOCATION);
    selectBranch(*branch, tmpBranch);
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

int editBranch(BranchActivity *branch) {
    int option;
    
    do {
        puts("Chose the Branch you want to edit");
        printBranches(*branch);
        scanf("%d",&option);
    
    } while ( option < 0 || option > branch->branchCounter - 1);
    
    return option;
}

void updateBranch(Branch *branch) {
    cleanInputBuffer();
    readString(branch->branch ,MAX_BRANCH , MSG_CREATE_BRANCH);
}

void updateBranches(BranchActivity *branch ) {
    if (branch->branchCounter > 0) {
        int value = editBranch(branch);
    
        updateBranch(&(*branch).branch[value]);
    } else {
        puts("There are no branches of activity available for editing. Please create one first.");
    }
}

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

void deleteCompanyNif(Companies *companies, char *filename) {
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

void deleteCompanyName(Companies *companies, char *filename) {
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

void deleteCompanyLocation(Companies *companies, char *filename) {
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

void createCommentNif(Companies *companies) {
    int value = getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    int index = searchCompanyNif(*companies, value);
    
    Company *pComment = &companies->company[index].comments;
    
    if (companies->company->commentsCounter == companies->company->maxComments) {
        pComment = (Comment *) realloc(companies->company[index].comments, companies->company[index].maxComments * 2 * sizeof(Comment));
    }
    
    if (pComment != NULL ) {
            companies->company->maxComments *= 2;
            companies->company->comments = pComment;
        }
    
    
    if (index != -1) {
        readString(companies->company[index].comments[companies->company->commentsCounter].email, MAX_EMAIL, MSG_GET_EMAIL);
        readString(companies->company[index].comments[companies->company->commentsCounter].username, MAX_USERNAME, MSG_GET_USER);
        readString(companies->company[index].comments[companies->company->commentsCounter].title, MAX_TITLE, MSG_GET_TITLE);
        readString(companies->company[index].comments[companies->company->commentsCounter].text, MAX_TEXT, MSG_GET_COMMENT);
        companies->company[index].comments[companies->company->commentsCounter].status = ATIVO;
    
        companies->company->commentsCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

void createCommentName(Companies *companies) {
    char tmpName[MAX_NAME];
    int index;
    
    cleanInputBuffer();
    
    readString(tmpName, MAX_NAME, MSG_GET_NAME);
    
    index = searchCompanyName(*companies, tmpName);
    
    Company *pComment = &companies->company->comments;
    
    if (companies->company->commentsCounter == companies->company->maxComments) {
        pComment = (Comment *) realloc(companies->company->comments, companies->company->maxComments * 2 * sizeof(Comment));
    }
    
    if (pComment != NULL ) {
            companies->company->maxComments *= 2;
            companies->company->comments = pComment;
        }
    
    
    if (index != -1) {
        readString(companies->company[index].comments[companies->company->commentsCounter].email, MAX_EMAIL, MSG_GET_EMAIL);
        readString(companies->company[index].comments[companies->company->commentsCounter].username, MAX_USERNAME, MSG_GET_USER);
        readString(companies->company[index].comments[companies->company->commentsCounter].title, MAX_TITLE, MSG_GET_TITLE);
        readString(companies->company[index].comments[companies->company->commentsCounter].text, MAX_TEXT, MSG_GET_COMMENT);
    
        companies->company->commentsCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

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
    
    Company *pComment = &companies->company->comments;
    
    if (companies->company->commentsCounter == companies->company->maxComments) {
        pComment = (Comment *) realloc(companies->company->comments, companies->company->maxComments * 2 * sizeof(Comment));
    }
    
    if (pComment != NULL ) {
            companies->company->maxComments *= 2;
            companies->company->comments = pComment;
        }
    
    
    if (index != -1) {
    readString(companies->company[index].comments[companies->company->commentsCounter].email, MAX_EMAIL, MSG_GET_EMAIL);
    readString(companies->company[index].comments[companies->company->commentsCounter].username, MAX_USERNAME, MSG_GET_USER);
    readString(companies->company[index].comments[companies->company->commentsCounter].title, MAX_TITLE, MSG_GET_TITLE);
    readString(companies->company[index].comments[companies->company->commentsCounter].text, MAX_TEXT, MSG_GET_COMMENT);
    
    companies->company->commentsCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

void createClassificationNif(Companies *companies) {
    int nif = getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    int index = searchCompanyNif(*companies, nif);
    
    int *pRating;
    
    if (companies->company->classificationCounter == companies->company->maxClassification) {
        pRating = (int *) realloc(companies->company->classification, companies->company->maxClassification * 2 * sizeof(int));
    }
    
    if (pRating != NULL) {
        companies->company->maxComments *= 2;
        companies->company->classification = pRating;
    }
        
    if (index != -1) {     
        companies->company[index].classification += getInt(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
        companies->company->classificationCounter++;
    } else {
       puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

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
    
    Company *pComment = &companies->company->comments;
    
    if (companies->company->commentsCounter == companies->company->maxComments) {
        pComment = (Comment *) realloc(companies->company->comments, companies->company->maxComments * 2 * sizeof(Comment));
    }
    
    if (pComment != NULL ) {
            companies->company->maxComments *= 2;
            companies->company->comments = pComment;
        }
    
    
    if (index != -1) {
        companies->company[index].classification = getInt(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
        companies->company->classificationCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

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
    
    Company *pComment = &companies->company->comments;
    
    if (companies->company->commentsCounter == companies->company->maxComments) {
        pComment = (Comment *) realloc(companies->company->comments, companies->company->maxComments * 2 * sizeof(Comment));
    }
    
    if (pComment != NULL ) {
            companies->company->maxComments *= 2;
            companies->company->comments = pComment;
        }
    
    
    if (index != -1) {
        companies->company[index].classification = getInt(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
    companies->company->classificationCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
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

void deleteCommentsData(Company company, int index) {
    strcpy(company.comments[index].email, "");
    strcpy(company.comments[index].text, "");
    strcpy(company.comments[index].title, "");
    strcpy(company.comments[index].username, "");
    company.comments[index].status = INATIVO;
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
                    for (i = option1; i < companies->company[value].commentsCounter; i++) {
                        companies->company[value].comments[i] = companies->company[value].comments[i + 1];
                    }

                    deleteCommentsData(companies->company[value], option1);

                    companies->company[value].commentsCounter--;
                    break;
                case 1:
                    companies->company[value].comments[option1].status = INATIVO;
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
        puts("Select the title of the comment to hide/delete: ");
        listCommentsTitle(companies->company[value]);
        scanf("%d", &option1);
        
        puts("Choose what you want to do: ");
        puts("0- Delete Comment");
        puts("1- Hide Comment");
        scanf("%d", &option2);
        
        switch (option2) {
            case 0:
                for (i = 0; i < companies->company[value].commentsCounter; i++) {
                    companies->company[value].comments[i] = companies->company[value].comments[i + 1];
                }
                
                deleteCommentsData(companies->company[value], option1);
                
                companies->company[value].commentsCounter--;
                break;
            case 1:
                companies->company[value].comments[option2].status = INATIVO;
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
        puts("Select the title of the comment to hide/delete: ");
        listCommentsTitle(companies->company[value]);
        scanf("%d", &option1);
        
        puts("Choose what you want to do: ");
        puts("0- Delete Comment");
        puts("1- Hide Comment");
        scanf("%d", &option2);
        
        switch (option2) {
            case 0:
                for (i = 0; i < companies->company[value].commentsCounter; i++) {
                    companies->company[value].comments[i] = companies->company[value].comments[i + 1];
                }
                
                deleteCommentsData(companies->company[value], option1);
                
                companies->company[value].commentsCounter--;
                break;
            case 1:
                companies->company[value].comments[option2].status = INATIVO;
        }
        
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}

void deleteBranchData(Branch *branch) {
    strcpy(branch->branch, "");
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

void deleteBranch(Companies *companies, BranchActivity *branch) {
    if (branch->branchCounter > 0) {
        int i, j, value = removeBranch(branch);
    
        for (i = 0; i < branch->branchCounter; i++) {
            if (strcmp(companies->company[i].branch, branch->branch[value].branch) == 0) {
                puts("You cannot delete this branch of activity. You can only change the branch status for INACTIVE");
                branch->branch[value].status = ATIVO;
            } else {
                for (j = value; j < branch->branchCounter - 1; j++) {
                    strcpy(branch->branch[j].branch, branch->branch[j + 1].branch);
                }
    
                deleteBranchData(&branch->branch[j]);
    
                branch->branchCounter--;
            }
        }
    } else {
        puts("There are no branches of activity available for remove. Please create one first.");
    }
}

void loadCompaniesFromFile(Companies *companies, BranchActivity *branch, char *filename) {
    int i, success = 0;

    FILE *fp = fopen(filename, "rb");
    if (fp != NULL) {
        fread(&companies->companiesCounter, sizeof(int), 1, fp);
        fread(&branch->branchCounter, sizeof(int), 1, fp);

        if (companies->companiesCounter > 0) {
            companies->maxCompanies = companies->companiesCounter;
            companies->company = (Company *) malloc(companies->companiesCounter * sizeof(Company));

            branch->maxBranch = branch->branchCounter > 7 ? branch->branchCounter * 2 : 7;
            branch->branch = (Branch *)malloc(branch->maxBranch * sizeof(Branch));

            for (i = 0; i < companies->maxCompanies; i++) {
                fread(&companies->company[i], sizeof(Company), 1, fp);

                companies->company[i].comments = (Comment *)malloc(companies->company[i].commentsCounter * sizeof(Comment));

                fread(companies->company[i].comments, sizeof(Comment), companies->company[i].commentsCounter, fp);

                fread(branch->branch[i].branch, sizeof(char), MAX_BRANCH, fp);
                fread(&branch->branch[i].status, sizeof(Status), 1, fp);

                printf("Index: %d\n", i);
                printf("%u [NIF]\n", companies->company[i].nif);
                printf("%s [name]\n", companies->company[i].name);
                printf("%s [location]\n", companies->company[i].location);
                printf("%s [Branch]\n", branch->branch[i].branch);
                printf("Status empresa: %d\n", companies->company[i].status);
                printf("Status branches: %d\n", branch->branch[i].status);
            }


            success = 1;
        }

        fclose(fp);
    }

    if (!success) {
        companies->maxCompanies = 10;
        companies->company = (Company *)malloc(companies->maxCompanies * sizeof(Company));
        companies->companiesCounter = 0;

        branch->maxBranch = 7;
        branch->branch = (Branch *)malloc(branch->maxBranch * sizeof(Branch));
        branch->branchCounter = 0;
    }
}

void saveCompanies(Companies *companies, BranchActivity *branch, char *filename) {
    int i;

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&companies->companiesCounter, sizeof(int), 1, fp);
    fwrite(&branch->branchCounter, sizeof(int), 1, fp);

    for (i = 0; i < companies->companiesCounter; i++) {
        fwrite(&companies->company[i], sizeof(Company), 1, fp);

        fwrite(companies->company[i].comments, sizeof(Comment), companies->company[i].commentsCounter, fp);

        fwrite(branch->branch[i].branch, sizeof(char), MAX_BRANCH, fp);
        fwrite(&branch->branch[i].status, sizeof(Status), 1, fp);
    }

    fclose(fp);
}






void listHigherCompanies(Companies *companies, Branch *branch) { 
    if (companies->companiesCounter > 0) {
        int i;
        for (i = 0; i < companies->companiesCounter; i++) {
            if (calculateAverageRating(&companies->company[i]) > 4.5) {
                printCompany(companies->company[i], *branch);
                printf("Average rating: %.2f\n", calculateAverageRating(&companies->company[i]));
            }
        }

    } else {
        puts(ERROR_EMPY_LIST);
    }
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
        printf("\nUsername: %s\n", company.comments[i].username);
        printf("Title: %s\n", company.comments[i].title);
        printf("Comment: %s\n", company.comments[i].text);
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

void listMostCompanies(Companies companies, int sizeOfTop) {
    if (companies.companiesCounter > 0) {
        int size = companies.companiesCounter >= sizeOfTop ? sizeOfTop : companies.companiesCounter;
        int array[size];

        mostSearchedCompanies(companies, size, array);

        for (int i = 0; i < size; i++) {
            printf("The %d company name is : %s \n", i + 1, companies.company[array[i]].name);
            printf("Average Rating: %.2f\n", calculateAverageRating(&companies.company[i]));
            listComments(companies.company[array[i]]);
        }
    }
}


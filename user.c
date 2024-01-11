/**
 * @file user.c
 * @brief Implementation of user-related functionalities for managing companies.
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


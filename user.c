#include "companies.h"
#include "input.h"
#include "tools.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


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

void createCommentNif(Companies *companies) {
    int value = getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF);
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

void createClassificationNif(Companies *companies) {
    int nif = getInt(MIN_NIF, MAX_NIF, MSG_GET_NIF);
    int index = searchCompanyNif(*companies, nif);
           
    if (index != -1) {     
        companies->company[index].classification += getInt(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
        companies->company[index].classificationCounter++;
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
    
   
    if (index != -1) {
        companies->company[index].classification = getInt(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
        companies->company[index].classificationCounter++;
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
    
    
    if (index != -1) {
        companies->company[index].classification = getInt(MIN_RATING, MAX_RATING, MSG_GET_RATING);
        
    companies->company[index].classificationCounter++;
    } else {
        puts(ERROR_COMPANY_DOES_NOT_EXIST);
    }
}


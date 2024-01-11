/**
* @file input.h
* @author Luís Morais & Cláudio Coelho
* @date 14-12-2023
* @version 1
*
*
* @brief A header file providing utility functions for user input validation and retrieval.
*
* This header file contains a collection of functions designed to facilitate user input
* in a C or C++ program. It includes functions for obtaining integers, floats, doubles,
* characters, and strings from the user while performing input validation to ensure
* that the entered values are within specified ranges or constraints.
*/
#ifndef COMPANIES_H
#define COMPANIES_H

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_NIF 999999999
#define MIN_NIF 100000000
#define MSG_GET_NIF "Enter the company's NIF: "

#define MAX_NAME 30
#define MSG_GET_NAME "Enter the company's name: "

#define MAX_ADRESS 80
#define MSG_GET_ADRESS "Enter the company's adress: "

#define MIN_LOCATION 0
#define MAX_LOCATION 30
#define MSG_GET_LOCATION "Enter the company's location: "

#define MAX_POSTAL_CODE 9
#define MSG_GET_POSTAL_CODE "Enter the company's Postal Code: "

#define MAX_TITLE 40
#define MAX_TEXT 300
#define MAX_USERNAME 15
#define MAX_EMAIL 40
#define MSG_GET_USER "Please, enter your username: "
#define MSG_GET_EMAIL "Please, enter your email: "
#define MSG_GET_TITLE "Enter the title of the comment: "
#define MSG_GET_COMMENT "Write the comment bellow: "
    
#define MIN_TYPE 0
#define MAX_TYPE 6
#define MSG_GET_TYPE "Select the company's branch of activity [0-6] :\n 0- Agricultura\n 1- Eletricidade\n 2- Gás e Água\n 3- Têxteis e Vestuário\n 4- Construção\n 5- Bancos\n 6- Seguros"

#define MIN_CATEGORY 0
#define MAX_CATEGORY 2
#define MSG_GET_CATEGORY "Select the company's category [0-2] :\n 0- Micro\n 1- PME\n 2- Grande"

#define MIN_STATUS 0
#define MAX_STATUS 1
#define MSG_GET_STATUS "Select the company's status [0-1] :\n 0- Inativo\n 1- Ativo"
    
#define MIN_RATING 0
#define MAX_RATING 5
#define MSG_GET_RATING "Rate the company from 0 to 5: "    

#define MAX_BRANCH  40
#define MSG_GET_BRANCH "Choose one branch or create a new one: "
#define MSG_CREATE_BRANCH "Enter the company's new branch: "
#define ERROR_BRANCH_ALREADY_EXIST "ERROR! Branch of activity already exists!"

#define ERROR_COMPANY_DOES_NOT_EXIST "Error! Company does not exist!"
#define ERROR_COMPANY_ALREADY_EXIST "Error! Company already exists!"
#define ERROR_EMPY_LIST "Error! The list of companies is empty!"    
#define ERROR_CREATE_BRANCH "Error: The list of branches of activity is empty. Please create at least one line of business to create a company."    
#define ERROR_INVALID_EMAIL "Error: Please, enter a valid email format."    


typedef enum {
    MICRO, PME, GRANDE, EMPTY
} Category;


typedef enum {
    INATIVO, ATIVO
} Status;

typedef struct {
    char branch[MAX_BRANCH];
    Status status;
} Branch;

typedef struct {
    int maxBranch;
    int branchCounter;
    Branch *branch;
} BranchActivity;

typedef struct {
    char title[MAX_TITLE];
    char text[MAX_TEXT];
    char username[MAX_USERNAME];
    char email[MAX_EMAIL];
    Status status;
} Comment;


typedef struct {
    unsigned int nif;
    char name[MAX_NAME];
    Category companyCategory;
    char branch[MAX_BRANCH];
    char adress[MAX_ADRESS];
    char location[MAX_LOCATION];
    char postalCode [MAX_POSTAL_CODE];
    Status status;
    int maxComments;
    int commentsCounter;
    int classificationCounter;
    int classification;
    Comment *comments;
    int searchCounter;
} Company;


typedef struct {
    int companiesCounter;
    int maxCompanies;
    Company *company;
} Companies;


void loadData(Companies *companies, BranchActivity *branch, char *filename);
void saveData(Companies *companies, BranchActivity *branch, char*);
void printBranches(BranchActivity branch);
void freeMemory(Companies *companies, BranchActivity *branch);


#ifdef __cplusplus
}
#endif

#endif /* COMPANIES_H */

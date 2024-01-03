
/*
 * File:   companies.h
 * Author: Luís Morais
 *
 * Created on 14 de dezembro de 2023, 21:10
 */

#ifndef COMPANIES_H
#define COMPANIES_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define COMPANIES_INITIAL_CAPACITY 10

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

#define MAX_POSTAL_CODE 8
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


typedef enum {
    MICRO, PME, GRANDE, EMPTY
} Category;


typedef enum {
    INATIVO, ATIVO
} Status;

typedef struct {
    char branch[MAX_BRANCH];
} Branch;

typedef struct {
    int maxBranch;
    int branchCounter;
    Branch *branch;
    Status status;
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
    int maxClassification;
    int classificationCounter;
    float averageRating;
    int *classification;
    Comment *comments;
} Company;


typedef struct {
    int companiesCounter;
    int maxCompanies;
    Company *company;
} Companies;

void loadCompanyFromFile(Companies *, char*);

void printCompany(Company company, BranchActivity branch);
void companyNif(Companies companies, BranchActivity branch);
void companyName(Companies companies, BranchActivity branch);
void companyLocation(Companies companies, BranchActivity branch);
void createActivity(BranchActivity *branch);
void printBranches(BranchActivity branch);
void insertCompanies(Companies *company, BranchActivity *branch, char *filename);
void updateCompaniesByNif(Companies *companies, BranchActivity *branch, char *filename);
void updateCompaniesByName(Companies *companies, BranchActivity *branch, char *filename);
void updateCompaniesByLocation(Companies *companies, BranchActivity *branch, char *filename);
void updateBranches(BranchActivity *branch );
void createCommentLocation(Companies *companies);
void createCommentName(Companies *companies);
void createCommentNif(Companies *companies);
void createClassificationLocation(Companies *companies);
void createClassificationName(Companies *companies);
void createClassificationNif(Companies *companies);
void deleteCompanyNif(Companies *companies, char *filename);
void manageCommentsNif(Companies *companies);
void manageCommetsName(Companies *companies);
void manageCommentsLocation(Companies *companies);
void deleteBranch(Companies *companies, BranchActivity *branch);
void listHigherCompanies(Companies *companies, BranchActivity *branch);
void saveCompanies(Companies *companies, char *filename);
void freeCompanies(Companies *companies);

#ifdef __cplusplus
}
#endif

#endif /* COMPANIES_H */

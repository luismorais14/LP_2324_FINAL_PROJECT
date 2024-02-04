/**
* @file input.h
* @author Luís Morais & Cláudio Coelho
* @date 14-12-2023
* @version 1
*
*
* @brief A header file providing utility functions for user input validation and retrieval.
*
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

#define ERROR_COMPANY_DOES_NOT_EXIST "Error! Company does not exist!"
#define ERROR_COMPANY_ALREADY_EXIST "Error! Company already exists!"
#define ERROR_EMPY_LIST "Error! The list of companies is empty!"    
#define ERROR_CREATE_BRANCH "Error: The list of branches of activity is empty. Please create at least one line of business to create a company."    
#define ERROR_INVALID_EMAIL "Error: Please, enter a valid email format."    
#define ERROR_BRANCH_ALREADY_EXIST "Error creating new branch of activity: Branch already exists."  

typedef enum {
    MICRO, PME, GRANDE
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
    int nif;
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


/**
 * @brief Loads data from a file into the Companies and BranchActivity structures.
 * @param companies Pointer to the Companies structure.
 * @param branch Pointer to the BranchActivity structure.
 * @param filename Name of the file from which data is loaded.
 */
void loadData(Companies *companies, BranchActivity *branch, char *filename);

/**
 * @brief Saves data from the Companies and BranchActivity structures into a file.
 * @param companies Pointer to the Companies structure.
 * @param branch Pointer to the BranchActivity structure.
 * @param filename Name of the file in which data is saved.
 */
void saveData(Companies *companies, BranchActivity *branch, char*);

/**
 * @brief Prints information about branches.
 * @param branch BranchActivity structure containing branch information.
 */
void printBranches(BranchActivity branch);

/**
 * @brief Frees memory allocated for the Companies and BranchActivity structures.
 * @param companies Pointer to the Companies structure.
 * @param branch Pointer to the BranchActivity structure.
 */
void freeMemory(Companies *companies, BranchActivity *branch);

/**
 * @brief Logs a message to a file.
 * @param msg Message to be logged.
 * @param filename Name of the log file.
 */
void logFile(char *msg, char *filename);

/**
 * @brief Verifies the format of a postal code.
 * @param zipCode String containing the postal code to be verified.
 * @return 0 if the postal code is valid, -1 otherwise.
 */
int postalCodeVerification(char *zipCode);

/**
 * @brief Verifies the format of an email address.
 * @param comment Pointer to the Comment structure containing the email to be verified.
 * @return -1 if the email address is valid, 1 otherwise.
 */
int emailVerification(Comment *comment);
      
/**
 * @brief Create a new branch of activity.
 * @param branch The structure holding information about branch activities.
 */
void createActivity(BranchActivity *branch);

/**
 * @brief Insert a new company into the system.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @return Returns the index of the newly inserted company.
 */
int insertCompany(Companies *companies, BranchActivity *branch);

/**
 * @brief Wrapper function to insert a new company into the system.
 * @param company The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 */
void insertCompanies(Companies *company, BranchActivity *branch);

/**
 * @brief Update company information based on NIF.
 * @param company The structure holding information about a specific company.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompany(Company *company, BranchActivity *branch);

/**
 * @brief Update company information based on NIF.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByNif(Companies *companies, BranchActivity *branch);

/**
 * @brief Update company information based on name.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByName(Companies *companies, BranchActivity *branch);

/**
 * @brief Update company information based on location.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByLocation(Companies *companies, BranchActivity *branch);

/**
 * @brief Update branch information.
 * @param branch The structure holding information about branch activities.
 */
void updateBranches(Companies *companies, BranchActivity *branch);

/**
 * @brief Delete a company based on NIF.
 * @param companies The structure holding information about companies.
 */
void deleteCompanyNif(Companies *companies);

/**
 * @brief Delete a company based on name.
 * @param companies The structure holding information about companies.
 */
void deleteCompanyName(Companies *companies);

/**
 * @brief Delete a company based on location.
 * @param companies The structure holding information about companies.
 */
void deleteCompanyLocation(Companies *companies);

/**
 * @brief Manage comments for a specific company based on NIF.
 * @param companies The structure holding information about companies.
 */
void manageCommentsNif(Companies *companies);

/**
 * @brief Manage comments for a specific company based on name.
 * @param companies The structure holding information about companies.
 */
void manageCommetsName(Companies *companies);

/**
 * @brief Manage comments for a specific company based on location.
 * @param companies The structure holding information about companies.
 */
void manageCommentsLocation(Companies *companies);

/**
 * @brief Delete a branch of activity.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 */
void deleteBranch(Companies *companies, BranchActivity *branch);

/**
 * @brief List companies with higher average ratings.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void listHigherCompanies(Companies *companies, BranchActivity *branchActivity);

/**
 * @brief List the most searched companies.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 * @param sizeOfTop The number of top companies to list.
 */
void listMostCompanies(Companies companies, BranchActivity branchActivity, int sizeOfTop);
   
/**
 * @brief Display company information based on NIF.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void companyNif(Companies companies, BranchActivity branchActivity);

/**
 * @brief Display company information based on name.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void companyName(Companies companies, BranchActivity branchActivity);

/**
 * @brief Display company information based on location.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void companyLocation(Companies companies, BranchActivity branchActivity);

/**
 * @brief Select a branch of activity from the available options.
 * @param branch The structure holding information about branch activities.
 * @param selectedBranch Pointer to store the selected branch.
 */
void selectBranch(BranchActivity *branch, char *selectedBranch);

/**
 * @brief Create a new comment for a company based on NIF.
 * @param companies The structure holding information about companies.
 */
void createCommentNif(Companies *companies);

/**
 * @brief Create a new comment for a company based on name.
 * @param companies The structure holding information about companies.
 */
void createCommentName(Companies *companies);

/**
 * @brief Create a new comment for a company based on location.
 * @param companies The structure holding information about companies.
 */
void createCommentLocation(Companies *companies);

/**
 * @brief Create a new classification for a company based on NIF.
 * @param companies The structure holding information about companies.
 */
void createClassificationNif(Companies *companies);

/**
 * @brief Create a new classification for a company based on name.
 * @param companies The structure holding information about companies.
 */
void createClassificationName(Companies *companies);

/**
 * @brief Create a new classification for a company based on location.
 * @param companies The structure holding information about companies.
 */
void createClassificationLocation(Companies *companies);

#ifdef __cplusplus
}
#endif

#endif /* COMPANIES_H */

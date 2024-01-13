/**
 * @file menus.c
 * @brief Implementation of menus and user interface functions.
 * @author Luís Morais & Cláudio Coelho
 * @date 24-11-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "companies.h"
#include "user.h"
#include "admin.h"

/**
 * @brief Display the search menu options.
 */
void displaySearchMenu() {
    puts("----------------------------");
    puts("1- Search by NIF");
    puts("2- Search by Name");
    puts("3- Search by Location");
    puts("4- Go Back");
    puts("----------------------------");
    puts("Choose one of the options above: [1 - 4]");
}

/**
 * @brief Handle the search menu options.
 * @param companies The structure holding information about companies.
 * @param branchActivity The structure holding information about branch activities.
 */
void searchMenu(Companies *companies, BranchActivity *branchActivity) {
    int option;

    do {
        displaySearchMenu();
        scanf(" %d", &option);

        switch (option) {
            case 1:
                companyNif(*companies, *branchActivity);
                break;
            case 2:
                companyName(*companies, *branchActivity);
                break;
            case 3:
                companyLocation(*companies, *branchActivity);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

/**
 * @brief Handle the update menu options.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The filename for data persistence.
 */
void updateMenu(Companies *companies, BranchActivity *branch) {
    int option;

    do {
        displaySearchMenu();
        scanf(" %d", &option);

        switch (option) {
            case 1:
                updateCompaniesByNif(companies, branch);
                break;
            case 2:
                updateCompaniesByName(companies, branch);
                break;
            case 3:
                updateCompaniesByLocation(companies, branch);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

/**
 * @brief Handle the comment menu options.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 */
void commentMenu(Companies *companies, BranchActivity *branch) {
    int option;
    
    do {
        displaySearchMenu();
        scanf(" %d", &option);
        
        switch (option) {
            case 1:
                createCommentNif(companies);
                break;
            case 2:
                createCommentName(companies);
                break;
            case 3:
                createCommentLocation(companies);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        } 
    } while (option != 4);
}

/**
 * @brief Handle the rating menu options.
 * @param companies The structure holding information about companies.
 */
void ratingMenu(Companies *companies) {
    int option;
    
    do  {
        displaySearchMenu();
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                createClassificationNif(companies);
                break;
            case 2:
                createClassificationName(companies);
                break;
            case 3:
                createClassificationLocation(companies);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

/**
 * @brief Handle the delete menu options.
 * @param companies The structure holding information about companies.
 * @param filename The filename for data persistence.
 */
void deleteMenu(Companies *companies) {
    int option;
    
    do {
        displaySearchMenu();
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                deleteCompanyNif(companies);
                break;
            case 2:
                deleteCompanyName(companies);
                break;
            case 3:
                deleteCompanyLocation(companies);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

/**
 * @brief Handle the comments menu options.
 * @param companies The structure holding information about companies.
 */
void commentsMenu(Companies *companies) {
    int option;
    
    do {
        displaySearchMenu();
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                manageCommentsNif(companies);
                break;
            case 2:
                manageCommetsName(companies);
                break;
            case 3:
                manageCommentsLocation(companies);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");  
        }
    } while (option != 4);
}

/**
 * @brief Handle the reports menu options.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 */
void reportsMenu(Companies *companies, BranchActivity *branch) {
    int option;
    
    do {
        puts("----------------------------");
        puts("       REPORTS MENU");
        puts("----------------------------");
        puts("1- List companies with a rating higher than 4.5");
        puts("2- List the most searched companies");
        puts("3- Go Back");
        puts("Choose one of the options above: [1 - 3]");
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                logFile("List companies with a rating higher than 4.5", "log.txt");
                listHigherCompanies(companies, branch);
                break;
            case 2:
                logFile("List the most searched companies", "log.txt");
                listMostCompanies(*companies, *branch, TOP_SEARCH_QUANTITY);
                break;
            case 3:
                break;
            default:
                puts("Invalid option. Please try again.");
        }    

    } while (option != 3);
}

/**
 * @brief Handle the companies catalog menu options.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The filename for data persistence.
 */
void companiesCatalog(Companies *companies, BranchActivity *branch) {
    int option;

    do {
        puts("----------------------------");
        puts("1- Create Company");
        puts("2- Edit Company");
        puts("3- Remove Company");
        puts("4- Manage Comments");
        puts("5- Go Back");
        puts("----------------------------");
        puts("Choose one of the options above: [1 - 5]");
        scanf("%d", &option);

        switch (option) {
            case 1:
                logFile("Create Company", "log.txt");
                insertCompanies(companies, branch);
                break;
            case 2:
                logFile("Update Company", "log.txt");
                updateMenu(companies, branch);
                break;
            case 3:
                logFile("Delete Company", "log.txt");
                deleteMenu(companies);
                break;
            case 4:
                logFile("Manage Comments", "log.txt");
                commentsMenu(companies);
                break;
            case 5:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 5);
}

/**
 * @brief Handle the branches of activity menu options.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 */
void branchesOfActivity(Companies *companies, BranchActivity *branch) {
    int option;

    do {
        puts("----------------------------");
        puts("1- Create branches of Activity");
        puts("2- Edit branches of Activity");
        puts("3- Remove branches of Activity");
        puts("4- Go Back");
        puts("----------------------------");
        puts("Choose one of the options above: [1 - 4]");
        scanf("%d", &option);

        switch (option) {
            case 1:
                logFile("Create branch of activity", "log.txt");
                createActivity(branch);
                break;
            case 2:
                logFile("Update branch of activity", "log.txt");
                updateBranches(branch);
                break;
            case 3:
                logFile("Delete branch of activity", "log.txt");
                deleteBranch(companies, branch);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

/**
 * @brief Handle the admin menu options.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The filename for data persistence.
 */
void adminMenu(Companies *companies, BranchActivity *branch) {
    int option;

    do {        
        puts("----------------------------");
        puts("     ADMIN MENU");
        puts("----------------------------");
        puts("1- Manage the Companies Catalog");
        puts("2- Manage branches of Activity");
        puts("3- View Reports");
        puts("4- Go Back");
        puts("----------------------------");
        puts("Choose one of the options above: [1 - 4]");
        scanf(" %d", &option);

        switch (option) {
            case 1:
                companiesCatalog(companies, branch);
                break;
            case 2:
                branchesOfActivity(companies, branch);
                break;
            case 3:
                reportsMenu(companies, branch);
                puts("View Reports");
                break;
            case 4:
                break;   
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

/**
 * @brief Handle the user menu options.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 */
void userMenu(Companies *companies, BranchActivity *branch) {
    int option;

    do {
        puts("----------------------------");
        puts("     USER MENU");
        puts("----------------------------");
        puts("1- Search Companies");
        puts("2- Classify Companies ");
        puts("3- Comment Companies");
        puts("4- Go Back");
        puts("----------------------------");
        puts("Choose one of the options above: [1 - 4]");
        scanf(" %d", &option);

        switch (option) {
            case 1:
                logFile("Search Company", "log.txt");
                searchMenu(companies, branch);
                break;
            case 2:
                logFile("Classify Company", "log.txt");
                ratingMenu(companies);
                break;
            case 3:
                logFile("Comment Company", "log.txt");
                commentMenu(companies, branch); 
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

/**
 * @brief Handle the main menu options.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The filename for data persistence.
 */
void mainMenu(Companies *companies, BranchActivity *branch) {
    int option;

    do {
        puts("----------------------------");
        puts("       MAIN MENU");
        puts("----------------------------");
        puts("1- Administrator");
        puts("2- User");
        puts("3- Quit");
        puts("----------------------------");
        puts("Choose one of the options above: [1 - 3]");
        scanf(" %d", &option);

        switch (option) {
            case 1:
                logFile("Admin Menu", "log.txt");
                adminMenu(companies, branch);
                break;
            case 2:
                logFile("User Menu", "log.txt");
                userMenu(companies, branch);
                break;
            case 3:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 3);
}
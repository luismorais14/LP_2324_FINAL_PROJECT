#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "companies.h"

void displaySearchMenu() {
    puts("----------------------------");
    puts("1- Search by NIF");
    puts("2- Search by Name");
    puts("3- Search by Location");
    puts("4- Go Back");
    puts("----------------------------");
    puts("Choose one of the options above: [1 - 4]");
}

void searchMenu(Companies *companies, BranchActivity *branch) {
    int option;

    do {
        displaySearchMenu();
        scanf(" %d", &option);

        switch (option) {
            case 1:
                companyNif(*companies, *branch);
                break;
            case 2:
                companyName(*companies, *branch);
                break;
            case 3:
                companyLocation(*companies, *branch);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

void updateMenu(Companies *companies, BranchActivity *branch, char *filename) {
    int option;

    do {
        displaySearchMenu();
        scanf(" %d", &option);

        switch (option) {
            case 1:
                updateCompaniesByNif(companies, branch, filename);
                break;
            case 2:
                updateCompaniesByName(companies, branch, filename);
                break;
            case 3:
                updateCompaniesByLocation(companies, branch, filename);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

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

void deleteMenu(Companies *companies, char *filename) {
    int option;
    
    do {
        displaySearchMenu();
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                deleteCompanyNif(companies, filename);
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
                listHigherCompanies(companies, branch);
                break;
            case 2:
                listMostSearchedCompanies(*companies, *branch);
                break;
            case 3:
                break;
            default:
                puts("Invalid option. Please try again.");
        }    

    } while (option != 3);
}

void companiesCatalog(Companies *companies, BranchActivity *branch, char *filename) {
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
                insertCompanies(companies, branch, filename);
                break;
            case 2:
                updateMenu(companies, branch, filename);
                break;
            case 3:
                deleteMenu(companies, filename);
                break;
            case 4:
                commentsMenu(companies);
                break;
            case 5:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 5);
}

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
                createActivity(branch);
                break;
            case 2:
                updateBranches(branch);
                break;
            case 3:
                deleteBranch(companies, branch);
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}



void adminMenu(Companies *companies, BranchActivity *branch, char *filename) {
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
                companiesCatalog(companies, branch, filename);
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
                searchMenu(companies, branch);
                break;
            case 2:
                ratingMenu(companies);
                break;
            case 3:
                commentMenu(companies, branch);                
                break;
            case 4:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 4);
}

void mainMenu(Companies *companies, BranchActivity *branch, char *filename) {
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
                adminMenu(companies, branch, filename);
                break;
            case 2:
                userMenu(companies, branch);
                break;
            case 3:
                break;
            default:
                puts("Invalid option. Please try again.");
        }
    } while (option != 3);
}
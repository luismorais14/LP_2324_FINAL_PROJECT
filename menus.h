/**
* @file menus.h
* @author Luís Morais & Cláudio Coelho
* @date 14-12-2023
* @version 1
*
*
* @brief A header file providing menus functions.
*
* This header file contains the menu functions to be used in the program.
*/

#ifndef MENUS_H
#define MENUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "companies.h"

/**
 * @brief A constant string representing the number of most searched companies.
 *
 * This constant is used to define the number of most searched companies to be presented.
 */
#define TOP_SEARCH_QUANTITY 3
    
/**
* @brief This function displays the main menu when the program starts.
* @param companies Pointer to the Companies structure.
* @param branch Pointer to the BranchActivity structure.
*/
void mainMenu(Companies *companies, BranchActivity *branch);

/**
* @brief This function displays the admin menu.
* @param companies Pointer to the Companies structure.
* @param branch Pointer to the BranchActivity structure.
*/
void adminMenu(Companies *companies, BranchActivity *branch);

/**
* @brief This function displays the user menu.
* @param companies Pointer to the Companies structure.
* @param branch Pointer to the BranchActivity structure.
*/
void userMenu(Companies *companies, BranchActivity *branch);


#ifdef __cplusplus
}
#endif

#endif /* MENUS_H */


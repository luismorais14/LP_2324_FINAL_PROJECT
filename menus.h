
/*
 * File:   menus.h
 * Author: Luís Morais
 *
 * Created on 14 de dezembro de 2023, 20:30
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
    
void mainMenu(Companies *companies, BranchActivity *branch);
void adminMenu(Companies *companies, BranchActivity *branch);
void userMenu(Companies *companies, BranchActivity *branch);
void companiesCatalog(Companies *companies, BranchActivity *branch);


#ifdef __cplusplus
}
#endif

#endif /* MENUS_H */


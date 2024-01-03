
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

void mainMenu(Companies *companies, BranchActivity *branch, char *filename);
void adminMenu(Companies *companies, BranchActivity *branch, char *filename);
void userMenu(Companies *companies, BranchActivity *branch);
void companiesCatalog(Companies *companies, BranchActivity *branch, char *filename);


#ifdef __cplusplus
}
#endif

#endif /* MENUS_H */


/**
* @file admin.h
* @author Luís Morais & Cláudio Coelho
* @date 14-12-2023
* @version 1
*
*
* @brief A header file providing utility functions for administrator features.
*
* This header file contains the collection of functions designed to facilitate 
* the program's administrator functions. It includes functions for creating, 
* editing and removing companies, managing comments, creating or deleting branches 
* of activity and functions for viewing reports on the companies created.
* 
*/

#ifndef ADMIN_H
#define ADMIN_H

#ifdef __cplusplus
extern "C" {
#endif

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
void updateCompany(Company *company, BranchActivity *branch, char *filename);

/**
 * @brief Update company information based on NIF.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByNif(Companies *companies, BranchActivity *branch, char *filename);

/**
 * @brief Update company information based on name.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByName(Companies *companies, BranchActivity *branch, char *filename);

/**
 * @brief Update company information based on location.
 * @param companies The structure holding information about companies.
 * @param branch The structure holding information about branch activities.
 * @param filename The name of the file to save the changes.
 */
void updateCompaniesByLocation(Companies *companies, BranchActivity *branch, char *filename);

/**
 * @brief Update branch information.
 * @param branch The structure holding information about branch activities.
 */
void updateBranches(BranchActivity *branch);

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


#ifdef __cplusplus
}
#endif

#endif /* ADMIN_H */


/* 
 * File:   user.h
 * Author: Luís Morais
 *
 * Created on 8 de janeiro de 2024, 17:53
 */

#ifndef USER_H
#define USER_H

#ifdef __cplusplus
extern "C" {
#endif

    
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

#endif /* USER_H */


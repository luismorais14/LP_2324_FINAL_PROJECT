

#ifndef ADMIN_H
#define ADMIN_H

#ifdef __cplusplus
extern "C" {
#endif

void createActivity(BranchActivity *branch);
int insertCompany(Companies *companies, BranchActivity *branch);
void insertCompanies(Companies *company, BranchActivity *branch);
void updateCompany(Company *company, BranchActivity *branch, char *filename);
void updateCompaniesByNif(Companies *companies, BranchActivity *branch, char *filename);
void updateCompaniesByName(Companies *companies, BranchActivity *branch, char *filename);
void updateCompaniesByLocation(Companies *companies, BranchActivity *branch, char *filename);
void updateBranches(BranchActivity *branch);
void deleteCompanyNif(Companies *companies);
void deleteCompanyName(Companies *companies);
void deleteCompanyLocation(Companies *companies);
void manageCommentsNif(Companies *companies);
void manageCommetsName(Companies *companies);
void manageCommentsLocation(Companies *companies);
void deleteBranch(Companies *companies, BranchActivity *branch);
void listHigherCompanies(Companies *companies, BranchActivity *branchActivity);
void listMostCompanies(Companies companies, BranchActivity branchActivity, int sizeOfTop);


#ifdef __cplusplus
}
#endif

#endif /* ADMIN_H */


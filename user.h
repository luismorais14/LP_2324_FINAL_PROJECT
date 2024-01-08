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

void selectBranch(BranchActivity *branch, char *selectedBranch);
void createCommentNif(Companies *companies);
void createCommentName(Companies *companies);
void createCommentLocation(Companies *companies);
void createClassificationNif(Companies *companies);
void createClassificationName(Companies *companies);
void createClassificationLocation(Companies *companies);



#ifdef __cplusplus
}
#endif

#endif /* USER_H */


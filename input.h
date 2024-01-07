
/*
 * File:   input.h
 * Author: Luís Morais
 *
 * Created on 15 de dezembro de 2023, 13:28
 */

#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

void cleanInputBuffer();
long long getInt(long long minValue, long long maxValue, char *msg);
float getFloat(float minValue, float maxValue, char *msg);
double getDouble(double minValue, double maxValue, char *msg);
char getChar(char *msg);
void readString(char *string, unsigned int length, char *msg);

#ifdef __cplusplus
}
#endif

#endif /* INPUT_H */


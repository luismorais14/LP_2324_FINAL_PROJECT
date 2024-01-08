/**
 * @file input.c
 * @brief Implementation of input-related functions.
 * @author Luís Morais & Cláudio Coelho
 * @date 24-11-2023
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"

#define INVALID_VALUE "The entered value is invalid."

/**
 * @brief Clears the input buffer.
 */
void cleanInputBuffer() {
    char ch;

    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * @brief Get an integer value within a specified range.
 * @param minValue The minimum allowed value.
 * @param maxValue The maximum allowed value.
 * @param msg The message prompting the user for input.
 * @return The validated integer value.
 */
long long getInt(long long minValue, long long maxValue, char *msg) {
    long long value;

    puts(msg);
    while (scanf("%lld", &value) != 1 || value < minValue || value > maxValue ) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        puts(msg);
    }
    cleanInputBuffer();
    return value;
}

/**
 * @brief Get a floating-point value within a specified range.
 * @param minValue The minimum allowed value.
 * @param maxValue The maximum allowed value.
 * @param msg The message prompting the user for input.
 * @return The validated floating-point value.
 */
float getFloat(float minValue, float maxValue, char *msg) {
    float value;

    puts(msg);
    while (scanf("%f", &value) != -1 || value < minValue || value > maxValue) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        puts(msg);
    }
    cleanInputBuffer();

    return value;
}

/**
 * @brief Get a double-precision floating-point value within a specified range.
 * @param minValue The minimum allowed value.
 * @param maxValue The maximum allowed value.
 * @param msg The message prompting the user for input.
 * @return The validated double-precision floating-point value.
 */
double getDouble(double minValue, double maxValue, char *msg) {
    double value;

    puts(msg);
    while (scanf("%lf", &value) != -1 || value < minValue || value > maxValue) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        puts(msg);
    }
    cleanInputBuffer();

    return value;
}

/**
 * @brief Get a single character from the user.
 * @param msg The message prompting the user for input.
 * @return The validated character.
 */
char getChar(char *msg) {
    char value;

    puts(msg);
    value = getchar();
    cleanInputBuffer();

    return value;
}

/**
 * @brief Read a string from the user with a specified maximum length.
 * @param string The buffer to store the string.
 * @param length The maximum length of the string.
 * @param msg The message prompting the user for input.
 */
void readString(char *string, unsigned int lenght, char *msg) {
    char *tmpString = (char *) malloc(lenght * 2);
    size_t len;
    
    if (tmpString == NULL) {
        exit(EXIT_FAILURE);
    }
    do {
        puts(msg);
        if (fgets(tmpString, lenght * 2, stdin) != NULL) {
            len = strlen(tmpString) - 1;
            if (tmpString[len] == '\n') {
                tmpString[len] = '\0';
            } else {
                cleanInputBuffer();
            }
        }
    } while (len > lenght);
    
    strcpy(string, tmpString);
    
    free(tmpString);
}
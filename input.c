#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"

#define INVALID_VALUE "The entered value is invalid."

void cleanInputBuffer() {
    char ch;

    while ((ch = getchar()) != '\n' && ch != EOF);
}

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

char getChar(char *msg) {
    char value;

    puts(msg);
    value = getchar();
    cleanInputBuffer();

    return value;
}

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
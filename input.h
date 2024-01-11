/**
* @file input.h
* @author Luís Morais & Cláudio Coelho
* @date 14-12-2023
* @version 1
*
*
* @brief A header file providing utility functions for user input validation and retrieval.
*
* This header file contains a collection of functions designed to facilitate user input
* in a C or C++ program. It includes functions for obtaining integers, floats, doubles,
* characters, and strings from the user while performing input validation to ensure
* that the entered values are within specified ranges or constraints.
*/

#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

void cleanInputBuffer();

/**
* @brief This function prompts the user to input an long long within a specified range
* and displays a custom message.
* @param minValue The minimum valid integer value.
* @param maxValue The maximum valid integer value.
* @param msg A custom message to prompt the user for input.
* @return The user-provided long long value within the specified range.
*/
long long getNum(long long minValue, long long maxValue, char *msg);

/**
 * @brief This function prompts the user to input a floating-point number within a specified range and displays a custom message.
 * @param minValue The minimum valid floating-point value.
 * @param maxValue The maximum valid floating-point value.
 * @param msg A custom message to prompt the user for input.
 * @return The user-provided floating-point value within the specified range.
 */
float getFloat(float minValue, float maxValue, char *msg);

/**
 * @brief This function prompts the user to input a double-precision floating-point number within a specified range and displays a custom message.
 * @param minValue The minimum valid double value.
 * @param maxValue The maximum valid double value.
 * @param msg A custom message to prompt the user for input.
 * @return The user-provided double-precision floating-point value within the specified range.
 */
double getDouble(double minValue, double maxValue, char *msg);

/**
 * @brief This function prompts the user to input a single character and displays a custom message.
 * @param msg A custom message to prompt the user for input.
 * @return The user-provided character.
 */
char getChar(char *msg);

/**
 * @brief This function reads a string of characters from the user with a specified maximum length and displays a custom message.
 * @param string A character array to store the user-provided string.
 * @param length The maximum number of characters that can be read (including null terminator).
 * @param msg A custom message to prompt the user for input.
 * @return This function does not return a value. It populates the string parameter with the user's input.
 */
void readString(char *string, unsigned int length, char *msg);

#ifdef __cplusplus
}
#endif

#endif /* INPUT_H */


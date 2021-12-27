/**
 * @file inputs.h
 * File containing functions which communicates with the user.
 */

#ifndef _INPUTS_
#define _INPUTS_

#include <stdbool.h>

/**
 * @enum coder
 * @brief All the choices of coder
 */
typedef enum coder { LZW, HUFFMAN, CODER_SIZE } coder;

/**
 * @fn bool check_filename(const char *filename)
 * @brief check if a file exists
 * @param filename name of the file to check
 * @return bool
 * @retval true if the file exists
 * @retval false if the file does not exist
 */
bool check_filename(const char *filename);

/**
 * @fn char* choiceOfFile()
 * @brief choice of a file
 * ask the user to choose a file from a preselected list
 * @return char*
 * @retval the name of the file chosen
 */
char* choiceOfFile();

/**
 * @fn char* choiceOfCoder()
 * @brief choice of a coder
 * ask the user to choose a coder from a preselected list
 * @return coder
 * @retval the value of the coder chosen
 */
coder choiceOfCoder();

#endif

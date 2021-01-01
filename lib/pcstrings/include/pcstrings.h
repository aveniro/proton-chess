/**
 * @file pcstrings.h
 * @author Nathan Seymour
 * @brief Portable, cross-platform string operations for
 * proton-chess.
 */

#ifndef PROTON_CHESS_PCSTRINGS_H
#define PROTON_CHESS_PCSTRINGS_H

#include "base_types.h"

/**
 * Checks if a character is uppercase or not, comparing it to the lowercase
 * character 'a' (97).
 * @param char Character to check.
 * @return 1 if the character is uppercase. Else returns 0.
 */
#define is_char_uppercase(char) (((char) >= 'a') ? 0 : 1)

uchar cb_read_uchar_from_string(const char *string, uchar start_index);
uchar cb_uchar_to_string(uchar value, char *buffer, uchar buffer_size);

#endif //PROTON_CHESS_PCSTRINGS_H

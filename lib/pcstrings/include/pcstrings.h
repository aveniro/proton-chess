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
 * Checks if a character is uppercase or not by checking if the value is between
 * 'A' and 'Z'.
 * @param character Character to check.
 * @return 1 if the character is uppercase. Else returns 0.
 */
#define is_char_uppercase(character) (((character) >= 'A' && (character) <= 'Z') ? 1 : 0)

/**
 * Checks if a character is lowercase or not by checking if the value is between
 * 'a' and 'z'.
 * @param character Character to check.
 * @return 1 if the character is lowercase. Else returns 0.
 */
#define is_char_lowercase(character) (((character) >= 'a' && (character) <= 'z') ? 1 : 0)

/**
 * Checks if a character is a digit or not.
 * @param character Character to check.
 * @return 1 if the character is a digit. Else returns 0.
 */
#define is_char_digit(character) (((character) >= '0' && (character) <= '9') ? 1 : 0)

uchar cb_read_uchar_from_string(const char *string, uchar start_index);
uchar cb_uchar_to_string(uchar value, char *buffer, uchar buffer_size);

#endif //PROTON_CHESS_PCSTRINGS_H

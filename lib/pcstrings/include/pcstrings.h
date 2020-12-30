/**
 * @file pcstrings.h
 * @author Nathan Seymour
 * @brief Portable, cross-platform string operations for
 * proton-chess.
 */

#ifndef PROTON_CHESS_PCSTRINGS_H
#define PROTON_CHESS_PCSTRINGS_H

#include "base_types.h"

uchar cb_read_uchar_from_string(const char *string, uchar start_index);
uchar cb_uchar_to_string(uchar value, char *buffer, uchar buffer_size);

#endif //PROTON_CHESS_PCSTRINGS_H

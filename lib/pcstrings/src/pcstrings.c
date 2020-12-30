/**
 * @file stringutils.c
 * @author Nathan Seymour
 * @brief Portable utilities for working with strings.
 */

#include "pcmath.h"
#include "chess.h"

/**
 * Read in a uchar number from a string, starting at a specific
 * index, and return it.
 * @param string String to scan the number from.
 * @param start_index Index at which to start looking.
 * @return Number found in the string. Zero is returned if no number is
 * found.
 */
uchar cb_read_uchar_from_string(const char *string, uchar start_index)
{
    uchar last_string_char_index = start_index;
    uchar number = 0;

    // Scan to the end of the number in the string
    for(; string[last_string_char_index] >= '0' && string[last_string_char_index] <= '9'; last_string_char_index++);
    last_string_char_index--;

    /*
     * Start from the back, and multiply each number by its positional value
     * and add the result to number.
     */
    for(char i = last_string_char_index; i >= start_index; i--)
    {
        number += (uchar)cb_single_char_to_int(string[i]) * (uchar)pcpow(10, last_string_char_index - i);
    }

    return number;
}

uchar cb_uchar_to_string(uchar value, char *buffer, uchar buffer_size)
{
    uchar chars_used = 0;
    uchar number = 0;

    for(uchar i = 2; i != 255 && i <= buffer_size; i--)
    {
        uchar positional_value = 0;
        for(; number + (positional_value * pcpow(10, i)) <= value; positional_value++);
        positional_value--;
        number += positional_value * (uchar)pcpow(10, i);

        if(positional_value > 0)
        {
            buffer[chars_used] = (char)(positional_value + 48);
            chars_used++;
        }
    }

    if(chars_used == 0)
    {
        buffer[chars_used] = '0';
        chars_used++;
    }

    buffer[chars_used] = '\0';
    chars_used++;

    return chars_used;
}
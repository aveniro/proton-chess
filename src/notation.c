/**
 * @file notation.c
 * @author Nathan Seymour
 * @brief Tools for parsing chess algebraic notation.
 */

#include "chess.h"
#include "notation.h"
#include "pcstrings.h"

/**
 * Parse chess algebraic notation for a certain board and returns the
 * move object.
 *
 * NOTE: This function ignores all annotations.
 * @param board Board to calculate notation moves from.
 * @param notation The chess algebraic notation to calculate. One move at a time.
 * Annotations will be ignored. Move number will be ignored.
 * @return Move object to be used with proton-chess movement tools.
 */
cb_move cb_parse_notation(chess_board *board, const char *notation) {
    // Move that will be returned
    cb_move move;

    /*
     * In the case of ambiguity (for example two bishops can move to the same
     * square), the file of the piece is noted that is being moved to the selected
     * square. This is the file that is stored here, if needed.
     */
    uchar from_file = '\0';

    /*
     * In rare cases, two pieces can be on the same file and be able to move to the same
     * square.
     *
     * See "k7/5n2/3R4/5n2/8/8/K7/8 b - - 1 1" - Both black knights are able to take the
     * Rook on d6.
     *
     * In this case, the rank of the moved piece is noted. That is stored here.
     */
    uchar from_rank = 0;

    /*
     * Default to PAWN because if a piece is not specifically mentioned in the notation,
     * it must be a pawn. This saves us code while parsing.
     */
    uchar moved_piece = PAWN;

    uchar to_file;
    uchar to_rank;

    // Loop over the notation until the null terminator
    for (uchar i = 0; notation[i] != '\0'; i++)
    {
        // If the character is uppercase, then it must be the piece that is being moved.
        if(is_char_uppercase(notation[i]))
        {
            moved_piece = cb_lookup_table[notation[i]];
        }
        // Check to see if character is lowercase. If so, it must be a file.
        else if(is_char_lowercase(notation[i]))
        {
            /*
             * For our intents and purposes, we really don't care whether a move
             * takes a piece or not.
             */
            if(notation[i] == 'x')
            {
                continue;
            }

            /*
             * If the previous character was uppercase, then it was a piece definition, and
             * the following number is specifying the rank that it was on.
             */
            if(is_char_uppercase(notation[i - 1]) && i > 0)
            {
                from_file = notation[i];
            }
            /*
             * Otherwise it must be part of the algebraic notation that notes the square that
             * the piece moved to.
             */
            else
            {
                to_file = notation[i];
            }
        }
        // Check to see if the character is a number. If so, it must be a rank.
        else if(is_char_digit(notation[i]))
        {
            /*
             * If the previous character was uppercase, then it was a piece definition, and
             * the following number is specifying the rank that it was on.
             */
            if(is_char_uppercase(notation[i - 1]) && i > 0)
            {
                from_rank = cb_single_char_to_int(notation[i]);
            }
            /*
             * Otherwise it must be part of the algebraic notation that notes the square that
             * the piece moved to.
             */
            else
            {
                to_rank = cb_single_char_to_int(notation[i]);
            }
        }
    }

    return move;
}
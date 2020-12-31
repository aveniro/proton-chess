/**
 * @file evaluation.c
 * @author Nathan Seymour
 * @brief Tools for evaluating advantage in chess positions.
 */

#include "chess.h"
#include "evaluation.h"

/**
 * Calculate the piece point value of white and black in a chess
 * position.
 * @param board Board to evaluation.
 * @param evaluation Pointer to evaluation object to modify.
 */
void cb_board_point_evaluation(chess_board *board, cb_board_evaluation *evaluation)
{
    for(uchar rank = 1; rank <= 8; rank++)
    {
        for(uchar file = 'A'; file <= 'H'; file++)
        {
            uchar piece = cb_get_board_value_at(board, file, rank);
            uchar piece_value = cb_piece_values[piece & COLOR_MASK];

            if(piece & BLACK)
            {
                evaluation->black_points += piece_value;
            }
            else
            {
                evaluation->white_points += piece_value;
            }
        }
    }
}
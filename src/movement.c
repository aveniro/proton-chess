/**
 * @file movement.c
 * @author Nathan Seymour
 * @brief Tools for moving pieces on a chess board
 */

#include "chess.h"
#include "movement.h"

/**
 * Perform a movement on the chess board WITHOUT checking the
 * legality of the move to be made.
 * @param board Board on which to perform the movement.
 * @param move Move object with to and from square index squares.
 */
void cb_perform_movement(chess_board *board, cb_move *move)
{
    // Get piece value that is being moved
    uchar moved_piece_value = cb_get_board_value_at_square_index(board, move->from_square_index);

    // Set the old square to empty
    cb_set_board_value_at_square_index(board, move->from_square_index, EMPTY_SQUARE);

    /* Put the piece on the new square
     * If there was already a piece there, it's effectively removed from the board
     * as if it was taken in the game.
     */
    cb_set_board_value_at_square_index(board, move->to_square_index, moved_piece_value);
}

uchar cb_find_movement_source_square_index(cb_move *move, uchar piece_value)
{

}
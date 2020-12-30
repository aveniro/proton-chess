/**
 * @file chess.c
 * @author Nathan Seymour
 * @brief Basic chess board creation and management functions.
 */

#include <stdlib.h>
#include <string.h>
#include "chess.h"

/**
 * Takes a coordinate index position and returns the notation
 * for the particular square.
 * @param coordinate_index Index of position to get notation of.
 * @return Null-terminated length 3 string of chess notation
 * for the particular square. Ex. "e2", "b8", etc.
 */
char *cb_coordinate_index_to_notation(uchar coordinate_index)
{
    static char notation[3];

    uchar rank_id = coordinate_index / 8;
    uchar file_id = coordinate_index % 8;

    notation[0] = cb_file(file_id);
    notation[1] = cb_single_int_to_char(cb_rank(rank_id));
    notation[2] = '\0';

    return notation;
}

/**
 * Retrieves the piece value at the given board coordinates.
 * @param board Pointer to chess board.
 * @param file Letter notation chess board file. 'A', 'B', 'C', etc.
 * @param rank Chess rank as a number.
 * @return The piece value at the given coordinates.
 */
uchar cb_get_board_value_at(chess_board *board, uchar file, uchar rank)
{
    uchar file_id = cb_file_id(file);
    uchar rank_id = cb_rank_id(rank);

    /*
     * The board is an array of bytes,
     * which in our case is then a 1D array of the chess board
     * as pairs of squares. This will allow us to select and replace
     * the concerned square.
     */
    uchar concerned_byte = board->board[cb_container_index(file_id, rank_id)];

    /*
     * The piece values are stored in four bits on either side of a
     * single byte. So we are determining if we need to put the new
     * piece value into the left or the right side of that byte. We
     * do this by taking mod 2 of the file id. 0 is left, and 1 is right.
     *
     * Left side
     */
    if(file_id % 2 == 0)
    {
        /*
         * Then we can return the left side by shifting it into the right.
         */
        return concerned_byte >> 4;
    }
    // Right side
    else
    {
        /*
         * Then we can return the right side by applying the mask 0xF,
         * which is equivalent to 0b0000 1111.
         */
        return concerned_byte & 0xF;
    }
}

/**
 * Set the piece value of the specified square.
 * @param board Pointer to chess board.
 * @param file Letter notation chess board file. 'A', 'B', 'C', etc.
 * @param rank Chess rank as a number.
 * @param piece_value Bitwise-OR'd piece and color value. Ex: BLACK | ROOK.
 */
void cb_set_board_value_at(chess_board *board, uchar file, uchar rank, uchar piece_value)
{
    uchar file_id = cb_file_id(file);
    uchar rank_id = cb_rank_id(rank);

    /*
     * The board is an array of bytes,
     * which in our case is then a 1D array of the chess board
     * as pairs of squares. This will allow us to select and replace
     * the concerned square.
     */
    uchar concerned_byte = board->board[cb_container_index(file_id, rank_id)];

    /*
     * The piece values are stored in four bits on either side of a
     * single byte. So we are determining if we need to put the new
     * piece value into the left or the right side of that byte. We
     * do this by taking mod 2 of the file id. 0 is left, and 1 is right.
     *
     * Left side
     */
    if(file_id % 2 == 0)
    {
        /*
         * First we bitshift out the side that we don't want.
         * In this case that is the right side.
         */
        concerned_byte <<= 4;
        concerned_byte >>= 4;

        /*
         * Now we can shift the new value to the left and bitwise-OR
         * the two values together.
         */
        concerned_byte |= (piece_value << 4);
    }
    // Right side
    else
    {
        /*
         * First we bitshift out the side that we don't want.
         * In this case that is the left side.
         */
        concerned_byte >>= 4;
        concerned_byte <<= 4;

        /*
         * Now we can bitwise-OR the two values together. No need to
         * shift, because the value is already on the right side.
         */
        concerned_byte |= piece_value;
    }

    /*
     * Now we can set the new calculated square-pair value
     */
    board->board[cb_container_index(file_id, rank_id)] = concerned_byte;
}

/**
 * Initialize a chess board to a standard game on turn 1. White to move.
 * Equivalent of FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1".
 * @param board Pointer to board to initialize.
 */
void cb_initialize_game(chess_board *board)
{
    /*
     * Copy the pre-made initial chess position into the chess board.
     * We could do this by using the FEN extensions, but this is faster,
     * and I would like to keep the FEN extensions optional to reduce
     * binary size for certain embedded applications.
     */
    memcpy(board->board, cb_initial_chess_position, 32);

    // Set other standard values.
    board->move_counter = 0;
    board->halfmove_clock = 0;
    board->castling_rights = CASTLE_RIGHTS_ALL;
    board->ep_target_square_index = -1;
}

/**
 * Allocate and initialize a new chess board. IMPORTANT: Memory is allocated in this function...
 * you MUST call cb_free_chess_board when you are done with it to avoid memory leaks.
 * @return New chess board.
 */
chess_board *cb_new_chess_board()
{
    chess_board *board = malloc(sizeof(chess_board));

    // Initialize values
    board->move_counter = 0;
    board->halfmove_clock = 0;
    board->castling_rights = CASTLE_RIGHTS_NONE;
    board->ep_target_square_index = -1;

    return board;
}

/**
 * Free chess board memory when you are done with it.
 * @param board Board to free.
 */
void cb_free_chess_board(chess_board *board)
{
    free(board);
}
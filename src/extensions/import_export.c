/**
 * @file import_export.c
 * @author Nathan Seymour
 * @brief Utilities for importing and exporting chess boards
 * as binary files.
 */

#include <stdio.h>
#include "chess.h"

/**
 * Write the binary contents of a chess board to the file at the provided
 * path. The entire chess position is saved. The position can then be reloaded
 * using cb_read_board_state_from_file or cb_import_board_from_file.
 *
 * '.pcgpf' - DOT PROTON CHESS GAME POSITION FILE is the preferred extension.
 *
 * If you would like to save the contents of a chess board not to a file, but
 * somewhere else, you must simply copy the structure from memory.
 * @param board Pointer to the board to save.
 * @param path Path to save the chess position to.
 */
void cb_write_board_to_file(chess_board *board, const char *path)
{
    FILE *file = fopen(path, "wb");

    fwrite(board, sizeof(chess_board), 1, file);

    fclose(file);
}

/**
 * Read the state of a chess board from a file into an already existing
 * chess board object.
 *
 * NOTE: This function ONLY supports the binary format exported by
 * proton chess using cb_write_board_to_file and should NOT be used to load
 * FEN or PGN strings.
 *
 * '.pcgpf' - DOT PROTON CHESS GAME POSITION FILE is the preferred extension.
 *
 * To create a new chess board from a file, use the helper function
 * cb_import_board_from_file.
 * @param board Pointer to board object to load state into.
 * @param path Path to '.pcgpf' file to load the position from.
 */
void cb_read_board_state_from_file(chess_board *board, const char *path)
{
    FILE *file = fopen(path, "rb");

    fread(board, sizeof(chess_board), 1, file);

    fclose(file);
}

/**
 * Import a chess board from a '.pcgpf' file, creating a new chess board
 * object.
 *
 * NOTE: This function ONLY supports the binary format exported by
 * proton chess using cb_write_board_to_file and should NOT be used to load
 * FEN or PGN strings.
 *
 * IMPORTANT: cb_free_chess_board must be called on the pointer returned by
 * this function when you are done with it to avoid memory leaks!
 * @param path Path to load the proton chess board state from.
 * @return Pointer to a new chess board object, initialized with the new board data.
 */
chess_board *cb_import_board_from_file(const char *path)
{
    chess_board *board = cb_new_chess_board();

    cb_read_board_state_from_file(board, path);

    return board;
}
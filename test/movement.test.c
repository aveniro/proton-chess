/**
 * @file movement.test.c
 * @author Nathan Seymour
 * @brief Tests for proton-chess movement tools.
 */

#include "chess.h"
#include "movement.h"
#include "scpunitc.h"

TEST(cb_perform_movement)
{
    chess_board *board = cb_new_chess_board();
    cb_initialize_game(board);

    cb_move movement;
    movement.from_square_index = cb_square_index(cb_file_id('A'), cb_rank_id(2));
    movement.to_square_index = cb_square_index(cb_file_id('A'), cb_rank_id(3));

    cb_perform_movement(board, &movement);

    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'A', 2), EMPTY_SQUARE, "Square moved from should be empty.");
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'A', 3), WHITE | PAWN, "Pawn should have advanced to A2.");

    movement.from_square_index = cb_square_index(cb_file_id('D'), cb_rank_id(7));
    movement.to_square_index = cb_square_index(cb_file_id('D'), cb_rank_id(6));

    cb_perform_movement(board, &movement);

    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'D', 7), EMPTY_SQUARE, "Square moved from should be empty.");
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'D', 6), BLACK | PAWN, "Pawn should have advanced to D6.");

    cb_free_chess_board(board);
}

TEST_SUITE(Movement)
{
    ADD_TEST(cb_perform_movement)
}
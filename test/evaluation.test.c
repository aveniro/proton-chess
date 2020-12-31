/**
 * @file evaluation.test.c
 * @author Nathan Seymour
 * @brief Unit tests for protonchess advantage evaluation functions.
 */

#include "chess.h"
#include "evaluation.h"
#include "scpunitc.h"

TEST(cb_board_point_evaluation)
{
    chess_board *board = cb_new_chess_board();
    cb_initialize_game(board);

    cb_board_evaluation expected_values;
    expected_values.white_points += 8 * cb_piece_values[PAWN];
    expected_values.white_points += 2 * cb_piece_values[ROOK];
    expected_values.white_points += 2 * cb_piece_values[KNIGHT];
    expected_values.white_points += 2 * cb_piece_values[BISHOP];
    expected_values.white_points += 1 * cb_piece_values[KING];
    expected_values.white_points += 1 * cb_piece_values[QUEEN];

    expected_values.black_points = expected_values.white_points;

    cb_board_evaluation produced_values;
    cb_board_point_evaluation(board, &produced_values);

    ASSERT_EQ_MSG(produced_values.white_points, expected_values.white_points, "White point values should be the same.");
    ASSERT_EQ_MSG(produced_values.black_points, expected_values.black_points, "Black point values should be the same.");

    cb_free_chess_board(board);
}

TEST_SUITE(Evaluation)
{
    ADD_TEST(cb_board_point_evaluation);
}
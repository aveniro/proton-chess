/**
 * @file chess.test.c
 * @author Nathan Seymour
 * @brief Tests for the core functions of the proton-chess
 * library.
 */

#include <scpunitc.h>
#include <string.h>
#include "chess.h"

TEST(cb_get_board_value_at)
{
    chess_board *board = cb_new_chess_board();
    cb_initialize_game(board);

    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'A', 1), WHITE | ROOK, "There should be a white rook at A1.");
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'B', 1), WHITE | KNIGHT, "There should be a white knight at B1.");

    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'E', 8), BLACK | KING, "There should be a black king at E8.");
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'H', 8), BLACK | ROOK, "There should be a black rook at H8.");

    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'F', 4), EMPTY_SQUARE, "There should be an empty square at F4.");

    cb_free_chess_board(board);
}

TEST(cb_set_board_value_at)
{
    chess_board *board = cb_new_chess_board();
    cb_initialize_game(board);

    cb_set_board_value_at(board, 'A', 1, BLACK | KING);
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'A', 1), BLACK | KING, "There should be a black king at A1.");

    cb_set_board_value_at(board, 'D', 7, WHITE | KNIGHT);
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'D', 7), WHITE | KNIGHT, "There should be a white knight at D7.");

    cb_set_board_value_at(board, 'H', 4, EMPTY_SQUARE);
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'H', 4), EMPTY_SQUARE, "There should be an empty square at H4.");

    cb_free_chess_board(board);
}

TEST(initialize_game)
{
    chess_board *board = cb_new_chess_board();
    cb_initialize_game(board);

    ASSERT_EQ_MSG(memcmp(board->board, cb_initial_chess_position, 32), 0, "Initial chess position should be correctly set.");
    ASSERT_EQ_MSG(board->move_counter, 0, "Move counter should be 0.");
    ASSERT_EQ_MSG(board->halfmove_clock, 0, "Halfmove clock should be 0.");
    ASSERT_EQ_MSG(board->castling_rights, CASTLE_RIGHTS_ALL, "Castling rights should be set to all.");
    ASSERT_EQ_MSG(board->ep_target_square_index, (uchar)-1, "There should be no en passant target square.");

    cb_free_chess_board(board);
}

TEST(cb_coordinate_index_to_notation)
{
    ASSERT_STR_EQ_MSG(cb_coordinate_index_to_notation(0), "a1", "Coordinate 0 should be a1.");
    ASSERT_STR_EQ_MSG(cb_coordinate_index_to_notation(46), "g6", "Coordinate 46 should be g6.");
    ASSERT_STR_EQ_MSG(cb_coordinate_index_to_notation(59), "d8", "Coordinate 59 should be d8.");
    ASSERT_STR_EQ_MSG(cb_coordinate_index_to_notation(33), "b5", "Coordinate 33 should be b5.");
    ASSERT_STR_EQ_MSG(cb_coordinate_index_to_notation(30), "g4", "Coordinate 30 should be g4.");
    ASSERT_STR_EQ_MSG(cb_coordinate_index_to_notation(47), "h6", "Coordinate 47 should be h6.");
}

TEST(cb_read_uchar_from_string)
{
    const char *test_string_1 = "100";
    ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_1, 0), 100, "Value should be 100.");

    const char *test_string_2 = "   211";
    ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_2, 3), 211, "Value should be 211.");

    const char *test_string_3 = "Agent 007, you are requested in the queen's office.";
    ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_3, 7), 7, "Value should be 7.");

    const char *test_string_4 = "28";
    ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_4, 0), 28, "Value should be 28.");

    const char *test_string_5 = "22";
    ASSERT_EQ_MSG(cb_read_uchar_from_string(test_string_5, 0), 22, "Value should be 22.");
}

TEST(cb_uchar_to_string)
{
    char string_buffer[4];

    cb_uchar_to_string(214, string_buffer, 4);
    ASSERT_STR_EQ_MSG(string_buffer, "214", "Value should be 214.");

    cb_uchar_to_string(0, string_buffer, 4);
    ASSERT_STR_EQ_MSG(string_buffer, "0", "Value should be 0.");

    cb_uchar_to_string(55, string_buffer, 4);
    ASSERT_STR_EQ_MSG(string_buffer, "55", "Value should be 55.");

    cb_uchar_to_string(178, string_buffer, 4);
    ASSERT_STR_EQ_MSG(string_buffer, "178", "Value should be 178.");

    cb_uchar_to_string(28, string_buffer, 4);
    ASSERT_STR_EQ_MSG(string_buffer, "28", "Value should be 28.");
}

TEST_SUITE(ProtonChessMain)
{
    ADD_TEST(initialize_game);
    ADD_TEST(cb_get_board_value_at);
    ADD_TEST(cb_set_board_value_at);
    ADD_TEST(cb_coordinate_index_to_notation);
}

TEST_SUITE(StringUtils)
{
    ADD_TEST(cb_read_uchar_from_string);
    ADD_TEST(cb_uchar_to_string);
}

int main()
{
    RUN_SUITE(ProtonChessMain);
    RUN_SUITE(StringUtils);

    return _has_error;
}
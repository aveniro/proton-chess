/**
 * @file fen.test.c
 * @author Nathan Seymour
 * @brief Tests for the FEN extensions of proton-chess.
 */

#include "scpunitc.h"
#include "chess.h"

TEST(cb_parse_fen)
{
    chess_board *board = cb_new_chess_board();
    cb_initialize_game(board);

    cb_parse_fen(board, "r1bqkbnr/pppp2pp/5p2/4pn2/2B1P1P1/8/PPPP1P1P/RNB1K1NR w KQkq - 0 6");

    ASSERT_EQ_MSG(board->move_counter, 12, "The move counter should be equal to 12.");
    ASSERT_EQ_MSG(board->castling_rights, CASTLE_RIGHTS_ALL, "Castling rights should be set to all.");
    ASSERT_EQ_MSG(board->ep_target_square_index, (uchar)-1, "The en passant target square should be empty.");
    ASSERT_EQ_MSG(board->ep_target_square_index, (uchar)-1, "The en passant target square should be empty.");

    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'A', 1), WHITE | ROOK, "There should be a white rook at A1.");
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'C', 4), WHITE | BISHOP, "There should be a white bishop at C4.");
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'D', 7), BLACK | PAWN, "There should be a black pawn at D7.");
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'H', 8), BLACK | ROOK, "There should be a black rook at H8.");
    ASSERT_EQ_MSG(cb_get_board_value_at(board, 'B', 8), EMPTY_SQUARE, "There should be an emtpy square at B8.");

    cb_free_chess_board(board);
}

TEST(cb_generate_fen)
{
    chess_board *board = cb_new_chess_board();
    cb_initialize_game(board);

    char fen_buffer[CB_FEN_NOTATION_LENGTH];

    const char *fen_strings[] = {
            "r1bqkbnr/pppp2pp/5p2/4pn2/2B1P1P1/8/PPPP1P1P/RNB1K1NR w KQkq - 0 6",
            "2kr1bnr/pp6/2p5/1P2P1p1/q1P2p2/PN1p3P/3Q4/R5K1 b - - 0 22",
            "2k5/pp4pp/8/2p2n2/8/1P2QN2/P3NPPK/1q6 w - - 6 26",
            "8/8/p2kp3/1p2p1p1/1Pp1P2p/P1PnNP1P/6P1/3K4 b - - 7 35",
            "r2q4/1pp2rkp/3p1ppN/pP2p3/3nP3/3P3Q/P4PPP/RNB2RK1 w - a6 0 18"
    };

    for(uchar i = 0; i < (sizeof(fen_strings) / sizeof(*fen_strings)); i++)
    {
        cb_parse_fen(board, fen_strings[i]);
        cb_generate_fen(board, fen_buffer, CB_FEN_NOTATION_LENGTH);

        ASSERT_STR_EQ_MSG(fen_buffer, fen_strings[i], "FEN strings should match exactly.");
    }

    cb_free_chess_board(board);
}

TEST_SUITE(FENExtensions)
{
    ADD_TEST(cb_parse_fen);
    ADD_TEST(cb_generate_fen);
}
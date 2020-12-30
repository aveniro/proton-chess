/**
 * @file fen.c
 * @author Nathan Seymour
 * @brief Utilities for parsing and generating Forsyth-Edwards
 * Notation.
 */

#include <string.h>
#include "chess.h"
#include "pcstrings.h"

/**
 * Parse Forsyth-Edwards notation into an initialized chess board.
 * @param board Pointer to a chess board object.
 * @param fen String of standard FEN notation.
 */
void cb_parse_fen(chess_board *board, const char *fen)
{
    uchar fen_length = (uchar)strlen(fen);
    uchar fen_index = 0;
    uchar file = 'A';
    uchar rank = 8;

    // Piece positions
    for(; fen_index < fen_length; fen_index++)
    {
        if(fen[fen_index] == '/')
        {
            rank--;
            file = 'A';
        }
        else if(fen[fen_index] == ' ')
        {
            break;
        }
        else if(fen[fen_index] >= 48 && fen[fen_index] <= 57)
        {
            uchar empty_squares = cb_single_char_to_int(fen[fen_index]);
            for(uchar i = 0; i < empty_squares; i++)
            {
                cb_set_board_value_at(board, file, rank, EMPTY_SQUARE);
                file++;
            }
        }
        else
        {
            cb_set_board_value_at(board, file, rank, cb_lookup_table[fen[fen_index]]);
            file++;
        }
    }

    // Current player to move
    fen_index++;
    board->move_counter = 0;
    if(fen[fen_index] == 'b')
    {
        board->move_counter++;
    }

    // Castling rights
    fen_index += 2;
    board->castling_rights = CASTLE_RIGHTS_NONE;
    for(; fen_index < fen_length; fen_index++)
    {
        if(fen[fen_index] == 'K')
        {
            board->castling_rights |= CASTLE_RIGHTS_KINGSIDE_WHITE;
        }
        else if(fen[fen_index] == 'Q')
        {
            board->castling_rights |= CASTLE_RIGHTS_QUEENSIDE_WHITE;
        }
        else if(fen[fen_index] == 'k')
        {
            board->castling_rights |= CASTLE_RIGHTS_KINGSIDE_BLACK;
        }
        else if(fen[fen_index] == 'q')
        {
            board->castling_rights |= CASTLE_RIGHTS_QUEENSIDE_BLACK;
        }
        else if(fen[fen_index] == ' ')
        {
            break;
        }
    }

    // En passant square
    fen_index++;
    if(fen[fen_index] == '-')
    {
        board->ep_target_square_index = -1;
    }
    else
    {
        uchar file_id = cb_file_id(fen[fen_index]);
        uchar rank_id = cb_rank_id(cb_single_char_to_int(fen[++fen_index]));
        board->ep_target_square_index = cb_square_index(file_id, rank_id);
    }

    // Halfmove clock
    fen_index += 2;
    board->halfmove_clock = cb_read_uchar_from_string(fen, fen_index);

    // Move counter
    for(; fen[fen_index] != ' '; fen_index++); // scan to move counter
    fen_index++;
    board->move_counter += cb_read_uchar_from_string(fen, fen_index) * 2;
}

/**
 * Generate Forsyth-Edwards notation as a string from the position on a
 * current board into a user supplied buffer.
 * @param board Pointer to the board.
 * @param buffer Character buffer to copy the FEN string into.
 * @param buffer_size Size of the buffer provided. Must be at least the size
 * of CB_FEN_NOTATION_LENGTH.
 */
void cb_generate_fen(chess_board *board, char *buffer, int buffer_size)
{
    // Piece positions
    uchar empty_square_count = 0;
    uchar fen_index = 0;
    for(uchar rank = 8; rank >= 1; rank--)
    {
        for(uchar file = 'A'; file <= 'H'; file++)
        {
            uchar piece_value = cb_get_board_value_at(board, file, rank);

            if(piece_value == 0)
            {
                empty_square_count++;
            }
            else
            {
                if(empty_square_count != 0)
                {
                    buffer[fen_index] = (char)(empty_square_count + 48);
                    fen_index++;
                    empty_square_count = 0;
                }

                buffer[fen_index] = cb_lookup_table[piece_value];
                fen_index++;
            }
        }

        if(empty_square_count != 0)
        {
            buffer[fen_index] = (char)(empty_square_count + 48);
            fen_index++;
            empty_square_count = 0;
        }

        if(rank != 1)
        {
            buffer[fen_index] = '/';
            fen_index++;
        }
        else {
            // Add space
            buffer[fen_index] = ' ';
            fen_index++;
        }
    }

    // Current player to move
    if(board->move_counter % 2 == 0)
    {
        buffer[fen_index] = 'w';
    }
    else
    {
        buffer[fen_index] = 'b';
    }
    fen_index++;
    buffer[fen_index] = ' ';
    fen_index++;

    // Castling rights
    if(board->castling_rights == CASTLE_RIGHTS_NONE)
    {
        buffer[fen_index] = '-';
        fen_index++;
    }
    else
    {
        if(board->castling_rights & CASTLE_RIGHTS_KINGSIDE_WHITE)
        {
            buffer[fen_index] = 'K';
            fen_index++;
        }

        if(board->castling_rights & CASTLE_RIGHTS_QUEENSIDE_WHITE)
        {
            buffer[fen_index] = 'Q';
            fen_index++;
        }

        if(board->castling_rights & CASTLE_RIGHTS_KINGSIDE_BLACK)
        {
            buffer[fen_index] = 'k';
            fen_index++;
        }

        if(board->castling_rights & CASTLE_RIGHTS_QUEENSIDE_BLACK)
        {
            buffer[fen_index] = 'q';
            fen_index++;
        }
    }
    buffer[fen_index] = ' ';
    fen_index++;

    // En passant square
    if(board->ep_target_square_index != (uchar)-1)
    {
        memcpy(buffer + fen_index, cb_coordinate_index_to_notation(board->ep_target_square_index), 2);
        fen_index += 2;
    }
    else
    {
        buffer[fen_index] = '-';
        fen_index++;
    }
    buffer[fen_index] = ' ';
    fen_index++;

    // Halfmove clock
    char move_buffer[4];
    uchar chars_used = cb_uchar_to_string(board->halfmove_clock, move_buffer, 4);
    memcpy(buffer + fen_index, move_buffer, chars_used);
    fen_index += chars_used - 1;

    buffer[fen_index] = ' ';
    fen_index++;

    // Move counter
    chars_used = cb_uchar_to_string( board->move_counter / 2, move_buffer, 4);
    memcpy(buffer + fen_index, move_buffer, chars_used);
    fen_index += chars_used - 1;
}
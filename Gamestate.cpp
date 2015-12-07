#include <algorithm>
#include "Gamestate.h"

namespace transforms{
    shape_t transpose(const shape_t&);
}

Piece::Piece(shape_t _shape)
{
    shape = _shape;
    width = shape[0].size();
    height = shape.size();
    read_shape = &shape;
    if (width != height) std::runtime_error("Piece must have equal width and height");
}

void Piece::rotate_left() // Take transpose and invert rows
{
    shape = transforms::transpose(shape);
    std::reverse(shape.begin(), shape.end());
}

void Piece::rotate_right() // Take transpose and invert columns
{
    shape = transforms::transpose(shape);
    for (auto &&row : shape)
    {
        std::reverse(row.begin(), row.end());
    }
}

void Gamestate::move_down()
{
    current_piece_loc[1] = current_piece_loc[1] + 1;
}

Gamestate Gamestate::pass()
{
    for (int row_num = 0; row_num < current_piece.width; ++row_num)
    {
        for (int col_num = 0; col_num < current_piece.height; ++col_num)
        {
            if ((*current_piece.read_shape)[row_num][col_num] && board[row_num][col_num + 1]) // On top of another piece
            {
                return stamp_current_piece();
            }
        }
    }
    Gamestate return_val = *this;
    return_val.move_down();
    return return_val;
}

Gamestate Gamestate::move_left()
{
    bool barrier = false;
    for (int row_num = 0; row_num < current_piece.width; ++row_num)
    {
        for (int col_num = 0; col_num < current_piece.height; ++col_num)
        {
            if (board[row_num + 1 + current_piece_loc[0]][col_num + current_piece_loc[1]] && (*read_shape)[row_num][col_num])
            {
                barrier = true;
                break; // Not necessary, but speeds things up
            }
        }
    }
    
    if (barrier)
    {
        return pass();
    }
    else
    {
        Gamestate new_gamestate = *this;
        new_gamestate.current_piece_loc += 1;
    }
}

Gamestate Gamestate::move_right()
{
    bool barrier = false;
    for (int row_num = 0; row_num < current_piece.width; ++row_num)
    {
        for (int col_num = 0; col_num < current_piece.height; ++col_num)
        {
            if (board[row_num + 1 + current_piece_loc[0]][col_num + current_piece_loc[1]] && (*read_shape)[row_num][col_num])
            {
                barrier = true;
                break; // Not necessary, but speeds things up
            }
        }
    }
    
    if (barrier)
    {
        return pass();
    }
    else
    {
        Gamestate new_gamestate = *this;
        new_gamestate.current_piece_loc += 1;
    }
}

Gamestate Gamestate::rotate_left()
{
    Gamestate new_gamestate = *this;
    new_gamestate.current_piece.rotate_left();
    for (int row_num = 0; row_num < new_gamestate.current_piece.width; ++row_num)
    {
        for (int col_num = 0; col_num < new_gamestate.current_piece.height; ++col_num)
        {
            if (board[row_num + new_gamestate.current_piece_loc[0]][col_num + new_gamestate.current_piece_loc[1]]
                && new_gamestate.current_piece[row_num][col_num]) // No room to rotate into
            {
                return pass();
            }
        }
    }
    return new_gamestate;
}

Gamestate Gamestate::rotate_right()
{
    Gamestate new_gamestate = *this;
    new_gamestate.current_piece.rotate_right();
    for (int row_num = 0; row_num < new_gamestate.current_piece.width; ++row_num)
    {
        for (int col_num = 0; col_num < new_gamestate.current_piece.height; ++col_num)
        {
            if (board[row_num + new_gamestate.current_piece_loc[0]][col_num + new_gamestate.current_piece_loc[1]]
                && new_gamestate.current_piece[row_num][col_num]) // No room to rotate into
            {
                return pass();
            }
        }
    }
    return new_gamestate;
}

Gamestate Gamestate::hard_drop()
{
    
}

const shape_t pieces::I = {{false, false, false, false},
                           {true,  true,  true,  true},
                           {false, false, false, false},
                           {false, false, false, false}};

const shape_t pieces::J = {{true,  false, false},
                           {true,  true,  true},
                           {false, false, false}};

const shape_t pieces::L = {{false, false, true},
                           {true,  true,  true},
                           {false, false, false}};

const shape_t pieces::O = {{true,  true},
                           {true,  true}};

const shape_t pieces::S = {{false, true,  true},
                           {true,  true,  false},
                           {false, false, false}};

const shape_t pieces::T = {{false, true,  false},
                           {true,  true,  true},
                           {false, false, false}};

const shape_t pieces::Z = {{true,  true,  false},
                           {false, true,  true},
                           {false, false, false}};

shape_t transforms::transpose(const shape_t &original)
{
    shape_t new_shape;
    for (int row_num = 0; row_num < original.size(); ++row_num)
    {
        for (int col_num = 0; col_num < original.back().size(); ++col_num)
        {
            new_shape[row_num][col_num] = original[col_num][row_num];
        }
    }
    return new_shape;
}
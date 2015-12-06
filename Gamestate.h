// The combination of:  the score
//                      the current piece
//                      ^ that piece's position
//                      the blocks already on the board
//                      the next piece

#ifndef TetrisAI_Gamestate_h
#define TetrisAI_Gamestate_h

#include <vector>

typedef std::vector<std::vector<bool>> shape_t;

class Piece {
    shape_t shape;
    
public:
    Piece(shape_t);
    unsigned int width;
    unsigned int height;
    const shape_t *read_shape;
    void rotate_right();
    void rotate_left();
};

class Gamestate {
    shape_t board; // Should not include the current piece
    Piece current_piece;
    unsigned int current_piece_loc[2];
    Gamestate stamp_current_piece();
    void move_down();
    
public:
    Gamestate();
    Gamestate(const Gamestate&);
    Gamestate pass();
    Gamestate move_left();
    Gamestate move_right();
    Gamestate rotate_left();
    Gamestate rotate_right();
    Gamestate hard_drop();
    std::vector<Gamestate> possible_moves();
    unsigned int points;
};

namespace pieces {
    extern const shape_t I;
    extern const shape_t J;
    extern const shape_t L;
    extern const shape_t O;
    extern const shape_t S;
    extern const shape_t T;
    extern const shape_t Z;
}

#endif

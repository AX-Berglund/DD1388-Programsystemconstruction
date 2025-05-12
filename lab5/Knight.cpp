#include "Knight.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

Knight::Knight(int x_, int y_, bool isWhite_, Type type_, ChessBoard* board_)
    : ChessPiece(x_, y_, isWhite_, type_, board_) {}

Knight::~Knight() {}

char const* Knight::utf_representation() {
    return this->isWhite ? "♘" : "♞";
}

char Knight::latin_representation() {
    return this->isWhite ? 'N' : 'n';
}

int Knight::valid_move(int x_to, int y_to) {
    int delta_x = std::abs(this->x - x_to);
    int delta_y = std::abs(this->y - y_to);

    // Check if the move follows the L-shaped pattern of a knight
    if (delta_x < 3 && delta_y < 3 && delta_x + delta_y == 3) {
        std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);
        
        if (cp_to == NULL) {
            return 1;  // Empty square
        } else if (cp_to->get_color() != this->get_color()) {
            return 2;  // Capture opponent's piece
        }
    }
    
    return 0;  // Invalid move
}

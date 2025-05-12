#include "Bishop.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

Bishop::Bishop(int x_, int y_, bool isWhite_, Type type_, ChessBoard* board_) 
    : ChessPiece(x_, y_, isWhite_, type_, board_) {}

Bishop::~Bishop() {}

char const* Bishop::utf_representation() {
    return this->isWhite ? "♗" : "♝";
}

char Bishop::latin_representation() {
    return this->isWhite ? 'B' : 'b';
}

int Bishop::valid_move(int x_to, int y_to) {
    // Calculate the absolute distance in both directions
    int delta_x = std::abs(this->x - x_to);
    int delta_y = std::abs(this->y - y_to);

    // Bishop must move diagonally (equal x and y distance)
    if (this->x == x_to || this->y == y_to || delta_x != delta_y) {
        return 0;
    }

    // Check if destination square has a piece of the same color
    std::shared_ptr<ChessPiece> target_piece = this->board->get_piece(x_to, y_to);
    if (target_piece != NULL && this->isWhite == target_piece->get_color()) {
        return 0;
    }

    // Check for pieces in the path
    for (int step = 1; step < delta_x; step++) {
        // Determine direction of movement
        int x_step = (x_to > this->x) ? step : -step;
        int y_step = (y_to > this->y) ? step : -step;
        
        // Check if there's a piece in the current step position
        if (this->board->get_piece(this->x + x_step, this->y + y_step) != NULL) {
            return 0;
        }
    }

    // Return 2 for capture, 1 for regular move
    return (target_piece != NULL) ? 2 : 1;
}

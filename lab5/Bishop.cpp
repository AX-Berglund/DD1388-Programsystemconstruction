#include "Bishop.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

Bishop::Bishop(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : ChessPiece(x_, y_, isWhite_, type_, board_) {}
Bishop::~Bishop() {}

char const* Bishop::utf_representation() {
  return this->isWhite ? "♗" : "♝";
}

char Bishop::latin_representation() {
  return this->isWhite ? 'B' : 'b';
}

int Bishop::valid_move(int x_to, int y_to) {
  int del_x = std::abs(this->x - x_to);
  int del_y = std::abs(this->y - y_to);

  if (this->x == x_to || this->y == y_to || del_x != del_y) {
    return 0;
  }

  std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);
  if (cp_to != NULL && this->isWhite == cp_to->get_color()) {
    return 0;
  }
  for (int it = 1; it < del_x; it++) {
    if (x_to > this->x && y_to > this->y) {
      if (this->board->get_piece(this->x + it, this->y + it) != NULL) {
        return 0;
      }
    } else if (x_to < this->x && y_to < this->y) {
      if (this->board->get_piece(this->x - it, this->y - it) != NULL) {
        return 0;
      }
    } else if (x_to > this->x && y_to < this->y) {
      if (this->board->get_piece(this->x + it, this->y - it) != NULL) {
        return 0;
      }
    } else if (x_to < this->x && y_to > this->y) {
      if (this->board->get_piece(this->x - it, this->y + it) != NULL) {
        return 0;
      }
    }
  }

  if (cp_to != NULL) {
    return 2;
  }

  return 1;
}

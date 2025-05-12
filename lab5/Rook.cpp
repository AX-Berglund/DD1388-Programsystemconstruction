#include "Rook.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

#include <cmath>

Rook::Rook(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : ChessPiece(x_, y_, isWhite_, type_, board_) {}
Rook::~Rook() {}

char const* Rook::utf_representation() {
  return this->isWhite ? "♖" : "♜";
}

char Rook::latin_representation() {
  return this->isWhite ? 'R' : 'r';
}

int Rook::valid_move(int x_to, int y_to) {
  if (this->x != x_to && this->y != y_to) {
    return 0;
  }
  if (this->x == x_to && this->y == y_to) {
    return 0;
  }

  std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);
  if (cp_to != NULL && this->isWhite == cp_to->get_color()) {
    return 0;
  }

  int delta_x = std::abs(this->x - x_to);
  int delta_y = std::abs(this->y - y_to);
  if (delta_x == 0) {
    if (y_to > this->y) {
      for (int it = this->y+1; it < y_to; it++) {
        if (this->board->get_piece(x_to, it) != NULL) {
          return 0;
        }
      }
    } else if (this->y > y_to) {
      for (int it = this->y-1; it > y_to; it--) {
        if (this->board->get_piece(x_to, it) != NULL) {
          return 0;
        }
      }
    }
  } else if (delta_y == 0) {
    if (x_to > this->x) {
      for (int it = this->x+1; it < x_to; it++) {
        if (this->board->get_piece(it, y_to) != NULL) {
          return 0;
        }
      }
    } else if (x_to < this->x) {
      for (int it = this->x-1; it > x_to; it--) {
        if (this->board->get_piece(it, y_to) != NULL) {
          return 0;
        }
      }
    }
  }
  if (cp_to != NULL) {
    return 2;
  }

  return 1;
}

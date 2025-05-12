#include "Pawn.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

Pawn::Pawn(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) : ChessPiece(x_, y_, isWhite_, type_, board_) {}
Pawn::~Pawn() {}

char const* Pawn::utf_representation() {
  return this->isWhite ? "♙" : "♟";
}

char Pawn::latin_representation() {
  return this->isWhite ? 'P' : 'p';
}

int Pawn::valid_move(int x_to, int y_to) {
  std::shared_ptr<ChessPiece> cp_to = this->board->get_piece(x_to, y_to);

  if (cp_to != NULL) {
    bool color_to = cp_to->get_color();
  }

  if (this->x == x_to) {
    if (cp_to != NULL) {
      return 0;
    }

    if ((this->isWhite && this->y > y_to) ||
        (!this->isWhite && this->y < y_to)) {
      return 0;
    }

    if ((this->isWhite && y == 1 && (this->y - y_to ) == -2) ||
        (!this->isWhite && y == 6 && (this->y - y_to ) == 2)) {
      if (this->board->get_piece(x_to, y_to-1) == NULL) {
        return 1;
      }
    }

    if ((this->isWhite && (this->y - y_to ) == -1) ||
        (!this->isWhite && (this->y - y_to ) == 1)) {
      return 1;
    }
  } else if (std::abs(this->y - y_to) == 1 && (std::abs(this->x-x_to) == 1) && ((this->isWhite && (this->y - y_to) == -1) || (!this->isWhite && (this->y - y_to ) == 1))) {
      if (cp_to != NULL) {
        if (this->isWhite != cp_to->get_color()) {
          return 2;
        }
      }
  }
  return 0;
}


#include "Queen.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

Queen::Queen(int x_, int y_, bool isWhite_, Type type_,
    ChessBoard* board_) :
  ChessPiece(x_, y_, isWhite_, type_, board_),
  Bishop(x_, y_, isWhite_, type_, board_),
  Rook(x_, y_, isWhite_, type_, board_) {
}
Queen::~Queen() {}

char const* Queen::utf_representation() {
  return this->isWhite ? "♕" : "♛";
}

char Queen::latin_representation() {
  return this->isWhite ? 'Q' : 'q';
}

int Queen::valid_move(int x_to, int y_to) {
  return std::max(Bishop::valid_move(x_to, y_to),
      Rook::valid_move(x_to, y_to));
}

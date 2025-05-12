#ifndef Pawn_H
#define Pawn_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    Pawn(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~Pawn();
};

#endif

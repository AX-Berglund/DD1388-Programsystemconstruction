#ifndef Knight_H
#define Knight_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move( int x_to,  int y_to);

  public:
    Knight(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~Knight();
};

#endif

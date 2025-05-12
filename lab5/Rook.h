#ifndef Rook_H
#define Rook_H

#include "ChessPiece.h"

class Rook : virtual public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    Rook(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~Rook();
};

#endif

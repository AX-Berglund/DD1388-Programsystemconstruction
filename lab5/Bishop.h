#ifndef Bishop_H
#define Bishop_H

#include "ChessPiece.h"

class Bishop : virtual public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    Bishop(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~Bishop();
};

#endif

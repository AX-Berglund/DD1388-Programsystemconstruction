#ifndef King_H
#define King_H

#include "ChessPiece.h"
#include <string>

class King : public ChessPiece {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    King(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~King();
};

#endif

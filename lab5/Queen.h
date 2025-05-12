#ifndef Queen_H
#define Queen_H

#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop, public Rook {
  protected:
    char const* utf_representation();
    char latin_representation();
    int valid_move(int x_to, int y_to);

  public:
    Queen(int x, int y, bool isWhite, Type type, ChessBoard* board);
    virtual ~Queen();
};

#endif

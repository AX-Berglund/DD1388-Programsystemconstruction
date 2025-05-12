#include "ChessBoard.h"
#include "Rook.h"
#include "Bishop.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "ChessPiece.h"
#include "ChessMove.h"

#include "Matrix.h"
#include "Helper.h"

#include <memory>
#include <cmath>

void ChessBoard::move_piece(ChessMove move) {
  std::shared_ptr<ChessPiece> cp = move.piece;

  cp->x = move.x_to;
  cp->y = move.y_to;

  this->state.set_element(0, move.x_to+move.y_to*8, cp);

  this->state.set_element(0, move.x_from+move.y_from*8, NULL);
}

void ChessBoard::rewind_move_piece(ChessMove move,
 std::shared_ptr<ChessPiece> cp_removed_by_move) {
  std::shared_ptr<ChessPiece> cp_to_rewind = move.piece;

  cp_to_rewind->x = move.x_from;
  cp_to_rewind->y = move.y_from;

  this->state.set_element(0, move.x_from+move.y_from*8, cp_to_rewind);

  this->state.set_element(0, move.x_to+move.y_to*8, cp_removed_by_move);
}

void ChessBoard::ai1_make_move(bool isWhite) {

  std::vector<ChessMove> nc_moves = non_capturing_moves(isWhite);
  std::vector<ChessMove> c_moves = capturing_moves(isWhite);

  ChessMove move;
  if (c_moves.size() > 0) {
    move = *select_random_element(c_moves.begin(), c_moves.end());
  } else {
    move = *select_random_element(nc_moves.begin(), nc_moves.end());
  }

  move_piece(move);

  if ((move.piece->type == pawn && move.piece->isWhite && move.y_to == 7) ||
      (move.piece->type == pawn && !move.piece->isWhite && move.y_to == 0)) {
      int num = gen_rand_num(0, 4);
      std::shared_ptr<ChessPiece> cp_new = create_new_piece(move.x_to,
          move.y_to, move.piece->get_color(), Type(num), move.piece->board);
      this->state.set_element(0, move.y_to*8+move.x_to, cp_new);
  }

  switch_turn();
}

void ChessBoard::ai2_make_move(bool isWhite) {

  std::vector<ChessMove> nc_moves = non_capturing_moves(isWhite);
  std::vector<ChessMove> c_moves = capturing_moves(isWhite);

  bool hasMoved = false;
  ChessMove move;
  if (c_moves.size() > 0) {

    for (auto const& m: c_moves) {
      std::shared_ptr<ChessPiece> cp_to = this->get_piece(m.x_to, m.y_to);
      move_piece(m);
      if (capturing_moves(!isWhite).size() != 0) {
        move = m;
        hasMoved = true;
        break;
      } else {
        rewind_move_piece(m, cp_to);
      }
    }
    if (!hasMoved) {
      move = *select_random_element(c_moves.begin(), c_moves.end());
      move_piece(move);
    }

  } else {
    for (auto const& m: nc_moves) {
      std::shared_ptr<ChessPiece> cp_to = this->get_piece(m.x_to, m.y_to);
      move_piece(m);
      if (capturing_moves(!isWhite).size() != 0) {
        move = m;
        hasMoved = true;
        break;
      } else {
        rewind_move_piece(m, cp_to);
      }
    }
    if (!hasMoved) {
      move = *select_random_element(nc_moves.begin(), nc_moves.end());
      move_piece(move);
    }
  }

  if ((move.piece->type == pawn && move.piece->isWhite && move.y_to == 7) ||
      (move.piece->type == pawn && !move.piece->isWhite && move.y_to == 0)) {
    bool hasBeenPromoted = false;
    for (int i = 0; i < 5; i++) {
      std::shared_ptr<ChessPiece> cp_new = create_new_piece(move.x_to,
          move.y_to, move.piece->get_color(), Type(i), move.piece->board);
      if (capturing_moves(!isWhite).size() != 0) {
        this->state.set_element(0, move.y_to*8+move.x_to, cp_new);
        hasBeenPromoted = true;
        break;
      }
    }

    if (!hasBeenPromoted) {
      int num = gen_rand_num(0, 4);
      std::shared_ptr<ChessPiece> cp_new = create_new_piece(move.x_to,
          move.y_to, move.piece->get_color(), Type(num), move.piece->board);
      this->state.set_element(0, move.y_to*8+move.x_to, cp_new);
    }
  }

  switch_turn();
}

std::shared_ptr<ChessPiece> ChessBoard::create_new_piece(int x, int y,
    bool isWhite, int type, ChessBoard* board) {
  std::shared_ptr<ChessPiece> cp;
  switch (type) {
    case king:
        cp = std::make_shared<King>(x, y, isWhite, king, board);
    case queen:
        cp = std::make_shared<Queen>(x, y, isWhite, queen, board);
      break;
    case bishop:
        cp = std::make_shared<Bishop>(x, y, isWhite, bishop, board);
      break;
    case knight:
        cp = std::make_shared<Knight>(x, y, isWhite, knight, board);
      break;
    case rook:
        cp = std::make_shared<Rook>(x, y, isWhite, rook, board);
      break;
  }
  return cp;
}


void ChessBoard::initialise_board(Matrix<std::shared_ptr<ChessPiece> > m) {
  turn = 1;
  state = m;
}

ChessBoard & operator>>(std::istream& is, ChessBoard& board) {
  Matrix<std::shared_ptr<ChessPiece> > m(1, 64);

  char c;
  int cnt = 0;
  c = is.get();
  while (is) {
    if (c == '\n') {
      c = is.get();
    } else {
      int x = cnt % 8;
      int y = std::floor(cnt / 8);
      switch (c) {
        case 'K':
          m.set_element(0, cnt, std::make_shared<King>(
                x, y, true, king, &board));
          break;
        case 'k':
          m.set_element(0, cnt, std::make_shared<King>(
                x, y, false, king, &board));
          break;
        case 'Q':
          m.set_element(0, cnt, std::make_shared<Queen>(
                x, y, true, queen, &board));
          break;
        case 'q':
          m.set_element(0, cnt, std::make_shared<Queen>(
                x, y, false, queen, &board));
          break;
        case 'N':
          m.set_element(0, cnt, std::make_shared<Knight>(
                x, y, true, knight, &board));
          break;
        case 'n':
          m.set_element(0, cnt, std::make_shared<Knight>(
                x, y, false, knight, &board));
          break;
        case 'P':
          m.set_element(0, cnt, std::make_shared<Pawn>(
                x, y, true, pawn, &board));
          break;
        case 'p':
          m.set_element(0, cnt, std::make_shared<Pawn>(
                x, y, false, pawn, &board));
          break;
        case 'B':
          m.set_element(0, cnt, std::make_shared<Bishop>(
                x, y, true, bishop, &board));
          break;
        case 'b':
          m.set_element(0, cnt, std::make_shared<Bishop>(
                x, y, false, bishop, &board));
          break;
        case 'R':
          m.set_element(0, cnt, std::make_shared<Rook>(
                x, y, true, rook, &board));
          break;
        case 'r':
          m.set_element(0, cnt, std::make_shared<Rook>(
                x, y, false, rook, &board));
          break;
        default:
          m.set_element(0, cnt, nullptr);
      }
      cnt++;
      c = is.get();
    }
  }
  if (cnt < 64) {
    std::cout << "Illegal size of input stream!" <<std::endl;
    exit(0);
  }

  board.initialise_board(m);

  return board;
}

void ChessBoard::print_board() {
  std::cout << "\n    ";
  int cnt = 0;
  for (int file = 0; file <= 7; file++)
    std::cout << file << "   ";
  std::cout << std::endl;
  for (int rank=0; rank <= 7; rank++) {
    std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
    std::cout << rank << " ";
    for (char file = 'A'; file <= 'H'; file++) {
      std::cout << '|' << " ";
      if (state.get_element(0, cnt) != NULL) {
        std::cout << state.get_element(0, cnt)->utf_representation();
      } else {
        std::cout << " ";
      }
      cnt ++;
      std::cout << " ";
    }
    std::cout << "|" << std::endl;
  }
  std::cout << "  +---+---+---+---+---+---+---+---+\n" << std::endl;
}


void ChessBoard::switch_turn() {
  turn = !turn;
}

bool ChessBoard::get_turn() {
  return turn;
}

std::shared_ptr<ChessPiece> ChessBoard::get_piece(int x, int y) {
  return state.get_element(0, x+y*8);
}

std::vector<ChessMove> ChessBoard::capturing_moves(bool isWhite) {
  std::vector<ChessMove> capturingMoves;
  int c = 0;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      std::shared_ptr<ChessPiece> cp = this->get_piece(x, y);
      if (cp != NULL && (cp->get_color() == isWhite)) {
        std::vector<ChessMove> moves =
          this->get_piece(x, y)->capturing_moves();
        capturingMoves.insert(capturingMoves.end(), moves.begin(),
            moves.end());
      }
    }
  }
  return capturingMoves;
}

std::vector<ChessMove> ChessBoard::non_capturing_moves(bool isWhite) {
  std::vector<ChessMove> nonCapturingMoves;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
        std::shared_ptr<ChessPiece> cp = this->get_piece(x, y);
        if (cp != NULL && (cp->get_color() == isWhite)) {
          std::vector<ChessMove> moves =
            this->get_piece(x, y)->non_capturing_moves();
          nonCapturingMoves.insert(nonCapturingMoves.end(), moves.begin(),
              moves.end());
      }
    }
  }
  return nonCapturingMoves;
}

std::vector<ChessMove> ChessBoard::possible_moves(bool isWhite) {
  std::vector<ChessMove> possible_moves = non_capturing_moves(isWhite);
  std::vector<ChessMove> c_moves = capturing_moves(isWhite);

  possible_moves.insert(possible_moves.end(), c_moves.begin(), c_moves.end());

  return possible_moves;
}

std::shared_ptr<ChessPiece> ChessBoard::find_king(bool isWhite) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      std::shared_ptr<ChessPiece> cp = this->get_piece(x, y);
      if (cp != NULL) {
        if (cp->get_color() == isWhite && cp->get_type() == king) {
          return cp;
        }
      }
    }
  }
  return nullptr;
}

bool ChessBoard::king_in_check(bool isWhite) {
  std::shared_ptr<ChessPiece> king = find_king(isWhite);
  if (king != NULL) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        std::shared_ptr<ChessPiece> cp = this->get_piece(x, y);
        if (cp != NULL && cp->get_color() != isWhite) {
          if (cp->valid_move(king->x, king->y)) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool ChessBoard::any_valid_move(bool isWhite) {
  return possible_moves(isWhite).size() > 0 ? true : false;
}


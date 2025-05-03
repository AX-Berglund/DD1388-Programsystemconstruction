#include "ChessBoard.h"
#include <iostream>
#include <sstream>

using namespace std;

void testBoard(istream &is, int board_id) {
    ChessBoard board;
    size_t exp_white_cm = 0;    // Expected nr. of white capturing moves
    size_t exp_black_cm = 0;    // Expected nr. of black capturing moves
    size_t exp_white_ncm = 0;   // Expected nr. of white non-capturing moves
    size_t exp_black_ncm = 0;   // Expected nr. of black non-capturing moves

    // Line variable, used for reading from is.
    string line;

    // Read board
    stringstream board_ss;

    for (size_t i = 0; i < 8; ++i) {
        if (!std::getline(is, line)) {
            throw runtime_error("Could not read board #" + to_string(board_id) + ".");
        }

        board_ss << line.substr(0, 8);
    }

    board_ss >> board;

    // Read expected values
    bool result = true;
    result &= !(is >> exp_white_cm).fail();
    std::getline(is, line);
    result &= !(is >> exp_black_cm).fail();
    std::getline(is, line);
    result &= !(is >> exp_white_ncm).fail();
    std::getline(is, line);
    result &= !(is >> exp_black_ncm).fail();
    std::getline(is, line);

    if (!result) {
        throw runtime_error("Could not read expected values for board #" + to_string(board_id) + ".");
    }

    // Verify that the numbers of moves match the expected values
    std::vector<ChessMove> white_capturing_moves = board.capturing_moves(true);
    cout << "White capturing moves for board #" << board_id << ": " << white_capturing_moves.size() << endl;
    for (const auto& move : white_capturing_moves) {
        cout << "  From (" << move.x_from << ", " << move.y_from << ") to (" << move.x_to << ", " << move.y_to << ")" << endl;
    }

    std::vector<ChessMove> black_capturing_moves = board.capturing_moves(false);
    cout << "Black capturing moves for board #" << board_id << ": " << black_capturing_moves.size() << endl;
    for (const auto& move : black_capturing_moves) {
        cout << "  From (" << move.x_from << ", " << move.y_from << ") to (" << move.x_to << ", " << move.y_to << ")" << endl;
    }

    std::vector<ChessMove> white_non_capturing_moves = board.non_capturing_moves(true);
    cout << "White non-capturing moves for board #" << board_id << ": " << white_non_capturing_moves.size() << endl;
    for (const auto& move : white_non_capturing_moves) {
        cout << "  From (" << move.x_from << ", " << move.y_from << ") to (" << move.x_to << ", " << move.y_to << ")" << endl;
    }

    std::vector<ChessMove> black_non_capturing_moves = board.non_capturing_moves(false);
    cout << "Black non-capturing moves for board #" << board_id << ": " << black_non_capturing_moves.size() << endl;
    for (const auto& move : black_non_capturing_moves) {
        cout << "  From (" << move.x_from << ", " << move.y_from << ") to (" << move.x_to << ", " << move.y_to << ")" << endl;
    }
}

int main() {
    try {
        // Test boards from stdin
        int board_id = 1;
        while (!cin.eof()) {
            testBoard(cin, board_id);
            ++board_id;
        }
        cout << "All tests were successful" << endl;
    } catch (std::runtime_error & error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
} 
CC=clang++
FLAGS = -std=c++11 -stdlib=libc++ -g -Wall -pedantic -I/opt/homebrew/Cellar/cxxtest/4.4_3/include
EXETEST=ChessBoard.o ChessPiece.o King.o Knight.o \
		Pawn.o Bishop.o Rook.o Queen.o  \
		Helper.o
EXE=ChessMain.o ChessBoard.o ChessPiece.o King.o Knight.o \
		Pawn.o Bishop.o Rook.o Queen.o  \
		Helper.o

# Run tests with input file
tests: tests.o ${EXETEST}
	${CC} ${FLAGS} -o tests tests.o ${EXETEST}
	./tests < tests.in

tests.o: tests.cpp
	${CC} ${FLAGS} -c tests.cpp

chess: ${EXE}
	${CC} ${FLAGS} ${EXE} -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	${CC} ${FLAGS} -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	${CC} ${FLAGS} -c ChessBoard.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h
	${CC} ${FLAGS} -c ChessPiece.cpp

King.o: King.cpp King.h
	${CC} ${FLAGS} -c King.cpp

Knight.o: Knight.cpp Knight.h
	${CC} ${FLAGS} -c Knight.cpp

Pawn.o: Pawn.cpp Pawn.h
	${CC} ${FLAGS} -c Pawn.cpp

Rook.o: Rook.cpp Rook.h
	${CC} ${FLAGS} -c Rook.cpp

Bishop.o: Bishop.cpp Bishop.h
	${CC} ${FLAGS} -c Bishop.cpp

Queen.o: Queen.cpp Queen.h
	${CC} ${FLAGS} -c Queen.cpp

Helper.o: Helper.cpp Helper.h
	${CC} ${FLAGS} -c Helper.cpp

.PHONY: clean
clean:
	rm -f chess *.o


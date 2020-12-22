#include <iostream>
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include "chess.h"
  
using namespace std; 
  
int main(){ 

// Logo Sequence
ifstream logoReader("logo.txt");

char c = logoReader.get();

// Clear Screen
cout << "\033[2J\033[1;1H";

// Logo
if(logoReader.good() == false){
    cout << "CHESSBOY9000";
}
while(logoReader.good()){
    cout << c;
    c = logoReader.get();
}

// Newlines
for(int i = 0; i < 5; i++){
    cout << endl;
    this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds(150));
}
logoReader.close();

// Game Sequence
char escape = 'x';
while(true){

    cout << "New Game? (Y/N)\n";
    // Sanitize input
    while(escape != 'Y' && escape != 'y' && escape != 'N' && escape != 'n'){
        cin >> escape;
    }

    // Exit if no new game desired
    if(escape != 'Y' && escape != 'y'){
        return 0;
    }

    // Initialize the board
    board theBoard;
    theBoard.initBoard();
    theBoard.printBoard();
    int turn = WHITE;
    int moveFrom[2];
    int moveTo[2];

    // While there isn't a checkmate get the next move
    while(theBoard.isCheckmate(WHITE) == false && theBoard.isCheckmate(BLACK) == false){
        // Print who's turn it is.
        printTurn(turn);
        // Get move
        getMove(moveFrom, moveTo);

        // Verify that the move is a valid move - moveFrom and moveTo are both valid squares, moveFrom has a friendly piece on it, and the selected piece can move to the selected destination
        while((!isSquareOnBoard(moveFrom[0], moveFrom[1]) || !isSquareOnBoard(moveTo[0], moveTo[1])) || !(theBoard.isOccupiedByColor(moveFrom[0], moveFrom[1], turn))  || !(theBoard.getSquare(moveFrom[0], moveFrom[1])->getPiece()->canMove(moveTo[0], moveTo[1], &theBoard))){
            printClearBoard(&theBoard);
            cout << "Invalid move!\n";
            // Print who's turn it is
            printTurn(turn);
            // Get new move
            getMove(moveFrom, moveTo);
        }
        // Move once a valid move is entered
        theBoard.move(moveFrom[0], moveFrom[1], moveTo[0], moveTo[1]);

        // Toggle the turn
        if(turn){
            turn = BLACK;
        }
        else{
            turn = WHITE;
        }
        cout << "\033[2J\033[1;1H";
        theBoard.printBoard();
    }

}
return 0;
} 
/****************************************************************************
 *
 * Proj.02: An implementation minesweeper.
 *
 * File Name: minesweeper.cpp
 * Name:      Lydia Thiel
 * Course:    CPTR 141
 * Date:      March 12, 2021
 *
 */
#include "mineFunctions.h" // function headers
#include <cstdlib>         // random number gen
#include <fstream>         // file input/output
#include <iomanip>         // for setw
#include <iostream>        // cin/cout
#include <string>          //strings
using namespace std;

char board[MAX_ROWS][MAX_COLS];

int main() {
  // variables
  int num_cols;
  int num_rows;
  string load;
  bool userLost;

  cout << "Welcome to Minesweeper!" << endl << endl;
  cout << "Would you like to load an OLD game or start a NEW one? Type OLD or "
          "NEW: ";
  getline(cin, load);

  while (load != "OLD" && load != "NEW") {
    cout << "Please enter a valid option: ";
    getline(cin, load);
  }
  if (load == "OLD") {
    // load old game
    oldGame(board, num_rows, num_cols);
  } else if (load == "NEW") {

    // start new game & check sizing

    cout << "Enter the size of your board as two numbers between 2 "
            "and 20 seperated by a space: ";
    do {
      cin >> num_rows;
      cin >> num_cols;
      if (num_rows < 2 || num_rows > 20 || num_cols < 2 || num_cols > 20) {
        cout << "Please enter valid dimensions: ";
      }
    } while (num_rows < 2 || num_rows > 20 || num_cols < 2 || num_cols > 20);

    // initializeBoard(board, num_rows, num_cols);
    initializeMines(board, num_rows, num_cols);
  }
  // Print game board
  printBoard(board, num_rows, num_cols);
  cout << endl;

  int userRow = 1;
  int userCol = 1;
  string choice = "PLAY";

  // User decides next action
  do {
    cout << "Would you like to PLAY, SAVE & quit, or QUIT? ";
    cin >> choice;

    if (choice == "PLAY") {
      // User picks cell to uncover
      userPlay(board, userRow, userCol, num_rows, num_cols);

      // Update game board
      updateBoard(board, userRow, userCol, userLost);

      // Print updated board
      printBoard(board, num_rows, num_cols);
      if (userLost == true) {
        return 0;
      }
    } else if (choice == "SAVE") {
      saveGame(board, num_rows, num_cols);
      return 0;
    } else if (choice == "QUIT") {
      return 0;
    } else {
      cout << "Please enter a valid choice." << endl;
      choice = "PLAY";
    }

  } while (choice == "PLAY" || choice == "SAVE" || choice == "QUIT");

  return 0;
}

/* FUNCTIONS */

// Set mines in board -----------------------------
void initializeMines(char board[][MAX_COLS], int num_rows, int num_cols,
                     int MAX_ROWS) {
  int mines;
  srand(time(0));
  if (num_cols < num_rows) {
    mines = num_cols;
  } else {
    mines = num_rows;
  }
  for (int i = 0; i < mines * 2; i++) {
    int x = rand() % num_rows;
    int y = rand() % num_cols;
    board[x][y] = 'B';
  }
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      if (board[i][j] != 'B') {
        board[i][j] = 'E';
      }
    }
  }
}

// print board function -----------------------------

void printBoard(char board[][MAX_COLS], int num_rows, int num_cols,
                int MAX_ROWS) {
  cout << "   ";

  for (int j = 1; j < (num_cols + 1); j++) { // top row
    cout << setw(2) << j << " |";
  }
  cout << endl;
  for (int i = 1; i < (num_rows + 1); i++) { // left hand row
    cout << setw(2) << i << "|";
    for (int y = 0; y < num_cols; y++) { // inside part of board
      if (board[i - 1][y] == 'B' || board[i - 1][y] == 'E') {
        cout << setw(2) << '-' << " |";
      } else {
        cout << setw(2) << board[i - 1][y] << " |";
      }
    }
    cout << endl;
  }

  return;
}

// Get user input function -----------------------------

void userPlay(char board[][MAX_COLS], int &userRow, int &userCol, int num_rows,
              int num_cols, int MAX_ROWS) {
  bool already = false;
  cout << "What cell would you like to uncover? Enter the location: ";
  do {
    cin >> userRow;
    cin >> userCol;

    if (userCol > num_cols || userRow > num_rows || userCol < 0 ||
        userRow < 0 ) {
      cout << "Please enter a valid point: ";
    }

  } while (userCol > num_cols || userRow > num_rows || userCol < 0 ||
           userRow < 0 );

  userRow -= 1;
  userCol -= 1;
  return;
}

// Update board function -----------------------------

void updateBoard(char board[][MAX_COLS], int userRow, int userCol,
                 bool &userLost, int MAX_ROWS) {
  // check if cell is B
  int bombs = 0;
  if (board[userRow][userCol] == 'B') {
    cout << "You Lost!" << endl;
    board[userRow][userCol] = '*';

    userLost = true;
    return;
  }
  // check if surrounding cells are B
  else if (board[userRow + 1][userCol + 1] == 'B') { // diagonal right down
    board[userRow][userCol] = '1';
    bombs += 1;
  }
  if (board[userRow + 1][userCol - 1] == 'B') { // diagonal left down
    board[userRow][userCol] = '1';
    bombs += 1;
  }
  if (board[userRow - 1][userCol + 1] == 'B') { // diagonal right up
    board[userRow][userCol] = '1';
    bombs += 1;
  }
  if (board[userRow - 1][userCol - 1] == 'B') { // diagonal left up
    board[userRow][userCol] = '1';
    bombs += 1;
  }
  if ((board[userRow + 1][userCol]) == 'B') { // vertical down
    board[userRow][userCol] = '1';
    bombs += 1;
  }
  if ((board[userRow - 1][userCol]) == 'B') { // vertical up
    board[userRow][userCol] = '1';
    bombs += 1;
  }
  if ((board[userRow][userCol + 1]) == 'B') { // horizontal right
    board[userRow][userCol] = '1';
    bombs += 1;
  }
  if ((board[userRow][userCol - 1]) == 'B') { // horizontal left
    board[userRow][userCol] = '1';
    bombs += 1;
  }

  // if more than one surrounding bomb, display number of surrounding bombs
  if (bombs != 1) {
    char bombsChar = '0' + bombs;

    board[userRow][userCol] = bombsChar;
  }
  return;
}

// Save game function -----------------------------
void saveGame(char board[][MAX_COLS], int num_rows, int num_cols,
              int MAX_ROWS) {
  ofstream fout;
  fout.open("savegame.txt");
  fout << num_rows << endl;
  fout << num_cols << endl;
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      fout << board[i][j];
    }
    fout << endl;
  }
  fout.close();
  return;
}

// Open old game -----------------------------
void oldGame(char board[][MAX_COLS], int &num_rows, int &num_cols,
             int MAX_ROWS) {
  ifstream fin;
  ofstream fout;
  fin.open("savegame.txt");
  if (!fin.is_open()) {
    cout << "Could not open saved game." << endl;
  } else {
    fin >> num_rows;
    fin >> num_cols;
    for (int i = 0; i < num_rows; i++) {
      for (int j = 0; j < num_cols; j++) {
        fin >> board[i][j];
      }
    }
  }
}
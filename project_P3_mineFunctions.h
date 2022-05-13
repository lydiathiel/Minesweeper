/*************************************************************************
 *
 * Project 3
 *
 * File Name:  mineFunctions.h
 * Course:     CPTR 141
 *
 */

// constant size of the board
const int MAX_ROWS = 40;
const int MAX_COLS = 40;

void printBoard(char board[][MAX_COLS], int num_rows, int num_cols, int = MAX_ROWS);

// void initializeBoard(char board[][MAX_COLS], int num_rows, int num_cols, int = MAX_ROWS);

void initializeMines(char board[][MAX_COLS], int num_rows, int num_cols, int = MAX_ROWS);

void userPlay(char board[][MAX_COLS], int& userRow, int& userCol, int num_rows, int num_cols, int = MAX_ROWS);

void updateBoard(char board[][MAX_COLS], int userRow, int userCol, bool &userLost, int = MAX_ROWS);

void saveGame(char board[][MAX_COLS], int num_rows, int num_cols, int = MAX_ROWS);

void oldGame(char board[][MAX_COLS], int &num_rows, int &num_cols, int = MAX_ROWS);

void checkSurround(char board[][MAX_COLS], int userRow, int userCol, int = MAX_ROWS);
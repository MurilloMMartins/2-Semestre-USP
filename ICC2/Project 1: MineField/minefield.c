/*
 * Subject: Introduction to Computer Science 2 
 *
 * Title: MineField
 * 
 * Functionality: This program works just like a traditional minefield, but you have 3 different commands
 * and you can only execute one before the program finishes executing. You should first have a .board file
 * (which is just a normal .txt file) which represents the blank spaces and the mines from the game, after
 * that you can select 3 commands: 1) prints the matrix from the .board file; 2) prints the matrix with tips
 * around the bombs; 3) user input, after that you need to insert the coordinates of the point you want to
 * "click" from the mine field. That's it basically, not really a minefield in the tradicional sense, but
 * just it's basic logic. Have fun :).
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 08/09/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct board{
    char **matrix;
    int lines;
    int columns;
} board_t;

//defining the chars used in the minefield
#define BOMB '*'
#define BLANK_SPACE '.'
#define HIDDEN_SPACE 'X'

//enumerating available commands
enum commands{PRINT_BOARD = 1,
              PRINT_BOARD_TIPS = 2,
              USER_INPUT = 3};

char *readLine(char *text);
void readMatrix(board_t *board, FILE *file);
void printMatrix(board_t board);
void transformMatrix(board_t *board);
bool isInMatrix(int x, int y, int maxX, int maxY);
int countNeighbors(board_t board, int y, int x);
void initializeBoardMask(board_t *boardMask, int lines, int columns);
void revealBlankSpaces(board_t board, char ***maskMatrix, int x, int y);
void deallocateMatrix(board_t *board);

int main(){
    //getting the first command
    int command;
    scanf("%d\n", &command);

    //getting the file name from the user's input
    char *boardName = NULL;
    boardName = readLine(boardName);
    if(boardName == NULL){
        printf("Error while reading file name\n");
        exit(1);
    }

    //opening file
    FILE *boardFile = fopen(boardName, "r");
    if(!boardFile){
        printf("Error while opening file\n");
        exit(1);
    }

    //reading matrix
    board_t currentBoard;
    readMatrix(&currentBoard, boardFile);
    fclose(boardFile);

    //switch with available commands
    switch (command){
        case PRINT_BOARD:
            printMatrix(currentBoard);
            break;
        case PRINT_BOARD_TIPS:
            transformMatrix(&currentBoard);
            printMatrix(currentBoard);
            break;
        case USER_INPUT:
            transformMatrix(&currentBoard);
            
            //getting coordinates from input
            int x, y;
            scanf(" %d %d", &y, &x);

            //these ifs check whether a bomb, a tip or a blank space is present in the coordinates from the input
            if(currentBoard.matrix[y][x] == BOMB){
                printMatrix(currentBoard);
            }
            else if('0' <= currentBoard.matrix[y][x] && currentBoard.matrix[y][x] <= '8'){
                board_t boardMask;
                initializeBoardMask(&boardMask, currentBoard.lines, currentBoard.columns);
                //copies tip from the original matrix and prints the mask
                boardMask.matrix[y][x] = currentBoard.matrix[y][x];
                printMatrix(boardMask);
                deallocateMatrix(&boardMask);
            }
            else if(currentBoard.matrix[y][x] == BLANK_SPACE){
                board_t boardMask;
                initializeBoardMask(&boardMask, currentBoard.lines, currentBoard.columns);
                //reveals blank spaces/adjacent hint spaces and prints the mask
                revealBlankSpaces(currentBoard, &boardMask.matrix, x, y);
                printMatrix(boardMask);
                deallocateMatrix(&boardMask);
            }
            break;
        default:
            printf("Error: Invalid command");
            break;
    }

    //deallocating the original board's name and matrix
    free(boardName);
    deallocateMatrix(&currentBoard);

    //return 0, probably
    return 0;
}

/**
 * @brief Reads a line from the input until it detects a \\n
 * 
 * @param text variable that will contain the string
 * @return char* 
 */
char *readLine(char *text){
    char readout;
    //size starts at 1 because of the \0
    int textSize = 1;
    text = NULL;

    do{
        readout = getchar();
        text = (char *)realloc(text, textSize*sizeof(char));
        text[textSize-1] = readout;
        textSize++;
    }while(readout != '\n');

    //[textSize-2] is used because textSize is incremented in the previous while
    text[textSize-2] = '\0';

    return text;
}

/**
 * @brief Reads the minefield board
 * 
 * @param board struct that has the board's info
 * @param file board file
 */
void readMatrix(board_t *board, FILE *file){
    //initialing variables
    board->lines = 0;
    board->columns = 0;
    board->matrix = NULL;

    //variables used in the reading process
    char readout;
    int control = 0;
    //reads the file until it hits EOF
    while(control != EOF){
        //dinamically allocating the matrix's lines
        board->lines++;
        board->matrix = (char **)realloc(board->matrix, board->lines * sizeof(char *));
        board->matrix[board->lines-1] = NULL;

        //resetting the columns to 0 is needed each time we read a new line
        board->columns = 0;
        do{
            control = fscanf(file, "%c", &readout);
            if(readout != '\n' && control != EOF){
                //dinamically allocating the matrix's columns
                board->columns++;
                board->matrix[board->lines-1] = (char *)realloc(board->matrix[board->lines-1], board->columns * sizeof(char));
                board->matrix[board->lines-1][board->columns-1] = readout;
            }
        }while(readout != '\n' && control != EOF);

        //this part controls whether or not we reach the end of file after a \n
        //it's needed because some files have a \n before EOF
        control = fscanf(file, "%c", &readout);
        if(control != EOF)
            ungetc(readout, file);
    }
       
}

/**
 * @brief Prints the board's matrix
 * 
 * @param board struct that has the board's info
 */
void printMatrix(board_t board){
    for(int i = 0; i < board.lines; i++){
        for(int j = 0; j < board.columns; j++){
            printf("%c", board.matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Adds the tips to the minefield board
 * 
 * @param board struct that has the board's info
 */
void transformMatrix(board_t *board){
    for(int i = 0; i < board->lines; i++){
        for(int j = 0; j < board->columns; j++){
            //checks if the current position is a BLANK_SPACE('.')
            if(board->matrix[i][j] == BLANK_SPACE){
                int neighbors = countNeighbors(*board, i, j);
                //if the amount of neighbors is below 0, the BLANK_SPACE is maintained
                if(neighbors > 0){
                    board->matrix[i][j] = neighbors + '0';
                }
            }
        }
    }
}

/**
 * @brief checks if a coordinate is inside the matrix
 * 
 * @param y y coordinate
 * @param x x coordinate
 * @param maxX x boundary
 * @param maxY y boundary
 * @return true 
 * @return false 
 */
bool isInMatrix(int y, int x, int maxX, int maxY){
    if(x < 0 || y < 0 || x > maxX || y > maxY) 
        return false;
    return true;
}

/**
 * @brief counts the adjacent neighbors from a given point
 * 
 * @param board struct that has the board's info
 * @param y y coordinate
 * @param x x coordinate
 * @return int neighbors
 */
int countNeighbors(board_t board, int y, int x){
    int counter = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(isInMatrix(y+i, x+j, board.columns-1, board.lines-1) && board.matrix[y+i][x+j] == BOMB)
                counter++;
        }
    }

    return counter;
}

/**
 * @brief initializes the board's mask
 * 
 * @param boardMask struct that contains information about the board's mask
 */
void initializeBoardMask(board_t *boardMask, int lines, int columns){
    boardMask->lines = lines;
    boardMask->columns = columns;

    boardMask->matrix = (char **)malloc(lines * sizeof(char *));
    for(int i = 0; i < lines; i++){
        boardMask->matrix[i] = (char *)malloc(columns * sizeof(char));
        for(int j = 0; j < columns; j++){
            //initializes every element with a HIDDEN_SPACE('X')
            boardMask->matrix[i][j] = HIDDEN_SPACE;
        }
    }
}

/**
 * @brief reveals the adjacent blank spaces and hints after a blank space is selected by the user's input
 * 
 * @param board struct that has the board's info
 * @param maskMatrix matrix from the board's mask
 * @param x x coordinate
 * @param y y coordinate
 */
void revealBlankSpaces(board_t board, char ***maskMatrix, int x, int y){
    //every if is a stop condition for the recursion
    //this one checks whether we've been through this point or not
    if((*maskMatrix)[y][x] == HIDDEN_SPACE){
        (*maskMatrix)[y][x] = board.matrix[y][x];

        if(board.matrix[y][x] == BLANK_SPACE){
            for(int i = -1; i <= 1; i++){
                for(int j = -1; j <= 1; j++){
                    if(isInMatrix(y+i, x+j, board.columns-1, board.lines-1)){
                        //this if is here to prevent the recursion happening in the same point
                        if(i != 0 || j != 0){
                            //recursive step
                            revealBlankSpaces(board, maskMatrix, x+j, y+i);
                        }
                    } 
                }
            }
        }
    }
}

/**
 * @brief deallocates a matrix from heap memory
 * 
 * @param board struct that has the board's info
 */
void deallocateMatrix(board_t *board){
    for(int i = 0; i < board->lines; i++){
        free(board->matrix[i]);
    }
    free(board->matrix);
}
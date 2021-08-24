/*
 * Subject: Introduction to Computer Science 2 
 *
 * Title: Reviewing Dinamic Alocation, Recursion and Files
 * 
 * Functionality: The program has the functionality of discovering a exit from an ascii labyrinth. 
 * The user inputs the title of a file containing the ascii labyrinth as well as its dimensions
 * (lenght and width) and the starting location. The program than uses a recursive function to find
 * a way out of the labyrinth. This program does not create a optimal path for escapingthe labyrinth,
 * it only tries to find its exit, after it finds it by chance, the program then prints the final 
 * labyrinth with the paths visited represented by the "*" character. After that it displays some 
 * informations about the labyrinth and its exploration, in order it displays: The number of walls,
 * the number of valid paths, the number of paths visited and the exploration percentage(which is 
 * represented by the division of the number of paths explored and the number of valid paths. This 
 * number is a double, but the number is truncated).
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 24/08/2021
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct labyrinthStruct{
    char **matrix;
    int lines;
    int columns;
    int startingX;
    int startingY;
}labyrinth_t;


char *readLine(char *text);
void readMatrix(labyrinth_t *labyrinth, FILE *file);
void printMatrix(labyrinth_t labyrinth);
int countChars(labyrinth_t labyrinth, char selectedChar);
int exploreLabyrinth(labyrinth_t *labyrinth, int x, int y);

int main(){
    //declaring and reading the file name from the user's input
    char *fileName = NULL;
    fileName = readLine(fileName);

    FILE *file = fopen(fileName, "r");
    if(!file){
        printf("Erro na abertura do arquivo");
        exit(1);
    }

    labyrinth_t labyrinth;
    readMatrix(&labyrinth, file);
    fclose(file);

    //variables needed to store the values needed for the end
    int amountOfPeople = countChars(labyrinth, '#');
    int amountOfPaths = countChars(labyrinth, '.');

    exploreLabyrinth(&labyrinth, labyrinth.startingX, labyrinth.startingY);

    int visitedPaths = countChars(labyrinth, '*');

    printMatrix(labyrinth);

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", amountOfPeople);
    printf("----Numero total de caminhos validos:   %d\n", amountOfPaths);
    printf("----Numero total de caminhos visitados: %d\n", visitedPaths);
    printf("----Exploracao total do labirinto: %.1lf%%\n", (double)(visitedPaths*100/amountOfPaths)); 

    //deallocating memory from the dinamically alocated variables
    for(int i = 0; i < labyrinth.lines; i++){
        free(labyrinth.matrix[i]);
    }
    free(labyrinth.matrix);
    free(fileName);

    //return 0, my boy
    return 0;
}

/**
 * @brief function that reads a line from the input until it detects a EOF
 * 
 * @param text 
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
    }while(readout != EOF);

    //[textSize-2] is used because textSize is incremented in the previous while
    text[textSize-2] = '\0';

    return text;
}

/**
 * @brief function that reads the matrix from the labyrinth, as well as its width, lenght, starting X and starting Y positions(these are all read from a file)
 * 
 * @param labyrinth 
 * @param file 
 */
void readMatrix(labyrinth_t *labyrinth, FILE *file){
    //reads the labyrinth's dimensions
    fscanf(file, "%d %d\n", &labyrinth->lines, &labyrinth->columns);
    //reads the starting positions to be used by the recursive function later
    fscanf(file, "%d %d\n", &labyrinth->startingX, &labyrinth->startingY);

    //allocates memory based of the size of the matrix and reads the characters in the file
    labyrinth->matrix = (char **)malloc(labyrinth->lines * sizeof(char *));
    for(int i = 0; i < labyrinth->lines; i++){
        labyrinth->matrix[i] = (char *)malloc(labyrinth->columns * sizeof(char));
        for(int j = 0; j < labyrinth->columns; j++){
            fscanf(file, "%c", &labyrinth->matrix[i][j]);
        }
        getc(file);
    }
}

/**
 * @brief function that prints the matrix
 * 
 * @param labyrinth 
 */
void printMatrix(labyrinth_t labyrinth){
    for(int i = 0; i < labyrinth.lines; i++){
        for(int j = 0; j < labyrinth.columns; j++){
            printf("%c", labyrinth.matrix[i][j]);
        }
        //prints the \n because it isn't present in the labyrinth's matrix
        printf("\n");
    }
}

/**
 * @brief function that returns the amount of times a char was found within a string matrix
 * 
 * @param labyrinth 
 * @param selectedChar 
 * @return int 
 */
int countChars(labyrinth_t labyrinth, char selectedChar){
    int counter = 0;
    for(int i = 0; i < labyrinth.lines; i++){
        for(int j = 0; j < labyrinth.columns; j++){
            if(labyrinth.matrix[i][j] == selectedChar)
                counter++;
        };
    }

    return counter;
}

/**
 * @brief recursive function that finds the path to the end of the labyrinth.
 * It will follow this order to execute the recursive function: up, right, down, left
 * 
 * @param labyrinth 
 * @param x 
 * @param y 
 * @return int 
 */
int exploreLabyrinth(labyrinth_t *labyrinth, int x, int y){
    labyrinth->matrix[x][y] = '*';

    //variable used to mark whether or not the end was been reached(0 is false, 1 is true)
    int reachedEnd;

    //stop condition of the recursive function
    if(x-1 < 0 || x+1 >= labyrinth->lines || y-1 < 0 || y+1 >= labyrinth->columns){
        return 1;
    }
    else{
        reachedEnd = 0;
        //these if's determine if a character around the current one is valid for the function to recursively continue
        if(labyrinth->matrix[x-1][y] == '.' && reachedEnd == 0){
            reachedEnd = exploreLabyrinth(labyrinth, x-1, y);
        }
        if(labyrinth->matrix[x][y+1] == '.' && reachedEnd == 0){
            reachedEnd = exploreLabyrinth(labyrinth, x, y+1);
        }
        if(labyrinth->matrix[x+1][y] == '.' && reachedEnd == 0){
            reachedEnd = exploreLabyrinth(labyrinth, x+1, y);
        }
        if(labyrinth->matrix[x][y-1] == '.' && reachedEnd == 0){
            reachedEnd = exploreLabyrinth(labyrinth, x, y-1);
        }

        //this is needed to guarantee that the function will try to run through diferent paths in case the program doesn't find the exit in its first time
        if(reachedEnd == 0){
            return 0;
        }
    }
    
    //this return is only present because -Wall and -Werror won't let me compile this function without a return outside of the ifs
    return 1;

}
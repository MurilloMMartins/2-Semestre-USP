#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

int readLine(char **text);

int main(int argc, char *argv[]){

    //reading string from stdin
    char *string;
    readLine(&string);

    //creating the huffman tree and the compression map
    huff_t *tree = create_huffman_tree(string);
    map_t *map = create_compression_map(tree);

    //compressing and decompressing string
    char *compressedString = compress_string(map, string);
    char *decompressedString = decompress_string(tree, compressedString);
    printf("%s\n", decompressedString);

    //calculating compression rate
    double rate = calculate_compression_rate(string, compressedString);
    printf("Indice de compressao: %.2lf\n", rate);

    //freeing allocated memory 
    destroy_map(map);
    destroy_huffman_tree(tree);
    free(decompressedString);
    free(compressedString);
    free(string);

    return 0;
}

/**
 * @brief reads a string from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a EOF is found, otherwise, returns a 0
 */
int readLine(char **text){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r', EOF or a space (and allocates the necessary memory)
    do{
        readout = getchar();
        *text = (char *)realloc(*text, (textSize+1)*sizeof(char));
        (*text)[textSize] = readout;
        textSize++;
    }while(readout != '\n' && readout != '\r' && readout != EOF);

    //if the last character is a '\r', it reads again
    //this is done in case it finds a '\r\n'
    if(readout == '\r')
        readout = getchar();

    //[textSize-1] is used because textSize is incremented in the previous while
    (*text)[textSize-1] = '\0';

    if(readout == EOF)
        return 1;
    return 0;
}
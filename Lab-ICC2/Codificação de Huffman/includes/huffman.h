#ifndef HUFFMAN_H
#define HUFFMAN_H

//--------------------------------------------------------------//
                    //Huffman Tree Functions//

typedef struct huffman_tree huff_t;

/**
 * @brief creates a huffman tree based on a given string
 * 
 * @param string string
 * @return huff_t* huffman tree structure
 */
huff_t *create_huffman_tree(char *string);
/**
 * @brief destroys a huffman tree and frees memory
 * 
 * @param tree huffman tree structure
 */
void destroy_huffman_tree(huff_t *tree);

//--------------------------------------------------------------//
                    //Compression Map Functions//

typedef struct compression_map map_t;

/**
 * @brief creates a compression map based on a given huffman tree
 * 
 * @param tree huffman tree struct
 * @return map_t* map structure
 */
map_t *create_compression_map(huff_t *tree);
/**
 * @brief destroys a compression map structure and frees memory
 * 
 * @param map map structure
 */
void destroy_map(map_t *map);
/**
 * @brief prints the compression map as a table with the characters and their encoding
 * 
 * @param map map structure
 */
void print_map(map_t *map);

//--------------------------------------------------------------//
            //Compression and Decompression Functions//

/**
 * @brief compress a string based on a compression map
 * 
 * @param map map structure
 * @param string string to be compressed
 * @return char* compressed string
 */
char *compress_string(map_t *map, char *string);
/**
 * @brief decompresses a compressed string based on a huffman tree
 * 
 * @param tree huffman tree
 * @param string string to be decompressed
 * @return char* decompressed string
 */
char *decompress_string(huff_t *tree, char *string);
/**
 * @brief Calculates the compression rate of a string
 * 
 * @param orig original string
 * @param comp string after compression
 * @return double compression rate
 */
double calculate_compression_rate(char *orig, char *comp);

#endif
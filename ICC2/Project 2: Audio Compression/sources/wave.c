#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include "wave.h"

/**
 * @brief reads the contents from .wav file and excludes the header
 * 
 * @author Gabriel Alves Kuabara - Monitor ICC II 
 * @param fname file name
 * @param dataSize size of the data array
 * @return unsigned* data array
 */
unsigned char* read_wav_data(char* fname, int *dataSize) {
    //opening file
    FILE* fp = fopen(fname, "rb");
    unsigned char buf4[4];

    //skipping the .wav header
    fseek(fp, 40, SEEK_SET);
    //reading the size of the data
    fread(buf4, sizeof(buf4), 1, fp);
    *dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    unsigned char* data = malloc(sizeof(*data) * (*dataSize));
    
    //reading data
    int i = 0;
    while (i < (*dataSize)) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    return data;
}

/**
 * @brief performs the Discrete Fourier Transform and returns a array of complex numbers
 * 
 * @author Gabriel Alves Kuabara - Monitor ICC II 
 * @param audio data array
 * @param length length of the array
 * @return double* complex array
 */
double complex *DFT(unsigned char *audio, int length) {
    //allocating memory
    double complex *coef = (double complex *) calloc(length, sizeof(double complex));
    
    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            //performing the transform
            coef[k] += audio[n] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
    }
    return coef;
}

/**
 * @brief performs the Inverse Fourier Transform and returns a array of unsigned chars(which can be used to reconstruct a audio file)
 * 
 * @param coef complex array
 * @param length length of the array
 * @return unsigned char* data array
 */
unsigned char *IFT(double complex *coef, int length) {
    //allocating memory
    unsigned char *data = (unsigned char *) calloc(length, sizeof(unsigned char));

    for (int n = 0; n < length; n++) {
        double complex temp = 0;
        for (int k = 0; k < length; k++) {
            //performing the transform
            temp += (coef[k] * cexp((2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I));
        }
        //converting to a real number
        data[n] = creal(temp/length);
    }
    return data;
}

/**
 * @brief copies the header from a audio file to a new one, and adds the new data to this new file
 * 
 * @param fname name of the audio file
 * @param data data array
 * @param length length of the array
 */
void save_wav_data(char* fname, unsigned char *data, int length) {
    FILE* fp = fopen(fname, "rb");
    unsigned char header[44];

    //copying header from the original file
    fread(header, sizeof(header), 1, fp);
    fclose(fp);

    fp = fopen("compressed.wav", "wb");

    //writing data to the new file
    fwrite(header, sizeof(header), 1, fp);
    fwrite(data, length, 1, fp);
    fclose(fp);
}
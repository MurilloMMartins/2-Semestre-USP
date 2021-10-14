#ifndef WAVE_H
#define WAVE_H

#include <complex.h>

unsigned char* read_wav_data(char* fname, int *dataSize);
double complex *DFT(unsigned char *audio, int length);
unsigned char *IFT(double complex *coef, int length);
void save_wav_data(char* fname, unsigned char *data, int lenght);

#endif
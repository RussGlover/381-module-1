

#ifndef FFTCORE_H
#define FFTCORE_H
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>


#define fft_core_base (volatile int *) 0x4820

int fft_engine(unsigned int transform[1024], short int result[1024]);

unsigned int encode(short int real, unsigned short int address);

short int get_real(int in);

short int get_imag(int in);

short int get_magnitude(int in);

#endif

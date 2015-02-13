#include "headers.h"
#include <math.h>


int main()
{
	unsigned int data[1024];
	short int result[1024];
	int i;

	for(i = 0; i< 1024; i++){
		data[i] = (unsigned int)(30000*sin((double) i) + 30000);
		//printf("Index: %i, Data%i\n", i, data[i]);
	}
	fft_engine(data, result);

	for(i = 0; i< 1024; i++){
		//printf("Index: %i, Data%i\n", i, result[i]);
	}

}

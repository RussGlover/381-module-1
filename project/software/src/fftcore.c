

#include "fftcore.h"



int fft_engine(unsigned int transform[1024], short int result[1024])
{
	double scale_factor = 0;
	unsigned int min = 100000;
	unsigned int max = 0;
	//Reset fft core
	IOWR_32DIRECT(fft_core_base,28,0);
	//Variable to set adresses
	unsigned short int i;

	for(i = 0; i < 1024 ;i++)
	{
		if(transform[i] < min){
			min = transform[i];
		}
		if(transform[i] > max){
			max = transform[i];
		}
	}
	scale_factor = 1000/((double)max - (double)min);
	//Encoding audio data with address
	for(i = 0; i < 1024 ;i++)
	{

		//printf("Index: %i, Audio Amplitude: %i\n", i, transform[i]);
		//printf("IndexT: %i, Audio Amplitudes: %i %i %i\n", i, (short int)(transform[i]), (short int)(scale_factor*((double)(transform[i] - min))), (short int)(transform[i]/10));
		transform[i] = encode( (short int)(scale_factor*((double)(transform[i] - min))), i);
		//printf("IndexT: %i, Audio Amplitude: %i\n", i, (short int)(transform[i]), (short int)(transform[i])/10);
	}


	//printf("%i\n", IORD_32DIRECT(fft_core_base,16) );
	//reset core
	IOWR_32DIRECT(fft_core_base,28,0);


	//wait for ready
	while( (IORD_32DIRECT(fft_core_base,16) == 0) )
	{}
	

	//Fill fft
	for(i = 0; i < 1024; i++ )
	{
		//set value
		IOWR_32DIRECT(fft_core_base,0,transform[i]);
		//wait till ready
		while( (IORD_32DIRECT(fft_core_base,16) == 0) )
				{}
	}


	//Start transform
	IOWR_32DIRECT(fft_core_base,8,0);


	//wait for ready
	while( (IORD_32DIRECT(fft_core_base,16) == 0) )
	{}


	//Read in values to transform
	for(i = 0; i < 1024 ; i++ )
	{
		//write in address of ram to read transformed value out. address reverse done in hardware
		IOWR_32DIRECT(fft_core_base,4,(int)i);
		//wait ready
		while( (IORD_32DIRECT(fft_core_base,16) == 0) )
			{}
		//read in new value
		transform[i] = IORD_32DIRECT(fft_core_base,12);
		result[i] = get_magnitude(transform[i]);
		//printf("Index: %i, FFT: %i\n", i ,result[i]);
	}
	printf("done\n");
	return 0;
}

unsigned int encode(short int real, unsigned short int address)
{
	unsigned int temp = 0;
	temp = temp | real;
	temp <<= 16;
	temp = temp | address;
	return temp;

}

short int get_real(int in)
{
	short int temp_real = 0;

	in >>= 16;

	temp_real = temp_real | in;

	return temp_real;
}
short int get_imag(int in)
{
	short int temp_imag = 0;

	temp_imag = temp_imag | in;

	return temp_imag;
}
short int get_magnitude(int in)
{
	short int real = get_real(in);
	short int imag = get_imag(in);
	short int result = (short int)sqrt( (double)pow((double)real,2) + (double)pow((double)imag, 2));
	return result;
}



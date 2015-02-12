#include <definitions.h>

#define fft_core_base (volatile int *) 0x

int main()
{
	unsigned int i = 0;
	int transform[fftLength];
	
	//reset core
	fft_core_reset = 0;
	usleep(15);
	//end of reset
	fft_core_reset = 1;
	while( !*(fft_core_ready) )
	{}

	
	for(i; i++ ; i < fftLength-1 )
	{		
		//Potentially do whole write in 1 
			
		IOWR_16DIRECT(fft_core_addr_in,0,i);
		IOWR_32DIRECT(fft_core_din,0,1);
		IOWR_8DIRECT(fft_core_we,0,1);
		IOWR_8DIRECT(fft_core_we,0,0);		
		
	}
	
	IOWR_32DIRECT(fft_core_start,0,1);
	IOWR_32DIRECT(fft_core_start,0,0);
	
	while( !*(fft_core_ready) )
	{}

	for(i; i++ ; i < fftLength-1 )
	{
		IOWR_32DIRECT(fft_core_addr_out,0,reverse_bits(i));
		transform[i] = IORD_32DIRECT(fft_core_dout,0) * IORD_32DIRECT(fft_core_dout,1);
	}

}

unsigned int reverse_bits(unsigned int in)
{
    unsigned int out = 0;
    unsigned int n = sizeof(i) << 3;
    unsigned int i = 0;

    for (i = 0; i < n; i++)
        if ((input >> i) & 0x1)
            output |=  (0x1 << (n - 1 - i));

    return output;
}
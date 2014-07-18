#include <stdio.h>
#include <stdlib.h>

typedef union
{
    unsigned char bitstream[16];
    long int rnum[4];
} Nonce;
    
int
main(int argc, char *argv[])
{
    int i = 0;

    Nonce n1;

    if (argc != 2)
    {
	printf("Usage:\n");
	printf("%s <seed>\n", argv[0]);
	exit(1);
    }

    i = atoi(argv[1]);
    srand48(i);

    for(i=0; i<4; i++)
    {
	long j = mrand48();
	n1.bitstream[i*4] = j & 0xff;
	n1.bitstream[i*4+1] = (j & 0xff00) >> 8;
	n1.bitstream[i*4+2] = (j & 0xff0000) >> 16;
	n1.bitstream[i*4+3] = (j & 0xff000000) >> 24;
    }

    for (i=0; i<16; i++)
    {
	printf("%0.2x ", n1.bitstream[i]);
    }
    printf("\n");


    double z = drand48();
    printf("random double z = %g\n", z);
    z = drand48();
    printf("random double z = %g\n", z);
}

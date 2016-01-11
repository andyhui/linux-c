#include "snauth_rand.h"
/**
 *Get_Random_Number：create rand number.
 *@num：bits of random number.
 *Return random number on success or null on fault.
 */
unsigned char* Get_Random_Number(int num)
{
    unsigned char *out = NULL;
    out = (unsigned char *)malloc(sizeof(unsigned char)*num);
    int ret;
    ret=RAND_bytes(out, num);
    if(ret!=1)/*fault to create random number*/
    {
        printf("err.\n");
        exit(0);
    }
    else/*create random number success*/
    {
        return out;
    }
}


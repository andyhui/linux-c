#ifndef SNAUTH_RAND_H
#define SNAUTH_RAND_H

#include <stdio.h>
#include <openssl/rand.h>

/**
 *Get_Random_Number：create rand number.
 *@num：bits of random number.
 *Return random number on success or null on fault.
 */
unsigned char* Get_Random_Number(int num);
#endif

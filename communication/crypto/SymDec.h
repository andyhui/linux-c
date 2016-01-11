#ifndef SYMDEC_H
#define SYMDEC_H

#include <string.h>
#include <openssl/evp.h>
#include "snauth_fileio.h"

int SymDec(unsigned char *input, unsigned char *output, unsigned char *key, int in_len, int *out_len);

#endif

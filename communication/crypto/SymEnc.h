# ifndef SYMENC_H
# define SYMENC_H

#include <string.h>
#include <openssl/evp.h>
#include "snauth_fileio.h"
int SymEnc(unsigned char *input, unsigned char *output, unsigned char *key, int in_len, int *out_len);

# endif

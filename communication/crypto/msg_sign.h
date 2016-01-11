/* Package:     msg_sign
 * Description: sign a message with host's own private key, 
                verify a signed-message with other host's public key
 * Author:      yi_kai@c4istarlab
 */
 
#ifndef MSG_SIGN_H
#define MSG_SIGN_H

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "snauth_fileio.h"


/* sign a message with private key */
int DoSign(const char *message,
        const unsigned int msgLen,
        unsigned char **signature,
        unsigned int *signLen,
        const char *privateKey);
/* verify a signature with public key */
int VerifySign(const char *message,
        const unsigned int msgLen,
        const unsigned char *signature,
        const unsigned int signLen,
        EVP_PKEY *publicKey);

#endif

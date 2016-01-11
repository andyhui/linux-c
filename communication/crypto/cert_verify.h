#ifndef CERT_VERIFY
#define CERT_VERIFY

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

/**
 *x509_verify：verify that the certificate is one of us
 *@CA_Certificate：ca certificate
 *@Rec_Certificate：the certificate need to verify 
 *Return 1 on success or 0 on fault.
 */
EVP_PKEY * x509_verify(char *CA_Certificate, char *Rec_Certificate,int len);

#endif

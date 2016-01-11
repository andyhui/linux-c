/* Package:     public key encryption/decryption (also known as asymmetric encryption/decryption)
   Description: encrypt a message with host's own private key
                decrypt a encrypted-message with other host's public key
                RSA and ECC are implmented
   Author:      yi_kai@c4istarlab
*/

#ifndef P_ENC_H
#define P_ENC_H

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include "snauth_fileio.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>  
#include "ecies.h"  

/* Function name: AsymEnc()
 * Description: This function does asymmetric encryption(RSA or ECC)
 * Parameters:
 *      msg: (input) original message which will be encrypted.
 *      msgLen: (input) length of the message.
 *      publicKey: (intut) public key in EVP_PKEY format
 *      encMsg: (output) encrypted message.   encMsg = encrypt(msg, public key)
 *      encMsgLen: (output) length of the encrypted message  
 * Return:
 *      1 for success, -1 for failure
 */
int AsymEnc(
    const unsigned char * msg, const size_t msgLen, 
    EVP_PKEY *publicKey, 
    unsigned char ** encMsg, size_t * encMsgLen);

/* Function name: AsymDec()
 * Description: This function does asymmetric decryption(RSA or ECC)
 * Parameters:
 *      msg: (output) original message which will be decrypted from an enctrypted message.
 *      msgLen: (output) length of the message.
 *      privateKey: (intut) file name of the encrpyted private key (PEM format)
 *      encMsg: (inntpu) encrypted message.   
 *      encMsgLen: (input) length of the encrypted message.
 *   msg = decrypt(encMsg, privateKey)
 * Return:
 *      1 for success, -1 for failure  
 */
int AsymDec(
    unsigned char ** msg, size_t * msgLen, 
    const char *privateKey, 
    const unsigned char * encMsg, const size_t encMsgLen);

    
/* Asymmetric encrypt/decrypt with RSA or ECC */
int AsymEnc_RSA(
    const unsigned char * msg, const size_t msgLen, 
    EVP_PKEY *publicKey, 
    unsigned char ** encMsg, size_t * encMsgLen);
    
int AsymDec_RSA(
    unsigned char ** msg, size_t * msgLen, 
    EVP_PKEY *privateKey, 
    const unsigned char * encMsg, const size_t encMsgLen);

int AsymEnc_ECC(
    const unsigned char * msg, const size_t msgLen, 
    EVP_PKEY *publicKey, 
    unsigned char ** encMsg, size_t * encMsgLen);

int AsymDec_ECC(
    unsigned char ** msg, size_t * msgLen, 
    EVP_PKEY *privateKey, 
    const unsigned char * encMsg, const size_t encMsgLen);

#endif

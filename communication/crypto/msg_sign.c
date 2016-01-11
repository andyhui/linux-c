/* Package:     msg_sign
 * Description: sign a message with host's own private key, 
                verify a signed-message with other host's public key
 * Author:      yi_kai@c4istarlab
 */ 

#include "msg_sign.h" 

/* if the key read from file matches the asymmetric algorithm */
int correct_key(const EVP_PKEY * key);

/* Function name: DoSign()
 * Description: This function signs a message with private key (RSA now)
 * Parameters:
 *      message: (input) original message which will be signed.
 *      msgLen: (input) length of the message.
 *      privateKey: (input) file name of the encrpyted private key
 *                  (PEM format)
 *      signature: (output) signature of the input message.
 *                 signature = sign(message, private key)
 *      signLen: (output) length of the signature
 * Return:
 *      1 for success, -1 for failure
 * Note:  please free(signature) after use
 */
int DoSign(const char *message,
        const unsigned int msgLen,
        unsigned char **signature,
        unsigned int *signLen,
        const char *privateKey)
{
    FILE * fp;
    EVP_PKEY * evpKey;
    EVP_MD_CTX md_ctx;
    char * password;
    char * digestType;
    EVP_MD * evpMD;
    
    ERR_load_crypto_strings();

    if (message == NULL || signature == NULL || signLen == NULL)
    {
        printf("Error: in msg_sign.c: DoSign(): wrong parameters format\n");
        return -1;
    }
    
    /* open private key file in PEM format */
    fp = fopen(privateKey, "rb");
    if (fp == NULL)
    {
        perror("Error: in msg_sign.c: DoSign(): Open Private Key File \
                Error");
        return -1;
    }
    
    OpenSSL_add_all_algorithms();
    
    /* read the private key from file */
    evpKey = EVP_PKEY_new();
    if (getPrivateKeyPassword(&password) != 1)
    {
        password = NULL;
        printf("Warning: in msg_sign.c: DoSign(): password for private \
                key missing in config.\n");
        printf("    you have to input password manually.\n");
    }
    PEM_read_PrivateKey(fp, &evpKey, NULL, password);
    if (evpKey == NULL)
    {
        printf("Error: in msg_sign.c: DoSign(): get evp key from \
                pem error\n");
        return -1;
    }
    fclose(fp);
    if (correct_key(evpKey) == -1)
    {
        printf("Error: in msg_sign.c: DoSign(): symmetric key type does \
                NOT match signature algorithm.\n");
        return -1;
    }
    
    /* Get digest type from config file */
    if (getDigestTypeOfSign(&digestType) != 1)
    {
        printf("Warning: in msg_sign.c: DoSign(): get digest type of \
                message sign error.\n");
        printf("    EVP_sha512() will be used as default.\n");
        evpMD = (EVP_MD*)EVP_sha512();
    }
    else if (strcmp(digestType, "sha512") == 0)
    {
        evpMD = (EVP_MD*)EVP_sha512();
    }
    else if (strcmp(digestType, "sha1") == 0)
    {
        evpMD = (EVP_MD*)EVP_sha1();
    }
    else if (strcmp(digestType, "md5") == 0)
    {
        if (EVP_PKEY_type(evpKey->type) == EVP_PKEY_EC)
        {
            printf("Error: in msg_sin.c: DoSign(): ECC signature does \
                    NOT support md5.\n");
            return -1;
        }
        evpMD = (EVP_MD*)EVP_md5();
    }
    else
    {
        printf("Error: in msg_sign.c: DoSign(): Digest type of message \
                sign error. %s not supported.\n", digestType);
        return -1;
    }
    
    /* sign */
    EVP_MD_CTX_init(&md_ctx);
    if (EVP_SignInit_ex(&md_ctx, evpMD, NULL) != 1)
    {
        printf("Error: in msg_sign.c: DoSign(): sign init error\n");
        return -1;
    }
    if (EVP_SignUpdate(&md_ctx, message, msgLen) != 1)
    {
        printf("Error: in msg_sign.c: DoSign(): sign update error\n");
        return -1;
    }
    EVP_PKEY_size(evpKey);
    *signature = malloc(EVP_PKEY_size(evpKey));
    if (EVP_SignFinal(&md_ctx, *signature, signLen, evpKey) != 1)
    {
        printf("Error: in msg_sign.c: DoSign(): Sign Final error\n");
        printf("    %s\n", ERR_error_string(ERR_get_error(), NULL));
        return -1;
    }
    return 1;
}

/* Function name: VerifySign()
 * Description: This function verifies a signature of a message with public
 * key (RSA now)
 * Parameters:
 *      message: (input) original message .
 *      msgLen: (input) length of the message.
 *      publicKey: (intut) public key in EVP_PKEY format.
 *      signature: (input) signature of the original message.
 *      signLen: (input) length of the signature
 * Return:
 *      1 for success, -1 for failure, 0 for wrong signature
 */
int VerifySign(const char *message,
        const unsigned int msgLen,
        const unsigned char *signature,
        const unsigned int signLen,
        EVP_PKEY *publicKey)
{
    int ret;
    EVP_MD_CTX md_ctx;
    char * digestType;
    EVP_MD * evpMD;
    
    if (message == NULL || signature == NULL)
    {
        printf("Error: in msg_sign.c: VerifySign(): wrong parameters \
                format\n");
        return -1;
    }
    
    if (correct_key(publicKey) == -1)
    {
        printf("Error: in msg_sign.c: VerifySign(): symmetric key type \
                does NOT match signature algorithm.\n");
        return -1;
    }
    
    /* Get digest type from config file */
    if (getDigestTypeOfSign(&digestType) != 1)
    {
        printf("Warning: in msg_sign.c: VerifySign(): Get digest type of \
                message sign error\n");
        printf("    EVP_sha512() will be used as default.\n");
        evpMD = (EVP_MD*)EVP_sha512();
    }
    else if (strcmp(digestType, "sha512") == 0)
    {
        evpMD = (EVP_MD*)EVP_sha512();
    }
    else if (strcmp(digestType, "sha1") == 0)
    {
        evpMD = (EVP_MD*)EVP_sha1();
    }
    else if (strcmp(digestType, "md5") == 0)
    {
        if (EVP_PKEY_type(publicKey->type) == EVP_PKEY_EC)
        {
            printf("Error: in msg_sign.c: VerifySign(): ECC signature \
                    does NOT support md5.\n");
            return -1;
        }
        evpMD = (EVP_MD*)EVP_md5();
    }
    else
    {
        printf("Error: in msg_sign.c: VerifySign(): Digest type of message \
                sign error. %s not supported.\n", digestType);
        return -1;
    }
    
    /* intialize MD context */
    EVP_MD_CTX_init(&md_ctx);
    
    /* verify */
    if (EVP_VerifyInit_ex(&md_ctx, evpMD, NULL) != 1)
    {
        printf("Error: in msg_sign.c: VerifySign(): verify init error\n");
        return -1;
    }
    if (EVP_VerifyUpdate(&md_ctx, message, msgLen) != 1)
    {
        printf("Error: in msg_sign.c: VerifySign(): verify update error\n");
        return -1;
    }
    ret = EVP_VerifyFinal(&md_ctx, signature, signLen, publicKey);
    if (ret == 1)
        return 1;
    else
        return 0;
}

int correct_key(const EVP_PKEY * key)
{
    char * algorithm;
    int ret;
    int NO_algorithm;
    
    algorithm = NULL;
    NO_algorithm = 0;
    if (getAsymEncAlgorithm(&algorithm) != 1)
    {
        NO_algorithm = 1;
        printf("Warning: in msg_sign.c: asymmetric algorithm missing in \
                config.\n");
        printf("    ECC will be used as default\n");
    }
    if ((NO_algorithm != 1) && (strcmp(algorithm, "RSA") == 0))
    {
        if (EVP_PKEY_type(key->type) == EVP_PKEY_RSA)
            ret = 1;
        else
            ret = -1;
    }
    else if ((NO_algorithm == 1) || (strcmp(algorithm, "ECC") == 0))
    {
        if (EVP_PKEY_type(key->type) == EVP_PKEY_EC)
            ret = 1;
        else
            ret = -1;
    }
    else
    {
        ret = -1;
    }
    
    if (algorithm != NULL){
        free(algorithm);
    }
    return ret;
}

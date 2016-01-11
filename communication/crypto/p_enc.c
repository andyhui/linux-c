/* Package:     public key encryption/decryption (also known as asymmetric encryption/decryption)
   Description: encrypt a message with host's own private key
                decrypt a encrypted-message with other host's public key
                RSA and ECC are implmented
   Author:      yi_kai@c4istarlab
*/

#include "p_enc.h"

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
    unsigned char ** encMsg, size_t * encMsgLen)
{
    char * method;          /* algorithm */
    int ret;                /* return value */
    int NO_method;
    
    if (msg == NULL || encMsg == NULL || encMsgLen == NULL)
    {
        printf("Error: in p_enc.c: AsymEnc(): Wrong parameters format\n");
        return -1;
    }
    
    /* get asymmetric encrypt algorithm from config file */
    NO_method = 0;
    method = NULL;
    if (getAsymEncAlgorithm(&method) != 1)
    {
        NO_method = 1;
        printf("Warning: in p_enc.c: AsymEnc(): \
                asymmetric algorithm missing in config \
                ECC will be used as default\n");
    }
    
    /* to decrypt the private key */
    OpenSSL_add_all_algorithms();
    
    /* encrypte the message by RSA or ECC */    
    if ((NO_method == 1) || (strcmp(method, "ECC") == 0))
    {
        if (EVP_PKEY_type(publicKey->type) != EVP_PKEY_EC)
        {
            printf("Error: in p_enc.c: AsymEnc(): \
                    asymmetric key does NOT match asymmetric algorithm.\n");
            ret = -1;
        }
        ret = AsymEnc_ECC(msg, msgLen, publicKey, encMsg, encMsgLen);
    }
    else if ((NO_method == 0) && (strcmp(method,"RSA") == 0))
    {
        if (EVP_PKEY_type(publicKey->type) != EVP_PKEY_RSA)
        {
            printf("Error: in p_enc.c: AsymEnc(): \
                    asymmetric key does NOT match asymmetric algorithm.\n");
            ret = -1;
        }
        ret = AsymEnc_RSA(msg, msgLen, publicKey, encMsg, encMsgLen);
    }
    else
    {
        printf("Error: in p_enc.c: AsymEnc(): \
                Asymmetric encryption algorithm %s not support\n", method);
        ret = -1;
    }
    
    if (method != NULL){
        free(method);
    }
    return ret;
}

/* Function name: AsymEnc_ECC()
 * Description: This function does ECC asymmetric encryption
 * Parameters:
 *      msg: (input) original message which will be encrypted.
 *      msgLen: (input) length of the message.
 *      publicKey: (intut)  public key in EVP_PKEY format
 *      encMsg: (output) encrypted message.   encMsg = encrypt(msg, public key)
 *      encMsgLen: (output) length of the encrypted message  
 * Return:
 *      1 for success, -1 for failure
 */
int AsymEnc_ECC(
    const unsigned char * msg, const size_t msgLen, 
    EVP_PKEY *publicKey, 
    unsigned char ** encMsg, size_t * encMsgLen)
{
    EC_KEY * ecKey;        /* public key in EC_KEY format */
    char * ecKey_hex;      /* public key in string format */
    unsigned char * msg2;  /* copy of msg, ecies_ecrypt() needs char*, not const char* */
    secure_t * encMsg2;    /* return value of ecies_ecrypt() */
    
    /* initialize */
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_ciphers();
    OpenSSL_add_all_digests();
    ecies_group_init();    
    srand(time(NULL));
    msg2 = (unsigned char*)msg;
    
    /* publickey: EVP_PKEY --> EC_KEY */    
    ecKey = EVP_PKEY_get1_EC_KEY(publicKey);
    if (ecKey == NULL)
    {
        printf("Error: in p_enc.c: AsymEnc_ECC(): \
                convert EVP_PKEY --> EC_KEY error\n");
        return -1;
    }
    /* publickey: EC_KEY --> string */
    if (!(ecKey_hex = ecies_key_public_get_hex(ecKey)))
    {
        printf("Error: in p_enc.c: AsymEnc_ECC(): \
                convert EC_KEY --> EC_KEY_hex error\n");
        return -1;
    }
    
    /* encMsg2 = encrypted message */
    encMsg2 = ecies_encrypt(ecKey_hex, msg2, msgLen);
    if (encMsg2 == NULL)
    {
        printf("Error: in p_enc.c: AsymEnc_ECC(): \
                ecies_encrypt() return NULL\n");
        return -1;
    }
    /* encMsg <- encMsg2 */
    *encMsgLen = secure_total_length((char**)encMsg2);
    *encMsg = malloc(*encMsgLen);
    memcpy(*encMsg, encMsg2, *encMsgLen);
    
    return 1;
}

/* Function name: AsymEnc_RSA()
 * Description: This function does RSA asymmetric encryption
 * Parameters:
 *      msg: (input) original message which will be encrypted.
 *      msgLen: (input) length of the message.
 *      publicKey: (intut)  public key in EVP_PKEY format
 *      encMsg: (output) encrypted message.   encMsg = encrypt(msg, public key)
 *      encMsgLen: (output) length of the encrypted message  
 * Return:
 *      1 for success, -1 for failure
 */
int AsymEnc_RSA(
    const unsigned char * msg, const size_t msgLen, 
    EVP_PKEY *publicKey, 
    unsigned char ** encMsg, size_t * encMsgLen)
{
    EVP_PKEY_CTX * ctx;     /* asymmetric encryption context */
    
    if (msgLen > 86)
    {
        printf("Error: in p_enc.c: AsymEnc_RSA(): \
                Can not encrypt a message longer than 86 bytes\n");
        return -1;
    }

    /* encrypt the message with public key, encMsg = encrypt(msg, public key) */
    ctx = EVP_PKEY_CTX_new(publicKey, NULL);
    if (!ctx)
    {
        /* initialize context */
        printf("Error: in p_enc.c: AsymEnc_RSA(): EVP_PKEY_CTX_new error\n");
        return -1;
    }
    if (EVP_PKEY_encrypt_init(ctx) <= 0)
    {
        /* initialzie encryption */
        printf("Error: in p_enc.c: AsymEnc_RSA(): \
                EVP_PKEY_encrypt_init error\n");
        return -1;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(ctx,RSA_PKCS1_OAEP_PADDING) <= 0)
    {
        /* set rsa padding */
        printf("Error: in p_enc.c: AsymEnc_RSA(): \
                EVP_PKEY_CTX_set_rsa_padding error\n");
        return -1;
    }
    if (EVP_PKEY_encrypt(ctx, NULL, encMsgLen, msg, msgLen) <= 0)
    {
        /* get encrypted message length */
        printf("Error: in p_enc.c: AsymEnc_RSA(): EVP_PKEY_encrypt error\n");
        return -1;
    }
    *encMsg = malloc(*encMsgLen);
    if (! (*encMsg))
    {
        /* if malloc success */
        perror("Error: in p_enc.c: AsymEnc_RSA(): malloc failure");
        return -1;
    }
    if (EVP_PKEY_encrypt(ctx, *encMsg, encMsgLen, msg, msgLen) <= 0)
    {
        /* encrypt message */
        printf("Error: in p_enc.c: AsymEnc_RSA(): EVP_PKEY_encrypt error\n");
        return -1;
    }
    
    return 1;
}

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
    const unsigned char * encMsg, const size_t encMsgLen)
{
    char * method;      /* decryption algorithm */
    EVP_PKEY * evpKey;  /* private key in EVP_PKEY format */
    FILE * fp;          /* private key file */
    char * password;    /* password of the private key */
    int ret;            /* return value */
    int NO_method;
    
    if (msg == NULL || msgLen == NULL || encMsg == NULL || encMsgLen <= 0)
    {
        printf("Error: in p_enc.c: AsymDec(): wrong parameters format.\n");
        return -1;
    }
    
    /* to decrypt the private key */
    OpenSSL_add_all_algorithms();
    
    /* open the file which includes the private key (PEM format) */
    fp = fopen(privateKey, "rb");
    if (fp == NULL)
    {
        perror("Error: in p_enc.c: AsymDec(): open private key file error");
        return -1;
    }
    
    /* get private key from file, PEM --> EVP_PKEY */
    evpKey = EVP_PKEY_new();
    if (getPrivateKeyPassword(&password) != 1)
    {
        password = NULL;
        printf("Warning: in p_enc.c: AsymDnc(): \
                password for private key missing in config. \
                you have to input password manually.\n");
    }
    PEM_read_PrivateKey(fp, &evpKey, NULL, password);
    if (evpKey == NULL)
    {
        printf("Error: in p_enc.c: AsymDec(): \
                get private key from pem error\n");
        return -1;
    }
    fclose(fp);
    
    /* get decryption algorithm from config file */
    method = NULL;
    NO_method = 0;
    if (getAsymEncAlgorithm(&method) != 1)
    {
        NO_method = 1;
        printf("Warning: in p_enc.c: AsymDnc(): \
                asymmetric algorithm missing in config. \
                ECC will be used as default\n");
    }
     
    /* decrypte the encrypted-message by RSA or ECC */     
    if ((NO_method == 1) || (strcmp(method, "ECC") == 0))
    {
        if (EVP_PKEY_type(evpKey->type) != EVP_PKEY_EC)
        {
            printf("Error: in p_enc.c: AsymDec(): \
                    symmetric key does NOT match asymmetric algorithm.\n");
            ret = -1;
        }
        ret = AsymDec_ECC(msg, msgLen, evpKey, encMsg, encMsgLen);
    }
    else if ((NO_method == 0) && (strcmp(method, "RSA") == 0))
    {
        if (EVP_PKEY_type(evpKey->type) != EVP_PKEY_RSA)
        {
            printf("Error: in p_enc.c: AsymDec(): \
                    symmetric key does NOT match asymmetric algorithm.\n");
            ret = -1;
        }
        ret = AsymDec_RSA(msg, msgLen, evpKey, encMsg, encMsgLen);
    }
    else
    {
        printf("Error: in p_enc.c: AsymDec(): \
                asymmetric decryption algorithm %s not support\n", method);
        ret = -1;
    }
    
    if (method != NULL){
        free(method);
    }
    return ret;
}

/* Function name: AsymDec_ECC()
 * Description: This function does asymmetric decryption(ECC)
 * Parameters:
 *      msg: (output) original message which will be decrypted from an enctrypted message.
 *      msgLen: (output) length of the message.
 *      privateKey: (intut) private key (EVP_PKEY format)
 *      encMsg: (inntpu) encrypted message.   
 *      encMsgLen: (input) length of the encrypted message.
 *   msg = decrypt(encMsg, privateKey)
 * Return:
 *      1 for success, -1 for failure  
 */
int AsymDec_ECC(
    unsigned char ** msg, size_t * msgLen, 
    EVP_PKEY *privateKey, 
    const unsigned char * encMsg, const size_t encMsgLen)
{
    EC_KEY * ecKey;       /* private key in EC_KEY format */
    char * ecKey_hex;     /* private key in strnig format */
    unsigned char * msg2; /* return value of ecies_decrypt() */
    secure_t * encMsg2;   /* ecies_decrypt() needs secure_t *, not const char * */

    /* initialize */
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_ciphers();
    OpenSSL_add_all_digests();
    ecies_group_init();
    
    /* private key: EVP_PKEY --> EC_KEY */        
    ecKey = EVP_PKEY_get1_EC_KEY(privateKey);
    if (ecKey == NULL)
    {
        printf("Error: in p_enc.c: AsymDec_ECC(): \
                convert EVP_PKEY --> EC_KEY error\n");
        return -1;
    }
    /* privete key: EC_KEY --> string */
    if (!(ecKey_hex = ecies_key_private_get_hex(ecKey)))
    {
        printf("Error: in p_enc.c: AsymDec_ECC(): \
                convert EC_KEY --> EC_KEY_hex error\n");
        return -1;
    }
    
    /* msg2 = decrypted message */
    encMsg2 = (char**)encMsg;
    msg2 = ecies_decrypt(ecKey_hex, encMsg2, msgLen);
    if (msg2 == NULL)
    {
        printf("Error: in p_enc.c: AsymDec_ECC(): ecies_decrypt() error\n");
        return -1;
    }
    /* msg <- msg2 */
    *msg = malloc(*msgLen);
    memcpy(*msg, msg2, *msgLen);
   
    return 1;
}

/* Function name: AsymDec_RSA()
 * Description: This function does asymmetric decryption(RSA)
 * Parameters:
 *      msg: (output) original message which will be decrypted from an enctrypted message.
 *      msgLen: (output) length of the message.
 *      privateKey: (intut) private key (EVP_PKEY format)
 *      encMsg: (inntpu) encrypted message.   
 *      encMsgLen: (input) length of the encrypted message.
 *   msg = decrypt(encMsg, privateKey)
 * Return:
 *      1 for success, -1 for failure  
 */
int AsymDec_RSA(
    unsigned char ** msg, size_t * msgLen, 
    EVP_PKEY *privateKey, 
    const unsigned char * encMsg, const size_t encMsgLen)
{
    EVP_PKEY_CTX * ctx;  /* EVP_PKEY context */
        
    /* decrypt the messgae, msg = decrypt(encMsg, private key) */
    ctx = EVP_PKEY_CTX_new(privateKey, NULL);
    if (!ctx)
    {
        /* initialize EVP_PKEY context */
        printf("Error: in p_enc.c: AsymDec_RSA(): EVP_PKEY_CTX_new error\n");
        return -1;
    }
    if (EVP_PKEY_decrypt_init(ctx) <= 0)
    {
        /* initialize decryption */
        printf("Error: in p_enc.c: AsymDec_RSA(): \
                EVP_PKEY_decrypt_init error\n");
        return -1;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(ctx,RSA_PKCS1_OAEP_PADDING) <= 0)
    {
        /* set rsa padding */
        printf("Error: in p_enc.c: AsymDec_RSA(): \
                EVP_PKEY_CTX_set_rsa_padding error\n");
        return -1;
    }
    if (EVP_PKEY_decrypt(ctx, NULL, msgLen, encMsg, encMsgLen) <= 0)
    {
        /* get decrypted message length */
        printf("Error: in p_enc.c: AsymDec_RSA(): \
                EVP_PKEY_decrypt_NULL error\n");
        return -1;
    }
    *msg = malloc(*msgLen);
    if (!*msg)
    {
        /* check if malloc OK */
        perror("Error: in p_enc.c: AsymDec_RSA(): malloc failure");
        return -1;
    }
    if (EVP_PKEY_decrypt(ctx, *msg, msgLen, encMsg, encMsgLen) <= 0)
    {
        /* get decrypted message */
        printf("Error: in p_enc.c: AsymDec_RSA(): EVP_PKEY_decrypt error\n");
        return -1;
    }
    return 1;
}

#include "SymDec.h"
/*
 * NAME: SymDec
 * PARAMETER：
 *        INPUT:   input: data to be decrypted
 *                 output: store the output data
 *                 key: store the key
 *                 in_len: length of input data
 *                 out_len: length of output data
 *        OUTPUT： 1 if success
 *                 0 if fail
 * FUNCTION： Decrypt the input date by symmetric encryption algorithm
 * AUTHOR：   li min
 */
int SymDec(unsigned char *input,
           unsigned char *output,
           unsigned char *key,
           int in_len,
           int *out_len)
{
    int ret;  //return 1 if success
    char *type;
    EVP_CIPHER_CTX ctx;
    const EVP_CIPHER *cipher;
    unsigned char iv[16];//the initial vector
    int i,outl,outl_total=0;

    for(i=0;i<16;i++)
    {
        memset(&iv[i],i,1);//intialize the vector
    }
    EVP_CIPHER_CTX_init(&ctx);//Context initialization

    // type of symmetric encryption algorithm
    type = NULL;
    if (getSymEncAlgorithm(&type)==1)
    {
#if(DEBUG)
        printf("SymDecType is: %s\n",type);
#endif
    }
    if (strncmp(type,"des",3)==0)
    {
        cipher=EVP_des_ofb();
    }
    else if(strncmp(type,"3des",4)==0)
    {
        cipher=EVP_des_ede3_ofb();
    }
    else if(strncmp(type,"aes",3)==0)
    {
        cipher=EVP_aes_192_ofb();
    }
    else
        cipher=EVP_des_ede3_ofb();

    // specific initialization
    ret=EVP_DecryptInit_ex(&ctx,cipher,NULL,key,iv);

    if(ret!=1)
    {
        printf("EVP_EncryptInit_ex error!\n");
        EVP_CIPHER_CTX_cleanup(&ctx);
        return 0;//error
    }

    EVP_DecryptUpdate(&ctx,output+outl_total,&outl,input,in_len);
    outl_total+=outl;

    ret=EVP_DecryptFinal_ex(&ctx,output+outl_total,&outl);
    outl_total+=outl;
#if(DEBUG)
    printf("The sym-dec is finished, the result is:%d\n",outl_total);
#endif
    *out_len = outl_total;
    EVP_CIPHER_CTX_cleanup(&ctx);
    if (type != NULL)
    {
        free(type);
    }
    return 1;//success
}



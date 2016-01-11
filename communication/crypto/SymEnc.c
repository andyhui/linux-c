#include "SymEnc.h"
/*
 * NAME:SymDec
 * PARAMETER：
 *      INPUT：input: data to be encrypted
 *             output: store the output data
 *             key: store the key
 *             in_len: length of input data
 *             out_len: length of output data
 *      OUTPUT：1 if success
 *              0 if fail
 * FUNCTION： Encrypt the input date by symmetric encryption algorithm
 * AUTHOR： li min
 */
int SymEnc(unsigned char *input,
           unsigned char *output,
           unsigned char *key,
           int in_len,
           int *out_len)
{
    int ret;  //return 1 if success
    char *type;//the type of encryption algorithm
    EVP_CIPHER_CTX ctx;
    const EVP_CIPHER *cipher;
    unsigned char iv[16];//the intial vector
    int i,outl,outl_total=0;

    for(i=0;i<16;i++)
    {
        memset(&iv[i],i,1);//Intialize the vector
    }
    EVP_CIPHER_CTX_init(&ctx);//intizlize the contex

    type = NULL;
    if (getSymEncAlgorithm(&type)==1)
    {
#if(DEBUG)
        printf("SymEncType is: %s\n",type);//the algorithm type
#endif
    }
    if (strcmp(type,"des")==0)
    {
        cipher=EVP_des_ofb();
    }
    else if(strcmp(type,"3des")==0)
    {
        cipher=EVP_des_ede3_ofb();
    }
    else if(strcmp(type,"aes")==0)
    {
        cipher=EVP_aes_192_ofb();
    }
    else 
        cipher=EVP_des_ede3_ofb();

    ret=EVP_EncryptInit_ex(&ctx,cipher,NULL,key,iv);//specific intialization

    if(ret!=1)
    {
        printf("EVP_EncryptInit_ex error!\n");
        EVP_CIPHER_CTX_cleanup(&ctx);
        return 0;//error
    }

    EVP_EncryptUpdate(&ctx,output+outl_total,&outl,input,in_len);
    outl_total+=outl;

    EVP_EncryptFinal_ex(&ctx,output+outl_total,&outl);
    outl_total+=outl;
    *out_len = outl_total;
#if(DEBUG)
    printf("The sym-enc is finished, the result is:%d\n",outl_total);
#endif
    EVP_CIPHER_CTX_cleanup(&ctx);
    if (type != NULL)
    {
        free(type);
    }
    return 1;//success
}




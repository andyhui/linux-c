/**
 *x509_verify：verify that the certificate is one of us.
 *@CA_Certificate：ca certificate.
 *@Rec_Certificate：the certificate need to verify.
 *Return 1 on success or 0 on fault.
 */
#include "cert_verify.h"
EVP_PKEY * x509_verify(char *CA_Certificate, char *Rec_Certificate,int len)
{
    OpenSSL_add_all_algorithms();
    EVP_PKEY * pkey;
    int ret;

    int certlen = 0;

    BIO *bCa = NULL;
    BIO *bCert = NULL;

    X509 *ca = NULL;
    X509 *selfCert = NULL;

    X509_STORE *ca_store = NULL;
    X509_STORE_CTX *ctx = NULL;
    STACK_OF(X509) *ca_stack = NULL;

    /* x509初始化 */
    ca_store = X509_STORE_new();
    ctx = X509_STORE_CTX_new();

    /*加入CA证书*/
    char *caBuf = CA_Certificate;

    bCa=BIO_new_file(caBuf,"r");
    if(!bCa)
    {
        ret = 0;
        fprintf(stderr, "Can't open cert file %s\n", caBuf);
        goto EXIT;
    }
    ca=PEM_read_bio_X509(bCa,NULL,NULL,NULL);

    /* 加入证书存储区 */
    ret = X509_STORE_add_cert(ca_store, ca);
    if ( ret != 1 )
    {
        fprintf(stderr, "X509_STORE_add_cert fail, ret = %d\n", ret);
        goto EXIT;
    }

    /* 需要校验的证书 */
    bCert = BIO_new(BIO_s_mem());
    certlen = BIO_write(bCert,Rec_Certificate,len);
    if(certlen != len)
    {
        //printf("hello world!\n");
        ret = 0;
        fprintf(stderr, " %s\n", "Bio write error");
        goto EXIT;
    }
    selfCert=PEM_read_bio_X509(bCert,NULL,NULL,NULL);

    /*获取证书的公钥*/
    pkey = EVP_PKEY_new();
    pkey = X509_get_pubkey(selfCert);


    ret = X509_STORE_CTX_init(ctx, ca_store, selfCert, ca_stack);
    if ( ret != 1 )
    {
        fprintf(stderr, "X509_STORE_CTX_init fail, ret = %d\n", ret);
        goto EXIT;
    }

    //openssl-1.0.1c/crypto/x509/x509_vfy.h
    ret = X509_verify_cert(ctx);

    if ( ret != 1 )
    {
        printf("fail please check!\n");
        fprintf(stderr, "X509_verify_cert fail, ret = %d, error id = %d, %s\n",
                ret, ctx->error, X509_verify_cert_error_string(ctx->error));
        goto EXIT;
    }
EXIT:
    X509_free(selfCert);
    X509_free(ca);

    X509_STORE_CTX_cleanup(ctx);
    X509_STORE_CTX_free(ctx);

    X509_STORE_free(ca_store);
    BIO_free(bCa);
    BIO_free(bCert);

    if (ret == 1)
    {
        return pkey;
    }
    else
    {
        return NULL;
    }
}

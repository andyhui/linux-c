 X509 * cert;
 EVP_PKEY * pubkey;
 //length is the length of the certificateDataBytes in terms of bytes.
 cert = d2i_x509 (certificateDataBytes, length);
 pubkey = X509_get_pubkey (cert);
 
 RSA * rsa
 rsa = EVP_PKEY_get1_RSA(pubkey);

 //Now rsa contains RSA public key. Use it.

 //After use, free the pubkey
 EVP_PKEY_free (pubkey);
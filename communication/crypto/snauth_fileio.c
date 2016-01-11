/* Package:     snauth_fileio
   Description: Get configuration from snauth.config
   Author:      yi_kai@c4istarlab
*/


#include "snauth_fileio.h"

/*
 * Function:    getConfig
 * Purpose:     Fuction call used to get the item content from the file
 *              "snauth.config".
 * Parameters
 *   e.g.  private_key_filename = SKx-lixiang.pem
 *   item: (input)left of the '='
 *   content: (output)right of the '='
 * Return:      length of content, 0 for failed, -1 for error
 * Author:      Kai Yi
 */
static int getConfig(const char * item, char ** content)
{
    FILE * fp;    
    int ret;
    char * line;
    size_t lineLen2;
    ssize_t lineLen;
    char * charPtr;
    char * key;
    char * content2;
    
    /* open config file */
    fp = fopen(configFile, "r");
    if (fp == NULL){
        perror("Open config file err");
        return -1;
    }
    line = NULL;
    ret = 0;
    /* procedure file line by line */
    while (ret == 0 && !feof(fp))
    {
        lineLen = getline(&line, &lineLen2, fp);
        lineLen2 = lineLen;
        /* if comment */
        if (line[0] != '#')
        {
            /* if include '=' */
            if ((charPtr = strchr(line, '=')) != NULL)
            {
                key = strstr(line, item);
                /* if match the key */
                if (key != NULL && key < charPtr && 
                    (key[strlen(item)] == ' ' || key[strlen(item)] == '='))
                {
                    charPtr ++;
                    while (charPtr[0] == ' ')
                    {
                        charPtr ++;
                    }
                    content2 = charPtr;
                    /* find the length of returned content */
                    while (charPtr != NULL && charPtr[0] != '\0' &&
                        charPtr[0] != '\n' && charPtr[0] != ' ')
                    {
                        charPtr ++;
                        ret ++;
                    }
                    if (ret <= 0)
                    {
                        printf("config file format wrong: NULL after =\n");
                        free(line);
                        line = NULL;
                        fclose(fp);
                        return -1;
                    }
                    *content = malloc(ret+1);
                    memset(*content, 0, ret+1);
                    strncpy(*content, content2, ret);
                    free(line);
                    line = NULL;
                    fclose(fp);
                    return 1;
                }    
            }
        } /* if comment */
        if(line != NULL)
        {
            free(line);
            line = NULL;
        }
    }
    fclose(fp);
    *content = NULL;
    if(line != NULL)
    {
        free(line);
        line = NULL;
    }
    return 0;
}


/*
 * Function:    getPrivateKeyFile
 * Purpose:     Fuction call used to get SK filename from the file
 *              "snauth.config".
 * Parameters
 *   filename:  pointer to the string storing the SK filename.
 * Return:      length of content, 0 for failed, -1 for error
 * Author:      Kai Yi
 */
int getPrivateKeyFile(char ** filename)
{
    return getConfig("private_key_filename", filename);
}


/*
 * Function:    getCertFile
 * Purpose:     Fuction call used to get certificate filename from the file
 *              "snauth.config".
 * Parameters
 *  filename:  pointer to the string storing the certificate filename.
 * Return:      length of content, 0 for failed, -1 for error
 * Author:      Kai Yi
 */
int getCertFile(char ** filename)
{
    return getConfig("certificate_filename", filename);
}


/*
 * Function:    getSymEncAlgorithm
 * Purpose:     Fuction call used to get symmetric encryption algorithm from
 *              the file "snauth.config".
 * Parameters
 *  algorithm:  pointer to the string storing the symmetric encryption 
 *              algorithm.
 * Return:      length of content, 0 for failed, -1 for error
 * Author:      Li Min
 */
int getSymEncAlgorithm(char ** algorithm)
{
	return getConfig("SymEnc_type",algorithm);
}

/*
 * Function:    getAsymEncAlgorithm
 * Purpose:     Fuction call used to get asymmetric encryption algorithm from
 *              the file "snauth.config".
 * Parameters
 *  algorithm:  pointer to the string storing the symmetric encryption
 *              algorithm.
 * Return:      length of content, 0 for failed, -1 for error
 * Author:      Li Min
 */
int getAsymEncAlgorithm(char ** algorithm)
{
    return getConfig("asymmetric_encryption_algorithm", algorithm);
}

/*
 * Function:    getDigestTypeOfSign
 * Purpose:     Fuction call used to get sign method from the file
 *              "snauth.config".
 * Parameters
 *  algorithm:  pointer to the string storing the sign method.
 * Return:      length of content, 0 for failed, -1 for error.
 * Author:      Kai Yi
 */
int getDigestTypeOfSign(char ** type)
{
    return getConfig("digest_type_of_sign",type);
}

/*
 * Function:    getDigestTypeOfSign
 * Purpose:     Fuction call used to get ECC encryption method from the file
 *              "snauth.config".
 * Parameters
 *  algorithm:  pointer to the string storing the ECC encryption method
 * Return:      length of content, 0 for failed, -1 for error
 * Author:      Kai Yi
 */
int getDigestTypeOfECCencrypt(char ** type)
{
    return getConfig("digest_type_of_ECC_encryption", type);
}

/*
 * Function:    getPrivateKeyPassword
 * Purpose:     Fuction call used to get SK password from the file
 *              "snauth.config".
 * Parameters
 *   password:  pointer to the string storing the SK password.
 * Return:      length of content, 0 for failed, -1 for error
 * Author:      Kai Yi
 */
int getPrivateKeyPassword(char ** password)
{
    return getConfig("private_key_password", password);
}

/*
 * Function:    getCacertFilename
 * Purpose:     Fuction call used to get cacert file from the file
 *              "snauth.config".
 * Parameters
 *   password:  pointer to the string storing the cacert file.
 * Return:      length of content, 0 for failed, -1 for error
 * Author:      Kai Yi
 */
int getCacertFilename(char ** filename)
{
    return getConfig("cacert_filename", filename);
}

/* Function:    setConfigFilename
 * Purpose:     let user set the configuration file
 */
int setConfigFilename(const char * filename)
{
    configFile = malloc(strlen(filename));
    memcpy(configFile, filename, strlen(filename));
    return 1;
}

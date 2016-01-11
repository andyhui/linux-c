/* Package:     snauth_fileio
   Description: Get configuration from snauth.config
   Author:      yi_kai@c4istarlab
*/

#ifndef SNAUTH_FILEIO_H
#define SNAUTH_FILEIO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * configFile; 
/* All the configuration should be written in this file. */
/* #define CONFIG_FILE "snauth.config" */

/* get item content from "snauth.config" */
//static int getConfig(const char * item, char ** content);

/* get SK filename from "snauth.config" */
int getPrivateKeyFile(char ** filename);

/* get SK password from "snauth.config" */
int getPrivateKeyPassword(char ** password);

/* get certificate filename from "snauth.config" */
int getCertFile(char ** filename);

/* get asymmetric encryption algorithm from "snauth.config" */
int getAsymEncAlgorithm(char ** algorithm);

/* get symmetric encryption algorithm from "snauth.config" */
int getSymEncAlgorithm(char ** algorithm);

/* get sign method from "snauth.config" */
int getDigestTypeOfSign(char ** type);

/* get ECC encryption method from "snauth.config" */
int getDigestTypeOfECCencrypt(char ** type);

/* get Cacert filename from "snauth.config" */
int getCacertFilename(char ** filename);

int setConfigFilename(const char * filename);
#endif

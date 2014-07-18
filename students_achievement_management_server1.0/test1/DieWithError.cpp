#include <stdio.h> 
#include <stdlib.h> 
using namespace std;
void DieWithError(const char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

#ifndef PA03_H
#define PA03_H

#include <stdlib.h>
char * strcat_ex(char * * dest, int * n, const char * src);
char * * explode(const char * str, const char * delims, int * arrLen);



char * strcat_ex(char * * dest, int * n, const char * src);
{
int length = (1 + 2 * (strlen(*dest) + strlen(src)));
if ((* dest == NULL) || (strlen(*dest) + strlen(src) + 1 > *n))
{
char * arr =  malloc(length * sizeof(char *));
*n = arr;
strcpy(arr, *dest);
free(arr);
}
strcat(*dest, src);
}
return 0;
}

char * * explode(const char * str, const char * delims, int * arrLen);
{
int N = 0;
int index;
int arrInd = 0;
int last = 0;
for (index = 0; index <  arrLen; index++)
{
if (strchr(delims, str[index]) =! NULL)
{
N++;
}
}
char * * strArr = malloc((N+1) * sizeof(char *));
for (ind

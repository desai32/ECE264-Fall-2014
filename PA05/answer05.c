#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "answer05.h"
void partition1(int *, int, int);
void partition2(int *, int, int);
void partition3(int *, int, int);
void partition4(int *, int, int);
void partition5(int *, int, int);
void partition6(int *, int, int);
void partition7(int *, int, int);
void printPartition(int *, int);
int primecheck(int);
void printDecreasing(int *, int);
void printPartition(int * arr, int length)
{
int ind;
printf("= ");
for (ind = 0; ind < length - 1; ind++)
{
//printf("= ");
printf("%d + ", arr[ind]);
}
printf("%d\n", arr[length -1]);
}
void partition1(int * arr, int ind, int left)
{
int val;
if (left == 0)
{
printPartition(arr, ind);
return;
}
for (val = 1; val <= left; val++)
{
arr[ind] = val;
partition1(arr, ind + 1, left - val);
}
}
void partitionAll(int value)
{
int * arr;
arr = malloc(sizeof(int) * value);
partition1(arr, 0, value);
free(arr);
return;
}

void partition2(int * arr, int ind, int left)
{
int val;
if (left == 0)
{
printPartition(arr, ind);
return;
}
int min = 1;
if (ind != 0)
{
min = arr[ind - 1] + 1;
}
for (val = min; val <= left; val++)
{
arr[ind] = val;
partition2(arr, ind + 1, left - val);
}
}

void partitionIncreasing(int value)
{
int * arr;
arr = malloc(sizeof(int) * value);
partition2(arr, 0, value);
free(arr);
return;
}

void partition3(int * arr, int ind, int left)
{
int val;
if (left == 0)
{
printDecreasing(arr, ind);
return;
}
int min = 1;
if ( ind != 0)
{
min = arr[ind - 1] + 1;
}
for (val = left; val >= min; val--)
{
arr[ind] = val;
partition3(arr, ind + 1, left - val);
}
}

void printDecreasing(int * arr, int length)
{
int lcv;
for (lcv = 0; lcv < length - 1; lcv++)
{
if (arr[lcv + 1] >= arr[lcv])
{
return;
}
}
printf("= ");
for (lcv = 0; lcv < length - 1; lcv++)
{
printf("%d + ", arr[lcv]);
}
printf("%d\n", arr[length -1]);
}
void partitionDecreasing(int value)
{
int * arr;
arr = malloc(sizeof(int) * value);
partition3(arr, 0, value);
free(arr);
return;
}

void partition4(int * arr, int ind, int left)
{
int val;
if (left == 0)
{
printPartition(arr, ind);
return;
}
for (val = 1; val <= left; val +=2)
{
arr[ind] = val;
partition4(arr, ind + 1, left - val);
}
}

void partitionOdd(int value)
{
int * arr;
arr = malloc(sizeof(int) * value);
partition4(arr, 0, value);
free(arr);
return;
}

void partition5(int * arr, int ind, int left)
{
int val;
if (left == 0)
{
printPartition(arr, ind);
return;
}
for (val = 2; val <= left; val +=2)
{
arr[ind] = val;
partition5(arr, ind + 1, left - val);
}
}

void partitionEven(int value)
{
int * arr;
arr = malloc(sizeof(int) * value);
partition5(arr, 0, value);
free(arr);
return;
}

void partition6(int * arr, int ind, int left)
{
int val;
if (left == 0)
{
printPartition(arr, ind);
return;
}
for (val = 1; val <= left; val++)
{
int valid = 0;
if ( ind == 0)
{
valid = 1;
}
else 
{
valid = (arr[ind - 1] % 2) != (val % 2);
}
if ( valid == 1)
{
arr[ind] = val;
partition6(arr, ind + 1, left - val);
}
}
}

void partitionOddAndEven(int value)
{
int * arr;
arr = malloc(sizeof(int) * value);
partition6(arr, 0, value);
free(arr);
return;
}

int primecheck(int value)
{
int i;
for (i = 2; i < value; i++)
{
if (value % i == 0 && i != value)
{
return;
}
else 
{
return 1;
}
}
}
void partition7(int * arr, int ind, int left)
{
int val;
if (left == 0)
{
printPartition(arr, ind);
return;
}
for (val = 1; val <= left; val++)
{
if (primecheck(val) == 1)
{
arr[ind] = val;
partition7(arr, ind + 1, left - val);
}
}
}
void partitionPrime(int value)
{
int * arr;
arr = malloc(sizeof(int) * value);
partition7(arr, 0, value);
free(arr);
return;
}


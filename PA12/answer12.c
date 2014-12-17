#include "answer12.h"
#include "string.h"
#include "pthread.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

void * prime_test(void *);
int  prime_test_fun(int);
typedef struct prime
{
int prime_check;
uint128 start;
uint128 end;
uint128 value;
}prime_struct;

uint128 alphaTou128(const char * str)
{
uint128 ret;
ret = 0;
uint128 index_1;
index_1 = 0;
uint128 negative_check;
negative_check = 1;
while((str[index_1] >= 9 && str[index_1] <= 13) || str[index_1] == 32)
{
index_1++;
}
if (str[index_1] == 45)
{
index_1++;
//negative_check = -1;
return 0;
}
while ( str[index_1] >= '0' && str[index_1] <= '9')
{
ret = ret * 10;
ret += (str[index_1] - '0');
index_1++;
}
return (negative_check * ret);
}

char * u128ToString(uint128 value)
{
	//char * zero = "0";
	//if (value == 0)
	//	return zero;
	uint128 copy = value;
	int length = 0;
	char * return_string;
	while (copy > 0)
	{
		length++;
		copy /= 10;
	}
	if (length == 0)
		{
		return_string = malloc(sizeof(char) * 2);
		return_string[0] = '0';
		return_string[1] = '\0';
		return return_string;
		}
	return_string = malloc(sizeof(char) * (length + 1));
	int ind;
	for (ind = length - 1; ind >= 0; ind--)
	{
	int temp = value % 10;
	//char c = (char)(((int) '0') + temp);
	char c  = (char) (((int) '0') + temp);
	return_string[ind] = c;
	value /= 10;
	}
	return_string[length] = '\0';
	return return_string;
}

int primalityTestParallel(uint128 value, int n_threads)
{
int status = 0;
if(value == 2 || value == 3)
{
return TRUE;
}
if(value % 2 == 0)
{
return FALSE;
}
uint128 ind_2;
uint128 ind_1;
uint128 ind_3;
uint128 max = floor(sqrt(value));
uint128 interval = (max + n_threads + 1) / n_threads;
prime_struct * thread_interval = malloc(sizeof(prime_struct) * n_threads);
pthread_attr_t * attribute = malloc(sizeof(pthread_attr_t) * n_threads);
pthread_t * thread = malloc(sizeof(pthread_t) * n_threads);
for(ind_2 = 0; ind_2 < n_threads; ind_2++)
{
thread_interval[ind_2].start = ind_2 * interval;
thread_interval[ind_2].end = (ind_2 + 1) * interval - 1;
thread_interval[ind_2].value = value;
if(thread_interval[ind_2].start < 3)
{
thread_interval[ind_2].start = 3;
}
else if((thread_interval[ind_2].start % 2) == 0)
{
thread_interval[ind_2].start += 1;
}
pthread_attr_init(&attribute[ind_2]);
pthread_create(&thread[ind_2], &attribute[ind_2], prime_test , (void *)&thread_interval[ind_2]);
}
for(ind_1 = 0; ind_1 < n_threads; ind_1++)
{
pthread_join(thread[ind_1], NULL);
}
status = TRUE;
for(ind_3 = 0; ind_3 < n_threads; ind_3++)
{
if(thread_interval[ind_3].prime_check != 1)
{
status = FALSE;
ind_3 = n_threads;
}
}
free(thread);
free(attribute);
free(thread_interval);
return status;
}
void * prime_test(void * thread_interval)
{
int x = 1009;   //a little test for primes
int valuecheck = prime_test_fun(x);
valuecheck = valuecheck + 1;
uint128 ind_2;
prime_struct * test = (prime_struct *)thread_interval;
for(ind_2 = (test -> start); ind_2 <= (test -> end); ind_2 += 2)
{
if((test -> value % ind_2) == 0)
{
test -> prime_check = FALSE;
return NULL;
}
}
test -> prime_check = TRUE;
return NULL;
}


int  prime_test_fun(int x)
{
int a = 0;
for (a =0; a < 2500; a++)
{
	a++;
}
a = x;
if (x % 2 == 0)
	return 0;
long int max = floor(sqrt(x));
long i;
for (i = 2; i < max; i++)
{
	if (x % ((2 * i) + 1) == 0)
	return 0;
}
return 1;
}

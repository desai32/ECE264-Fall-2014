#include "answer08.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

List * List_createNode(const char * str)
{
  List * nd = malloc(sizeof(List));
  nd ->str = strdup(str);

  nd ->next = NULL; 
  return nd;
}
void List_destroy(List * list)
{
  if (list == NULL)
    {
      return;
    }
  while (list != NULL)
    {
      List * p = list -> next;
      free(list->str);
      free(list);
      list = p;
    }
}

int List_length(List * list)
{
  int length = 0;
  while (list != NULL)
    {
      List * p = list -> next;
      list = p;
      length++;
    }
  return length;
}
List * List_merge(List * lhs,
                  List * rhs,
                  int (*compar)(const char *, const char*))
{
  List * head; 
  List * tail; 
  int lcv;
  if (lhs == NULL && rhs == NULL)
	{
	return NULL;
	}
  if (rhs == NULL)
    {
      return lhs;
    }
  if (lhs == NULL)
    {
      return rhs;
    }
  if (compar(lhs->str,rhs->str) < 0)
    {
      head = lhs;
      tail = lhs;
      lhs = lhs->next;
      //tail = rhs;
    }
  else 
    {
      head = rhs;
      tail = rhs;
      rhs = rhs->next;
      //tail = lhs;
    }
  while (lhs != NULL && rhs != NULL)
    {
      lcv = compar(lhs->str, rhs->str);
      if (lcv < 0)
	{
	  tail->next = lhs;
	  //tail = tail->next;
	  lhs = lhs->next;
	  tail = tail->next;
	}

      else 
	{
	  tail->next = rhs;
	  //tail = tail->next; 
	  rhs = rhs->next;
	  tail = tail->next;
	}
    }
  if (lhs == NULL)
    {
      tail->next = rhs;
    }
  if (rhs == NULL)
    {
      tail->next = lhs;
    }
  return head;
}
List * List_sort(List * list, int (*compar)(const char *, const char*))
{
List * lhs = list;
List * rhs;
int lcv = 1;
//List * lhs; 
  if (List_length(list) <= 1)
     {
	return (list);
     }

int mid = List_length(list) / 2;
//int lcv = 1;

while (list->next != NULL)
{
if (lcv == mid)
{
rhs = list->next;
list->next = NULL;
}
else 
list = list->next;
lcv++;
}
/*
for (lcv = 0; lcv < mid; lcv++)
{
list = list->next;
rhs = list->next;
list->next = NULL;
}
*/
lhs = List_sort(lhs, compar);
rhs =  List_sort(rhs, compar);
list = List_merge(lhs,rhs, compar);
return list;
}
/*
if (List_length(list) == 0 || List_length(list) == 1)
     {
        return list;
     }
int count = 0;
List * p = list;
while(p != NULL)
{
count++;
p = p->next;
}
int midpoint = count / 2;
List * left = list;
List * right = list;
List * null = NULL;
int half = 0;
while (right != NULL)
{
half++;
List * next = right->next;
if (half == midpoint)
{
right->next = NULL;
null = next;
}
right = next;
}
List * lhs = List_sort(left, compar);
List * rhs = List_sort(right, compar);
List * New = List_merge(lhs, rhs, compar);
return New;
}
*/


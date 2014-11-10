#include "answer09.h"
//Most of the code is very similar to Prof. Lu's textbook as it was used as reference.
//I had a lot of help from the TA's to complete the explode function
char * * explode(const char * str, const char * delims, int * arrLen);
char * * explode(const char * str, const char * delims, int * arrLen)
{
int array_index;
int last;
int lcv;
int length;
array_index = 0;
last = 0;
lcv = 0;
length = 0;
char * * stringArr = malloc(sizeof(char *) * (*arrLen));
for(lcv = 0; lcv < strlen(str); lcv++)
{
if (strchr(delims, str[lcv]) != NULL)
{
length = lcv - last;
stringArr[array_index] = malloc(sizeof(char) * (length + 1));
memcpy(stringArr[array_index], &str[last], length);
stringArr[array_index][length] = '\0';
array_index++;
last = lcv + 1;
}
}
length = lcv - last;
stringArr[array_index] = malloc(sizeof(char) * (length + 1));
memcpy(stringArr[array_index], &str[last], length);
stringArr[array_index][length] = '\0';
array_index++;
last = lcv + 1;
return (stringArr);
}
BusinessNode * create_node(char * stars, char * name, char * address)
{
BusinessNode * new;
new = malloc(sizeof(BusinessNode));
new ->left = NULL;
new -> right = NULL;
new -> name = name;
new -> stars = stars;
new -> address = address;
return new;
}

BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
if (root == NULL)
{
return node;
}
if (strcmp(node->name, root->name) <= 0)
   {
     root->left = tree_insert(node, root->left);
   }
else 
   {
     root->right = tree_insert(node, root->right);
   }
//root = node; 
return root;
}

BusinessNode * load_tree_from_file(char * filename)
{
BusinessNode * root = NULL;
BusinessNode * node;
//char * string1;
//char * string2;
//char * string3;
FILE * fptr = fopen(filename, "rb");
int length = 3;
char * * stringarr;
char * string = malloc(sizeof(char) * 2048); //2048 because TA told me to
if (fptr == NULL)
{
free(string);
return NULL;
} 
while(fgets(string, 2048, fptr) != NULL)
{
stringarr = explode(string, "\t\t\0", &length);
/*
stringarr = malloc(3 * sizeof(int *));
*/ 
//string1 = strdup(stringarr[0]);
//string2 = strdup(stringarr[1]);
//string3 = strdup(stringarr[2]);
node = create_node(stringarr[0], stringarr[1], stringarr[2]);
root = tree_insert(node, root);
//free(stringarr[0]);
//free(stringarr[1]);
//free(stringarr[2]);
free(stringarr);
}
//free(string1);
//free(string2);
//free(string3);
//free(stringarr);
free(string);
fclose(fptr);
return root;
}

BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
if (root == NULL)
return NULL;
if (strcmp(name, root->name) == 0)
return root;
if (strcmp(name, root->name) < 0)
return tree_search_name(name, root->left);
return tree_search_name(name, root->right);
}

void destroy_tree(BusinessNode * root)
{
if (root == NULL)
return;
destroy_tree(root->left);
destroy_tree(root->right);
free(root->name);
free(root->stars);
free(root->address);
free(root);
}


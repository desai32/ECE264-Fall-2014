#include "answer09.h"
char * * explode(const char * str, const char * delims, int * arrLen);
char * * explode(const char * str, const char * delims, int * arrLen)
{
int ind=0;
    int last=0;
    int len=0;
    int arrInd=0;
    *arrLen = 1;
for(ind = 0; ind < strlen(str); ind++)
    {
        if (strchr(delims, str[ind]) != NULL)
        {
            (*arrLen)++;
        }
    }
    char * * strArr = malloc(((*arrLen)) * sizeof(char *));
    for(ind=0; ind < strlen(str); ind++)
    {
        if (strchr(delims, str[ind]) != NULL)
        {
            len = ind - last;
            strArr[arrInd]=malloc((len+1)*sizeof(char));
            memcpy(strArr[arrInd], &str[last], len);
            strArr[arrInd][len]='\0';
            arrInd++;
            last=ind+1;
        }
    }
len = ind - last;
    strArr[arrInd]=malloc((len+1)*sizeof(char));
    memcpy(strArr[arrInd], &str[last], len);
    strArr[arrInd][len]='\0';
    arrInd++;
    last=ind+1;
    return(strArr);
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
char ** stringarr;
char * string = malloc(sizeof(char) * 2048);
if (fptr == NULL)
{
free(string);
return NULL;
} 
while(fgets(string, 2048, fptr) != NULL)
{
stringarr = explode(string, "\t\t\0", &length);
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


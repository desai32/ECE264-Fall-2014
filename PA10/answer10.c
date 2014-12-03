#include "answer10.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
//#include "inttypes"
#define BUFSIZE 20000
typedef struct BusLoc_t
{
long Bus_offset;
long review_offset;
int num_rev;
} BusinessLocation;

typedef struct BusTree_t
{
char * name;
BusinessLocation * head;
struct BusTree_t * left, * right;
} BusinessTree;
BusinessTree * BusTree_Insert(BusinessTree *, char *, long);
BusinessTree * BusTree_create(char *, long);
void destroy_tree(BusinessTree *);
void create_business_bst1(const char*); //, const char* reviews_path);
char * * explode(const char *, const char *, int *);
void print_tree(BusinessNode*, const char*);


void print_tree(BusinessTree* Root,const char * filename)
{
if(root == NULL)
{
return;
}
print_tree(root -> left, filename); // Prints the Left Side of the Tree

printf("\n\nThe Business Name is %s at ",root -> BusinessTree);

//print_Locations(root -> location,filename);

print_tree(root -> right, filename); // Print the 
}

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
void create_business_bst1(const char* businesses_path) //, const char* reviews_path)
{
FILE * ptr = fopen("business_path", "r");
if (ptr == NULL)
return;
char *  buffer = malloc(sizeof(char) * BUFSIZE);
char ** string = NULL;
const char * delim = "\t";
int value;
long offset;
int ind;
BusinessTree * root = NULL;
while (!feof(ptr))
	{
		offset = ftell(ptr);
		fgets(buffer, BUFSIZE, ptr);
		if (feof(ptr))
			break;
		string = explode(buffer, delim, &value);
		printf("the offset value is %s", string[0]);
		printf("the business name is %s", string[1]);
		root = BusTree_Insert(root, string[1], offset);
	
		for (ind = 0; ind < value; ind++)
			{
				free(string[ind]);
			}
		free(string);
	}
	print_tree(root, business_path);	 	
	destroy_tree(root);
}
/*
struct Business* get_business_reviews(struct YelpDataBST* bst, char* name, char* state, char* zip_code)
{

}

void destroy_business_bst(struct YelpDataBST* bst)
{
return;
}

void destroy_business_result(struct Business* b);
{
return;
}

typedef struct review
{
long int file_offset;
int num_reviews;
} 
*/
/*
typedef struct YelpDataBST;
{
FILE * reviews;
FILE * business;
BusinessTree * treenode; 
} 
*/
/*
typedef struct BusLoc_t
{
long Bus_offset;
long review_offset;
int num_rev
} BusinessLocation;
*/
/*
typedef struct BusTree_t
{
char * name;
BusinessLocation * head;
struct BusTree_t * left, * right;
} BusinessTree;
*/

/*
BusinessLocation * BusLoc_create(FILE * , FILE * )
{
BusLoc * loc = malloc(sizeof(BusLoc));

loc -> id = id;
loc -> address = strdup(address);
loc -> city = strdup(address);
loc -> state = strdup(city);
loc -> zip = strdup(zip);

return loc;
}

void BusLoc_destory(BusinessLocation * BusLoc)
{
	if (BusLoc == NULL)
		return;
	while (BusLoc != NULL)
	{
		BusinessLocation * p = BusLoc -> next;
		free(BusLoc -> something);
		free(BusLoc);
		BusLoc = p;
	}
}
*/
BusinessTree * BusTree_create(char * name, long offset)
{
BusinessTree * new;
new = malloc(sizeof(BusinessTree));
new->name = name;
new->head = NULL;
new->left = NULL;
new->right = NULL;
return new;
}


BusinessTree * BusTree_Insert(BusinessTree * root, char * name, long offset)
{
	if (root == NULL)
	{
		BusinessTree * tree = BusTree_create(name, offset);
		return tree;
	}
	if (strcmp(name, root -> name) < 0)
		{
			root -> left = BusTree_Insert(root -> left, name, offset);
			return root;
		}
	else if (strcmp(name, root -> name) == 0)
		{
			//root -> head = BusTree_Insert(root -> head, offset);
			return root;
		}
	else
		{
			root -> right = BusTree_Insert(root -> right, name, offset);
			return root;
		}
	//return root;
}


void destroy_tree(BusinessTree * root)
{
	if (root == NULL)
		return;
	destroy_tree(root -> left);
	destroy_tree(root -> right);
	free(root -> name);
	free(root);
}
//make destroy functions
//make insert functions
//make a find function

int main()
{
	create_business_bst1("Bus.tsv");
	return EXIT_SUCCESS;
}

#include "answer10.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
//#include <"inttypes">
#define BUFSIZE 20000 
typedef struct BusLoc_t
{
long Bus_offset;
long review_offset;
int num_rev;
struct BusLoc_t * next;
} BusinessLocation;

typedef struct BusTree_t
{
char * name;
BusinessLocation * head;
struct BusTree_t * left, * right;
} BusinessTree;

typedef struct YelpDataBST
{
FILE * reviews; 
FILE * business;
BusinessTree * treenode;
} YelpData;

BusinessTree * BusTree_Insert(BusinessTree *, char *, long, long, int);

BusinessTree * BusTree_create(char *, long, long, int);

void destroy_tree(BusinessTree *);

struct YelpDataBST * create_business_bst(const char*, const char *); 

char * * explode(const char *, const char *, int *);

//void print_tree(BusinessTree *, const char*);

long getrev_offset(int * , FILE *, FILE *, int);

BusinessLocation * BusLoc_create(long, long, int);

void BusLoc_destroy(BusinessLocation *);

//void print_Locations(BusinessLocation * , const char*);

BusinessLocation * list_create(BusinessLocation *, long, long, int);

struct YelpDataBST * yelp_create(FILE *, FILE *, BusinessTree * );

BusinessLocation * list_create(BusinessLocation * head , long offset1, long offset2, int num_rev)
{
	if (head == NULL)
		return BusLoc_create(offset1, offset2, num_rev);
	head -> next = list_create(head -> next, offset1, offset2, num_rev);
	return head;
}

YelpData * yelp_create(FILE * rev_ptr, FILE * bus_ptr, BusinessTree * root)
{
	YelpData * new = malloc(sizeof(YelpData));
	new -> reviews = rev_ptr;
	new -> business = bus_ptr;
	new -> treenode = root;
	return new;
}

BusinessLocation * BusLoc_create(long bus_offset, long rev_offset, int num_rev)
{
	BusinessLocation * new = malloc(sizeof(BusinessLocation));
	new -> review_offset = rev_offset;
	new -> Bus_offset = bus_offset;
	new -> num_rev = num_rev;
	new -> next = NULL;
	return new;
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

struct YelpDataBST * create_business_bst(const char* business_path, const char* reviews_path)
{
FILE * ptr = fopen(business_path, "r");
FILE * temp_ptr = fopen(reviews_path, "r");
FILE * rev_ptr = fopen(reviews_path, "r");
if (ptr == NULL)
return NULL;
char *  buffer = malloc(sizeof(char) * BUFSIZE);
char ** string = NULL;
int num_rev = 0;
long rev_offset = -1;
int value = 0;
long offset = 0;
int ind;
BusinessTree * root = NULL;
while (!feof(ptr))
	{
		offset = ftell(ptr);
		fgets(buffer, BUFSIZE, ptr);
		if (feof(ptr))
			break;
		string = explode(buffer, "\t", &value);
		//printf("the offset value is %ld\n", offset);
		//printf("the business name is %s\n", string[1]);
		rev_offset = getrev_offset(&num_rev, rev_ptr, temp_ptr, atoi(string[0]));
		printf("%ld\n", rev_offset);
		printf("%d\n", num_rev);
		root = BusTree_Insert(root, string[1], offset, rev_offset, num_rev);
		num_rev = 1;
		for (ind = 0; ind < value; ind++)
			{
				free(string[ind]);
			}
		free(string);
	}
	//fclose(ptr);
	//fclose(temp_ptr);
	//fclose(rev_ptr);
	free(buffer);

	struct YelpDataBST * yelpdata = yelp_create(rev_ptr, ptr, root);
	
	return yelpdata;
}



long getrev_offset(int * num_rev, FILE * rev_ptr, FILE * temp_ptr, int id)
{
	long rev_offset = -1;
	long temp_offset = 0;
	int ind = 0;
	int arrlength = 0;
	char * buffer = malloc(sizeof(char) * BUFSIZE);
	char ** string;
	if (rev_ptr == NULL)
		return -1;
	while(!feof(rev_ptr))
		{
			temp_offset = ftell(rev_ptr);
			fgets(buffer, BUFSIZE, rev_ptr);
			if (feof(rev_ptr))
				break;
			string = explode(buffer, "\t", &arrlength);
			if (atoi(string[0]) == id && rev_offset == -1)
				{
					rev_offset = temp_offset;
				}
			if (atoi(string[0]) == id)
				{
					(*num_rev) = 1 + (*num_rev);
				}
			else //free the memory
				{
					for (ind = 0; ind < arrlength; ind++)
						{
							free(string[ind]);
						}
				free(string);
				break;
				}
			for (ind = 0; ind < arrlength; ind++)
				{
					free(string[ind]);
				}
			free(string);
			fgets(buffer, BUFSIZE,temp_ptr);
		}
	free(buffer);
	return (rev_offset);
}			

void BusLoc_destroy(BusinessLocation * BusLoc)
{
	if (BusLoc == NULL)
		return;
	BusLoc_destroy(BusLoc -> next);
	free(BusLoc);
}

BusinessTree * BusTree_create(char * name, long bus_offset, long rev_offset, int num_rev)
{
BusinessTree * new;
new = malloc(sizeof(BusinessTree));
new->name = strdup(name);
new->head = BusLoc_create(bus_offset, rev_offset, num_rev);
new->left = NULL;
new->right = NULL;
return new;
}


BusinessTree * BusTree_Insert(BusinessTree * root, char * name, long bus_offset, long rev_offset, int num_rev)
{
	if (root == NULL)
		{
		return BusTree_create(name, bus_offset, rev_offset, num_rev);
		}
	if (strcasecmp(name, root -> name) < 0)
		{
			root -> left = BusTree_Insert(root -> left, name, bus_offset, rev_offset, num_rev);
			return root;
		}
	else if (strcasecmp(name, root -> name) == 0)
		{
			root -> head = list_create(root -> head, bus_offset, rev_offset, num_rev);
			return root;
		}
	else
		{
			root -> right = BusTree_Insert(root -> right, name, bus_offset, rev_offset, num_rev);
			return root;
		}
	
}


void destroy_tree(BusinessTree * root)
{
	if (root == NULL)
		return;
	destroy_tree(root -> left);
	destroy_tree(root -> right);
	BusLoc_destroy(root -> head);
	free(root -> name);
	free(root);
}
void destroy_business_bst(struct YelpDataBST* bst)
{
	destroy_tree(bst -> treenode);
	free(bst);
	return;
}

int Length_locList(BusinessLocation * BusLoc)
{
	BusinessLocation* temp = BusLoc;
	int length = 0; // Length of the Location List

	while(temp != NULL)
	{
		length += 1;
		temp = temp -> next;		
	}	
	
	return(length);
}

void search(BusinessTree* BusLoc,char* Businessname)
{

	if(BusLoc == NULL)
	{
		printf("No Business Found\n\n");
		return;
	}

	if(strcasecmp(BusLoc -> name,Businessname) == 0)
	{
		printf("No.of Locations of the McDonald's %d\n", Length_locList(BusLoc -> head));
		
		return;		
	}
	
	else if(strcasecmp(BusLoc -> name,Businessname) < 0)
	{
		search(BusLoc -> left,Businessname);
	}
	
	else if(strcasecmp(BusLoc -> name,Businessname) > 0)
	{
		search(BusLoc -> right,Businessname);
	}
	
	return;	
}
/*
int main()
{
	YelpData * new = create_business_bst("bus.tsv", "reviews.tsv"); ///home/shay/a/ece264p0/share/yelp_data/businesses.tsv", "/home/shay/a/ece264p0/share/yelp_data/reviews.tsv");
	
	search(new -> treenode,"Ruby's Diner");
	
	destroy_business_bst(new);
	return EXIT_SUCCESS;
}
*/

struct Business* get_business_reviews(struct YelpDataBST* bst, char* name, char* state, char* zip_code)
{
	/*
	//FILE * busptr = fopen(bst -> bus, "r");
	//FILE * revptr = fopen(bst -> reviews, "r");
	struct Business * bus_get = reviews_get(bst -> business, bst -> reviews, bst -> treenode, name, state, zip_code);
	//fclose(revptr);
	//fclose(busptr);
	return (bus_get);
	*/
return NULL;
}
/*
struct Business * reviews_get(FILE *, FILE *, BusinessTree *, char *, char *, char *);
struct Business * reviews_get(FILE * busptr, FILE * revptr, BusinessTree * tree, char * name, char * state, char * zip_code)
{
	int length = 0;
	uint32_t size_list;
	if (tree == NULL)
		{
			return NULL;
		}
	if (strcasecmp(name, tree -> name) > 0)
		return (reviews_get(bustptr, revptr, tree -> right, name, state, zip_code));
	if (strcasecmp(name, tree -> name) < 0)
		return (reviews_get(busptr, revptr, tree -> left, name, state, zipcode));
	else
		struct Business * new_bus = malloc(sizeof(struct Business));
		char * string1 = malloc(BUFSIZE * sizeof(char));
		char * string2 = malloc(BUFSIZE * sizeof(char));
		int ind = 100;
		new_bus -> name = strdup(tree -> name);
		BusinessLocation * second_bus = tree -> location;
		size_list = length_list(second_bus);
		new_bus -> num_locations = size_list;
		new_bus -> locations = malloc(size_list * sizeof(struct BusinessLocation));
		
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1; 
#define FALSE 0;

int main(int argc, char * * argv)
{
  int return_Variable = 1;
  int new_counter = 0;
  FILE * string;
  int abort1 = FALSE;
  int invert1 = FALSE;
  int line_number = FALSE;
  int quiet = FALSE;
  //int match = FALSE;
  int badswitch = FALSE;
  int lcv;
  for (lcv = 1; lcv < argc; lcv++)
    {
      if (strcmp(argv[lcv], "--help") == 0)
	{
	  printf("Usage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n-v, --invert-match     print non-matching lines\n-n, --line-number      print line numbers with output\n-q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.\n");
	  return EXIT_SUCCESS;
	}
    }
  int index1;
  for(index1 = 1; index1 < argc-1; index1++)
    {
      if (strcmp(argv[index1], "-v") == 0 || strcmp(argv[index1], "--invert-match") == 0)
	{
	  invert1 = TRUE;
	}
      if (strcmp(argv[index1], "-n") == 0 || strcmp(argv[index1], "--line-number") == 0)
	{
	  line_number = TRUE;
	}
      if (strcmp(argv[index1], "-q") == 0 || strcmp(argv[index1], "--quiet") == 0)
	{
	  quiet = TRUE;
	}
      if(argv[argc - 1][0] ==  '-')
	{
	  abort1 = TRUE;
	  return 2;
	}
       if (!invert1 && !quiet && !line_number)
	{
	badswitch = TRUE;
	fprintf(stderr, "Aborting... \n");
        return 2;
	}

    }
  if (!badswitch) //(badswitch == FALSE)
    {
      char buffer[2001];
      string = stdin;
      while (fgets(buffer, 2001, string) != NULL)
	{
	new_counter++;
	 
	  
	    
	      if (invert1)
		{
		  if (strstr(buffer, argv[argc -1]) == NULL)// not a match
		    {
			return_Variable = 0;
		      if (!quiet)
			{
			  if (line_number)
			    {
			      printf("%d:", new_counter);
			      
			    }
			  printf("%s", buffer);
			}
		      
		    }
		  
		}
	    
	      else 
		{
		  if  (strstr(buffer, argv[argc -1]) != NULL)
		    {
		    return_Variable = 0;
		    if (!quiet)
			{

			  if (line_number)
			    {
			      printf("%d:", new_counter);
			      
			    }
			  printf("%s", buffer);
			}
		    }	
		    }
		
		}
	    }
	


return (return_Variable);
    }


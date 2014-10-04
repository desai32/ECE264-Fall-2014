#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
    int lcv;
    if (argc < 2)
    {
    printf("\n");
    }
   
    for(lcv = 1; lcv < argc - 1; lcv++)
    {
        printf("%s%s", argv[lcv], " ");
    }
    if (argc > 1)
{
    printf("%s%s", argv[argc - 1], "\n");
}
    return EXIT_SUCCESS;

}


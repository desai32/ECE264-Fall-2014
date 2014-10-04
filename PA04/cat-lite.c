#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
int lcv;
FILE * file_ptr1;
char cpy_string1;
if (argc == 1)
{
file_ptr1 = stdin;
while(feof(file_ptr1) == 0)
{
cpy_string1 = fgetc(file_ptr1);
if (feof(file_ptr1) == 0)
{
printf("%c", cpy_string1);
}
}
}
for (lcv = 1; lcv < argc; lcv++)
{
if (strcmp(argv[lcv], "--help") == 0)
{
printf("Usage: cat-lite [--help] [FILE]...\nWith no FILE, or when FILE is -, read standard input.\n\nExamples:\ncat-lite README   Print the file README to standard output.\ncat-lite f - g    Print f's contents, then standard input,\nthen g's contents.\ncat-lite          Copy standard input to standard output.\n");
return EXIT_SUCCESS;
}
}
FILE * file_ptr;
char copy;
int ind;
char cpy_string;
for (ind = 1; ind < argc; ind++)
{
file_ptr= fopen(argv[ind], "r");
if (strcmp(argv[ind], "-") == 0)
{
FILE * dash_input = stdin;
while (feof(dash_input) == 0)
{
cpy_string = fgetc(dash_input);
if (feof(dash_input) == 0)
{
printf("%c", cpy_string);
}
}
}
else if (file_ptr == NULL)
{
fprintf(stderr, "stderr: cat cannot open %s\n", argv[ind]);
return EXIT_FAILURE;
}
else
{
while ((copy = fgetc(file_ptr)) != EOF)
{
printf("%c", copy);
}
fclose(file_ptr);
}
}

return EXIT_SUCCESS;
}



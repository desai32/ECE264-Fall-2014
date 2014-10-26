#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer07.h"

Image * Image_load(const char * filename)
{
int read_header;
int read;
int read1;
int read2;
FILE * fptr = NULL;
ImageHeader header; //= NULL;
Image * img; //= NULL;
fptr = fopen(filename, "rb");
if ( fptr == NULL)
	{
		return NULL;
	}
read_header = fread(&header, sizeof(ImageHeader), 1, fptr);
if (read_header != 1)

{
fprintf(stderr, "Failed to open file '%s'\n", filename);
return NULL;
}
if (header.magic_number != ECE264_IMAGE_MAGIC_NUMBER)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
return NULL;
}
if (header.width == 0 || header.height == 0)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
return NULL;
}
if (header.comment_len == 0)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
return NULL;
}

img = malloc(sizeof(Image));
if (img == NULL)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
return NULL;
}
img->width = header.width;
img->height = header.height;
img->comment = malloc(header.comment_len * sizeof(char));
if (img->comment == NULL)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
return NULL;
}
img->data = malloc(sizeof(unsigned char) * img->width * img->height);
if (img ->data == NULL)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
return NULL;
}
read = fread(&img->comment, (sizeof(char *) * header.comment_len), 1, fptr);
if (read != 1)
{
return NULL;
}
read1 = strchr(img->comment, '\0');
if (read1 == NULL)
{
return NULL;
}

read2 = fread(&img->data, (sizeof(unsigned char) * header.width * header.height), 1, fptr);
if (read2 == 0)
{
return NULL;
}

if (fgetc(fptr) != EOF)
{
return NULL;
}
fclose(fptr);
return &img;
}

int Image_save(const char * filename, Image * image)
{
return 0;
}

void Image_free(Image * image)
{
if (image != NULL)
{
free(image->data);
free(image->comment);
free(image);
}
}

void linearNormalization(int width, int height, uint8_t * intensity) 
{
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer07.h"

Image * Image_load(const char * filename)
{
int read_header;
int read;
//int read1;
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
fclose(fptr);
return NULL;
}
if (header.magic_number != ECE264_IMAGE_MAGIC_NUMBER)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
fclose(fptr);
return NULL;
}
if (header.width == 0 || header.width > 16000000 || header.height == 0 || header.height > 16000000)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
fclose(fptr);
return NULL;
}
if (header.comment_len == 0 || header.comment_len > 16000000)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
fclose(fptr);
return NULL;
}

img = malloc(sizeof(Image));
if (img == NULL)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
fclose(fptr);
free(img);
return NULL;
}
img->width = header.width;
img->height = header.height;
img->comment = malloc(header.comment_len * sizeof(char));
if (img->comment == NULL)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
fclose(fptr);
//free(img);
free(img->comment);
free(img);
return NULL;
}
img->data = malloc(sizeof(unsigned char) * img->width * img->height);
if (img ->data == NULL)
{
fprintf(stderr, "Failed to open file '%s'\n", filename);
fclose(fptr);
//free(img);
free(img->comment);
free(img->data);
free(img);
return NULL;
}
read = fread(img->comment, (sizeof(char) * header.comment_len), 1, fptr);
if (read != 1 || img->comment[header.comment_len - 1] != '\0')
{
fclose(fptr);
free(img->comment);
free(img->data);
free(img);
return NULL;
}

read2 = fread(img->data, (sizeof(uint8_t) * header.width * header.height), 1, fptr);
if (read2 != 1)
{
fclose(fptr);
free(img->comment);
free(img->data);
free(img);
return NULL;
}
uint8_t byte_check;
if (fread(&byte_check, sizeof(uint8_t),1 , fptr) != 0)
{
fclose(fptr);
free(img->comment);
free(img->data);
free(img);
return NULL;
}
/*
if (fgetc(fptr) != EOF)
{
return NULL;
}*/
fclose(fptr);
return img;
}

int Image_save(const char * filename, Image * image)
{
ImageHeader header_1;
header_1.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
header_1.width = image->width;
header_1.height = image->height;
header_1.comment_len = strlen(image->comment) + 1;
FILE * fptr = NULL;
fptr = fopen(filename, "w");
if (fptr == NULL)
{
return 0;
}
if (fwrite(&(header_1), sizeof(ImageHeader), 1, fptr) != 1)
{
fclose(fptr);
return 0;
}
if (fwrite((image->comment), sizeof(char), header_1.comment_len , fptr) != header_1.comment_len)
{
fclose(fptr);
return 0;
}
if (fwrite((image->data), sizeof(unsigned char) * header_1.height * header_1.width, 1, fptr) != 1)
{
fclose(fptr);
return 0;
}
fclose(fptr);
return 1;
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
int ind;
int minimum = intensity[0];
int maximum = intensity[0];
int lcv;
for (ind = 0; ind < width * height; ind++)
{
if (minimum > intensity[ind])
{
minimum = intensity[ind];
}
if (maximum < intensity[ind])
{
maximum = intensity[ind];
}
}
for (lcv = 0; lcv < width * height; lcv++)
{
intensity[lcv] = (intensity[lcv] - minimum) * 255.0 / (maximum - minimum);
}
}

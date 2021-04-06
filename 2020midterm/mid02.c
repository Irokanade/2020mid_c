#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

struct _sBmpHeader
{
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__));

typedef struct _twoByteColor {
    uint16_t blue:5;
    uint16_t green:6;
    uint16_t red:5;
}__attribute__((__packed__)) twoByteColor; 

typedef struct _sBmpHeader sBmpHeader;

int main() {
    FILE *pFile = NULL;
    FILE *pFile2 = NULL;
    char fileName[129];
    char resultName[129];   
    sBmpHeader header1;
    sBmpHeader header2;

    printf("sizeof: %ld\n", sizeof(twoByteColor));

    printf("Please enter the image input name: ");
    fgets(fileName, 129, stdin);
    if(fileName[strlen(fileName) - 1] == '\n') {
        fileName[strlen(fileName) - 1] = 0;
    }    

    printf("fileName: %s\n", fileName);

    if((pFile = fopen(fileName, "r")) == NULL) {
        printf("Error when opening the file\n");
        return 1;
    }

    printf("Please enter the image output name: ");
    fgets(resultName, 129, stdin);
    if(resultName[strlen(resultName) - 1] == '\n') {
        resultName[strlen(resultName) - 1] = 0;
    }    

    printf("resultName: %s\n", resultName);

    if((pFile2 = fopen(resultName, "w")) == NULL) {
        printf("Error when opening the file\n");
        return 1;
    }

    fread(&header1, 54, 1, pFile);
    header2 = header1;

    header2.bpp = 16;
    header2.size = 54+((header2.width*header2.height*header2.bpp)/8);
    header2.bitmap_size = (header2.width*header2.height*header2.bpp)/8;

    fwrite(&header2, 54, 1, pFile2);

    while(!feof(pFile)) {
        int blue;
        int green;
        int red;
        twoByteColor newColor;
        fread(&blue, 1, 1, pFile);
        fread(&green, 1, 1, pFile);
        fread(&red, 1, 1, pFile);
        newColor.blue = blue&00011111;
        newColor.green = green&00111111;
        newColor.red = red&0011111;
        fwrite(&newColor, 2, 1, pFile2);
    }

    printf("Done!\n");

    fclose(pFile);
    fclose(pFile2);

    return 0;
}
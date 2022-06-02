#include <stdio.h>
#include <stdlib.h>
#include "compresie.h"
#include "warp.h"
#include "mesh.h"

#define MAX_WIDTH 240
#define MAX_HEIGHT 320
#define PADDING MAX_WIDTH*15

int main()
{
    FILE* inputImage  = fopen("input_240x320_P400.raw", "rb");
	FILE* outputImage = fopen("output.raw", "wb");
	if(inputImage == NULL || outputImage == NULL)
    {
        printf("Imaginea nu a putut fi deschisa\n");
        exit(1);
    }
    unsigned width = MAX_WIDTH, height = MAX_HEIGHT;

    //ALOCARE SPATIU IMAGINI
    unsigned char* inputBuffer  = (unsigned char*)malloc(sizeof(unsigned char) * width * height + PADDING);
	unsigned char* outputBuffer = (unsigned char*)malloc(sizeof(unsigned char) * width * height + PADDING);

    //CITIRE IMAGINE
	unsigned int bytesLoaded = fread(inputBuffer, 1, width * height, inputImage);

	//ERORI
    if(bytesLoaded!=width * height) {
        if(feof(inputImage)){
	        printf("End of file!\n");
	    }
        if(ferror(inputImage)){
            printf("Error reading from file.\n");
        }
        printf("Could not read from stream enough bytes.\n");
        printf("Expected %u, loaded %u bytes\n", width*height, bytesLoaded);
        exit(1);
    }

    //UMPLERE 15 RANDURI CU ULTIMA LINIE CITITA
    int i,j;
    for(i=0; i<width; i++)
        for(j=0; j<15; j++)
            *(inputBuffer + (height+j)*width + i) = *(inputBuffer + (height-1)*width + i);

    apply_warp(width, height, inputBuffer, outputBuffer, 21, 16, mesh_x, mesh_y);


    //SCRIERE IMAGINE
    fwrite(outputBuffer, 1, sizeof(unsigned char) * width * height, outputImage);

    //CHESTII DE FINAL
	fclose(outputImage);

	free(inputBuffer);
	free(outputBuffer);

    fclose(inputImage);

    /*char matrice[64] = {-18, 40, 48, 54, 42, 31, 6, 17, 38, 40, 36, 33, 37, 43, 31, 13, 18, -10, -4, -6, -9, 17, 34, 16, -26, -94, -106, -103, -90, -17, 18, 31, -21, -79, 2, 31, -126, -99, -11, 36, -33, -57, 25, 79, -113, -98, -6, 22, -16, -107, -128, -109, -128, -98, 4, 7, 35, 1, -45, -61, -59, -21, 11, 31};
    char transform[64];

    compresie8x8(0, 0, matrice, transform);

    unsigned i, j;
    for(i = 0; i < 8; ++i)
    {
        for(j = 0; j < 8; ++j)
            printf("%d ", transform[i * 8 + j]);
        puts("");
    }*/
    return 0;
}

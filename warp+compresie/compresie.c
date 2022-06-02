#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define pi 3.14159265359

float TCD[8][8] = {
{0.420448, 0.420448, 0.420448, 0.420448, 0.420448, 0.420448, 0.420448, 0.420448},
{0.490393, 0.415735, 0.277785, 0.097545, -0.097545, -0.277785, -0.415735, -0.490393},
{0.461940, 0.191342, -0.191342, -0.461940, -0.461940, -0.191342, 0.191342, 0.461940},
{0.415735, -0.097545, -0.490393, -0.277785, 0.277785, 0.490393, 0.097545, -0.415735},
{0.353553, -0.353553, -0.353553, 0.353553, 0.353553, -0.353553, -0.353553, 0.353553},
{0.277785, -0.490393, 0.097545, 0.415735, -0.415735, -0.097545, 0.490393, -0.277785},
{0.191342, -0.461940, 0.461940, -0.191342, -0.191342, 0.461940, -0.461940, 0.191342},
{0.097545, -0.277785, 0.415735, -0.490393, 0.490393, -0.415735, 0.277785, -0.097545},
};

int Q[8][8] = {
{8, 16, 24, 32, 40, 48, 56, 64},
{16, 24, 32, 40, 48, 56, 64, 72},
{24, 32, 40, 48, 56, 64, 72, 80},
{32, 40, 48, 56, 64, 72, 80, 88},
{40, 48, 56, 64, 72, 80, 88, 96},
{48, 56, 64, 72, 80, 88, 96, 104},
{56, 64, 72, 80, 88, 96, 104, 112},
{64, 72, 80, 88, 96, 104, 112, 120},
};

void afisare(int* m)
{
    unsigned i, j;
    for(i = 0; i < 8; ++i)
    {
        for(j = 0; j < 8; ++j)
            printf("%d ", m[i * 8 + j]);
        puts("");
    }
    puts("");
}

void TCD_maker(unsigned n)
{
    FILE *out = fopen("TCD.txt", "w");
    if(out == NULL) exit(1);
    fprintf(out, "{\n");
    unsigned i, j;
    float radical = sqrt((float)2 / n), radical2 = sqrt((float) 1 / sqrt(2));
    fprintf(out, "{");
    for(j = 0; j < n; ++j)
    {
        fprintf(out, "%f", radical2 * radical);
        if(j < n - 1) fprintf(out, ", ");
    }
    fprintf(out, "},\n");
    for(i = 1; i < n; ++i)
    {
        fprintf(out, "{");
        for(j = 0; j < n; ++j)
        {
            fprintf(out, "%f", radical * cos((i * (2 * j + 1) * pi) / (2 * n)));
            if(j < n - 1) fprintf(out, ", ");
        }
        fprintf(out, "},\n");
    }
    fprintf(out, "};");

    if(fclose(out) != 0) exit(1);
}
void transform_coordonates(unsigned width, unsigned height, unsigned char* input, char* output)
{
    unsigned i, j;
    for(i = 0; i < height; ++i)
        for(j = 0; j < width; ++j)
            output[i * width + j] = (char) input[i * width + j] - 128;
}
void copy_matrix(int *output, int *input)
{
    unsigned i, j;
    for(i = 0; i < 8; ++i)
        for(j = 0; j < 8; ++j)
            output[i * 8 + j] = input[i * 8 + j];
}
void inmultire_TCD(char* input, int* output)
{
    unsigned i, j, x;
    float out[64], in[64];
    for(i = 0; i < 8; ++i)
        for(j = 0; j < 8; ++j)
        {
            out[i * 8 + j] = 0;
            for(x = 0; x < 8; ++x){
                out[i * 8 + j] += TCD[i][x] * input[x * 8 + j];
            }
        }

    for(i = 0; i < 8; ++i)
        for(j = 0; j < 8; ++j)
            in[i * 8 + j] = out[i * 8 + j];

    for(i = 0; i < 8; ++i)
        for(j = 0; j < 8; ++j)
        {
            output[i * 8 + j] = 0;
            for(x = 0; x < 8; ++x)
                output[i * 8 + j] += in[i * 8 + x] * TCD[j][x];
        }
}
void cuantificare(int* input, char* output)
{
    unsigned i, j;
    for(i = 0; i < 8; ++i)
        for(j = 0; j < 8; ++j)
            output[i * 8 + j] = input[i * 8 + j] / Q[i][j];
}
void compresie8x8(unsigned lin, unsigned col, char* input, char* output)
{
    unsigned i, j;
    char input_chunk[64], output_chunk[64];
    int output_TCD[64];
    for(i = 0; i < 8; ++i)
        for(j = 0; j < 8; ++j)
            input_chunk[i * 8 + j] = input[(lin + i) * 8 + col + j];

    inmultire_TCD(input_chunk, output_TCD);
    afisare(output_TCD);
    cuantificare(output_TCD, output_chunk);
}

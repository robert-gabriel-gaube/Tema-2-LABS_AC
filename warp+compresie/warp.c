#include <stdio.h>
void apply_warp(unsigned width, unsigned height, unsigned char* input, unsigned char* output, unsigned mesh_width, unsigned mesh_height, float mesh_x[mesh_height][mesh_width], float mesh_y[mesh_height][mesh_width])
{
    unsigned i, j, newi, newj, x, y;
    for(i = 0; i < height; ++i)
        for(j = 0; j < width; ++j)
            output[i * width + j] = input[i * width + j];

    for(i = 0; i < mesh_height; ++i)
        for(j = 0; j < mesh_width; ++j)
            for(x = 0; x < 8; ++x)
                for(y = 0; y < 8; ++y)
                {
                    newi = i + x + mesh_x[i][j];
                    newj = j + y + mesh_y[i][j];
                    output[newi * width + newj] = input[(i + x) * width + j + y];
                }
}

#include "convolution.h"

#include <stdlib.h>

#include "image.h"

void convolve(float *result, const float *img, int w, int h,
              const float *matrix, int w_m, int h_m) {
   
    
    if (img == NULL || result == NULL || matrix == NULL || w <= 0 || h <= 0 || w_m <= 0 || h_m <= 0) {
        return;
    } 
    
    int matLen = w_m * h_m;
    if(matLen % 2 == 0) {
        return;
    }
    int a = w_m/2;
    int b = h_m/2;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            float sum = 0.0;
            for (int j = 0; j < h_m; j++) {
                for (int i = 0; i < w_m; i++) {
                    int xCoord = x - a + i;
                    int yCoord = y - b + j;
                    float mirrorImg = get_pixel_value(img, w, h, xCoord, yCoord);
                    float kernel = matrix[j * w_m + i];
                    sum += mirrorImg*kernel;
                }
            }
            result[y*w + x] = sum;
        }
    }
}

    // TODO: Implement me!


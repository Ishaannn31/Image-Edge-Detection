#include "derivation.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "convolution.h"
#include "image.h"

void gradient_magnitude(float *result, const float *d_x, const float *d_y,
                        int w, int h) {
   
    if(w<=0 || h<=0 || d_x == NULL || d_y == NULL || result == NULL) {
        return;
    }
    int totalPix = w*h;
    double resX[totalPix],resY[totalPix],sum[totalPix],grad[totalPix];

    for(int i=0; i<totalPix; i++) {
       resX[i]  = d_x[i] * d_x[i];
       resY[i]  = d_y[i] * d_y[i];
       sum[i] = resX[i] + resY[i];
       grad[i] = sqrt(sum[i]);
       result[i]= grad[i];
    }

    
  
    // TODO: Implement me!
}

const float sobel_x[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};

const float sobel_y[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

void derivation_x_direction(float *result, const float *img, int w, int h) {
    convolve(result, img, w, h, sobel_x, 3, 3);
}

void derivation_y_direction(float *result, const float *img, int w, int h) {
    convolve(result, img, w, h, sobel_y, 3, 3);
}

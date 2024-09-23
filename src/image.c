#include "image.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void apply_threshold(float *img, int w, int h, int T) { //float *img = img[0]
   

    int totalPixels = w*h; // 1-D array

    for(int i=0; i<totalPixels; i++) {
        if(img[i]>T) {
            img[i] = 255.0;
        } else {
            img[i] = 0.0;
        }
    }

    // TODO: Implement me!
}

void scale_image(float *result, const float *img, int w, int h) {
    if(w<=0 || h<=0 || result == NULL || img == NULL) {
        return;
    }
    int totalPixels = w*h;
    float acc[totalPixels];
    float min = INT_MAX;
    float max = INT_MIN;
    
    for(int i=0; i<totalPixels; i++) {
        acc[i] = img[i];
    }
    for(int i=0; i<totalPixels; i++) {
        if(acc[i]<min) {
            min = acc[i];
        }
    }
    for(int i=0; i<totalPixels; i++) {
        if(acc[i]>max) {
            max = acc[i];
        }
    }
    for(int i=0; i<totalPixels; i++) {
        if(max==min) {
            result[i] = 0;
        } else {
        result[i]= ((acc[i]-min)/(max-min))*255;
        }
    }
   
    // TODO: Implement me!
}

float get_pixel_value(const float *img, int w, int h, int x, int y) {
   
   
   int xCoordinate,yCoordinate; 
   
   
    if(img == NULL || w <= 0 || h <= 0 ) {
        return 0.0f;
    }
   
    if(x < 0) {
        xCoordinate = (-x-1); //edge
    }
    if(y < 0) {
        yCoordinate = (-y-1); //edge
    }
    if(x >= 0 && x < w) {
        xCoordinate = x; 
    }
    if(y >= 0 && y < h) {
        yCoordinate = y; 
    }
    if(x >= w) {
        xCoordinate = (2*w)-x-1; 
    }
    if(y >= h) {
        yCoordinate = (2*h)-y-1;
    }
   if(img[yCoordinate*w + xCoordinate]>=0 && img[yCoordinate*w + xCoordinate]<=255) {
    return img[yCoordinate*w + xCoordinate];
    } else {
        return 0.0f;
    }
}




float *array_init(int size) {
   
    float *array;
     if(size<=0) {
        return NULL;
     }
    array=(float*)malloc(sizeof(float)* size);
    if(array == NULL) {
        return NULL;
    }

    // TODO: Implement me!

    return array;
}

void array_destroy(float *m) {

   if(m != NULL) {
    free(m);
    m = NULL;
   }
    // TODO: Implement me!
}

float *read_image_from_file(const char *filename, int *w, int *h) {
  
    FILE *ptr;
    ptr = fopen(filename, "r");

    if(ptr == NULL) {
        return NULL;
    } 

    char ch1,ch2;

    if((fscanf(ptr, "%c%c",&ch1,&ch2 ) != 2) || (ch1 !='P' || ch2 != '2')) {
        fclose(ptr);
        return NULL;
    }

    int maxBrightVal;
    if(fscanf(ptr, "%d %d\n%d", w, h, &maxBrightVal) != 3 || *w<=0 || *h<=0 || maxBrightVal!= 255) {
        fclose(ptr);
        return NULL;
    }
    int lengthDesArrays = (*w) * (*h);
    float *readArray = array_init(lengthDesArrays);
    if (readArray == NULL) {
        return NULL;
    }
    int counter=0;
    int pix;
    while(fscanf(ptr, "%d ", &pix) == 1) { // while(!feof(ptr))
        if(pix < 0 || pix > 255) {
            array_destroy(readArray);
            fclose(ptr);
            return NULL;
        }
        if(counter < lengthDesArrays) {
            readArray[counter] = pix;
            counter++;
        } else {
            array_destroy(readArray);
            fclose(ptr);
            return NULL;
        }
    }
    if(counter != lengthDesArrays) {
        array_destroy(readArray);
        fclose(ptr);
        return NULL;
    } 
   
    fclose(ptr);

    return readArray;
}

void write_image_to_file(const float *img, int w, int h, const char *filename) {
   
    if(img == NULL || w<=0 || h<=0 || filename == NULL) {
        return;
    }
    FILE *qtr;
    qtr = fopen(filename, "w");

    if(qtr == NULL) {
        return;
    }

    fprintf(qtr, "P2\n");
    fprintf(qtr,"%d %d\n", w,h);
    fprintf(qtr, "255\n");

    
     for(int j=0; j<h; j++) {
        for(int i =0; i<w; i++) {
             int pixelVal = (int)img[j*w +i];
             if(pixelVal < 0 || pixelVal > 255) {
             fclose(qtr);
             return;
         }
         fprintf(qtr, "%d ", pixelVal);
        }
        fprintf(qtr, "\n");
        
    }
    fclose(qtr);

    // TODO: Implement me!
}

#include <stdio.h>
#include <stdlib.h>

#include "argparser.h"
#include "convolution.h"
#include "derivation.h"
#include "gaussian_kernel.h"
#include "image.h"

int main(int const argc, char **const argv) {
    
    parse_arguments(argc, argv);
    printf("Computing edges for image file %s with threshold %i\n",
           image_file_name, threshold);

    
    int w,h;
    float *readIt;
    readIt = read_image_from_file(image_file_name, &w, &h);
    if(readIt == NULL) {
      
       return 1;
    } 
    
    float *storeRes= array_init(w*h);
    if( storeRes == NULL) {
       return 1;
    }
   
    convolve(storeRes, readIt, w, h, gaussian_k, gaussian_w, gaussian_h );
    char *outputFile = "out_blur.pgm";
    write_image_to_file(storeRes, w, h, outputFile);
    
      float *xRes = array_init(w*h);
      float *yRes = array_init(w*h);
      derivation_x_direction(xRes, storeRes, w,h);
      derivation_y_direction(yRes, storeRes, w, h);
      
     float *scaleImg1 = array_init(w*h);
     scale_image(scaleImg1, xRes, w, h);
     float *scaleImg2 = array_init(w*h);
     scale_image(scaleImg2, yRes, w, h);

     write_image_to_file(scaleImg1, w, h, "out_d_x.pgm");
     write_image_to_file(scaleImg2, w, h, "out_d_y.pgm");
     
     

      float *gradientMag = array_init(w*h);
      gradient_magnitude(gradientMag, xRes, yRes, w, h);
      float *rescaleRes = array_init(w*h);
      scale_image(rescaleRes, gradientMag, w, h);
      const char *lastFile = "out_gm.pgm";
      write_image_to_file(rescaleRes, w, h, lastFile);



      apply_threshold(gradientMag, w, h, threshold);
      const char *resFile = "out_edges.pgm";

      write_image_to_file(gradientMag, w, h, resFile);
      array_destroy(readIt);
      array_destroy(storeRes);
      array_destroy(xRes);
      array_destroy(yRes);
      array_destroy(scaleImg1);
      array_destroy(scaleImg2);
      array_destroy(gradientMag);
      array_destroy(rescaleRes);

    /**
     * Remember to free dynamically allocated memory when it is no longer used!
     */
}

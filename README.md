# Image-edge-Detection

This project implements an image edge detection algorithm in C, which detects edges in grayscale images by identifying the borders between homogeneous areas. The edge detection algorithm is widely used in various applications like object detection, artistic image filters, and image compression.

## Algorithm Overview

The edge detection algorithm follows these steps:

1. **Reading the image**: Load a PGM format grayscale image.
2. **Blurring**: Apply a Gaussian blur to reduce noise in the image.
3. **Sobel Convolution**: Compute the discrete derivative in both x and y directions using Sobel filters.
4. **Gradient Magnitude Calculation**: Calculate the magnitude of the gradient for each pixel.
5. **Thresholding**: Apply a threshold to detect edges and produce a binary (black and white) output image.
6. **Output**: Write the final image with detected edges.

## How to Build

To build the project, navigate to the project root directory and run:

```bash
make
```

This will generate an executable file `edgedetection` in the `bin/` directory.

## How to Run

To run the edge detection algorithm, use the following command:

```bash
./bin/edgedetection -T <threshold> <input_image.pgm>
```

- `<threshold>`: The threshold value for edge detection (e.g., 100).
- `<input_image.pgm>`: The path to the input image in PGM format.

For example, to run the program with a threshold of 100 on an image `img_P.pgm`, you would execute:

```bash
./bin/edgedetection -T 100 test/data/input/img_P.pgm
```

When you run the command after building the project, the output image will be generated in the root directory. This output should match the expected results found in the `tests/expected/` folder for a threshold value of 100.

## Input and Expected Output

The `tests/` folder contains test images in the `data/` subdirectory, which include various cases like broken and valid images. Expected results are provided in the `expected/` subdirectory for a threshold value of 100.

---


# Binary Handwritten-Digit Classification in C

A from-scratch 5-nearest-neighbours classifier that identifies whether a 28-by-28 grayscale image contains the digit `1`.

> University of Bristol Coursework<br>
> Mark awarded: **100/100**<br>
> Date: 12/2023 <br>

## Project overview

The program reads flattened grayscale images from binary matrix files, computes squared Euclidean distances between every test image and every training image, and classifies each test image from the labels of its five nearest neighbours.

The assignment combines low-level data handling with a complete classification pipeline: images are read from a custom binary format, stored in manually allocated matrices, compared without a machine-learning library and rendered in the terminal.

The supplied data contains:

- 1,987 training images;
- 100 test images;
- 784 pixel values per image, corresponding to a 28-by-28 grid; and
- 1,987 binary training labels, of which 219 are labelled as the digit `1`.

For each test image, the program prints an ASCII representation and predicts either `1` or `Not 1`. The supplied test set produces 17 predictions of the digit `1`.

## Input representation

Each `.matrix` file begins with two integers giving the number of rows and columns, followed by the matrix entries. Images are flattened in row-major order, so each row of `X.matrix` or `T.matrix` contains one complete image.

- `X.matrix` has shape `1987 × 784` and stores the training images.
- `T.matrix` has shape `100 × 784` and stores the test images.
- `Y.matrix` has shape `1987 × 1` and stores the binary training labels.

Pixel values are integers from the grayscale images. `image2char(...)` maps lower-intensity pixels to spaces, mid-range pixels to `I` and high-intensity pixels to `M`, allowing each 28-by-28 image to be inspected in the terminal.

## Classification algorithm

For test image $T_i$ and training image $X_j$, the program calculates

$$
D_{ij}=\sum_{p=1}^{784}(T_{ip}-X_{jp})^2.
$$

Each row of $D$ therefore contains the distances from one test image to all 1,987 training images. The five smallest entries identify its nearest neighbours. If at least three of their labels equal `1`, the test image is classified as `1`; otherwise it is classified as `Not 1`.

## Implementation

The main functions are:

- `read_matrix(filename)`: reads the dimensions and values from a binary matrix file.
- `get_elem(M, i, j)` and `set_elem(M, i, j, value)`: access the flattened row-major storage.
- `pairwise_dist2(M1, M2, D)`: fills the complete pairwise squared-distance matrix.
- `find_min_index(a, len)`: finds the location of the smallest array element.
- `minimum5(a, len, indices)`: repeatedly finds and records the five smallest entries.
- `image2char(image, Height, Width)`: prints a grayscale image using ASCII characters.

`main()` loads the three matrices, constructs the `100 × 1987` distance matrix, classifies each test image, reports the predictions and frees all dynamically allocated memory.

## Repository contents

The executable expects all four input files in the same directory:

```text
.
├── image_to_char.c    # Classifier implementation
├── X.matrix           # Training images
├── T.matrix           # Test images
├── Y.matrix           # Training labels
└── README.md
```

## Building and running

Using GNU GCC:

```bash
gcc -std=c11 image_to_char.c -lm -o image_to_char
./image_to_char
```

The original submission declares `void main()`. GNU GCC accepts this with a warning, but modern Apple Clang rejects it in its default hosted mode. On macOS with Clang, the preserved source can be compiled as a freestanding program:

```bash
clang -std=c11 -ffreestanding image_to_char.c -lm -o image_to_char
./image_to_char
```

## Scope and limitations

This is a binary `1`-versus-`not 1` classifier rather than a ten-class digit recogniser. The number of neighbours, image dimensions and input filenames are fixed in the source. Test labels are not included, so the repository can reproduce the predictions but cannot calculate test accuracy.

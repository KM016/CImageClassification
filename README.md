# CImageClassification

Date: 12/2023 <br>
University Project

# The Task

The goal of this project is to implement a simple image-to-text conversion algorithm using C. The task is to convert images, represented as matrices, into textual representations of characters. This project is part of the coursework and aims to demonstrate the application of matrix operations and file handling in C.

## Input

The input consists of images, each represented as a matrix of pixels. These grayscale images are flattened into 1D arrays (vectors) where each element represents the brightness of a pixel.

- **Training Data**: A matrix where each row corresponds to a grayscale image.
- **Test Data**: Another matrix that needs to be classified based on the training data.
- **Labels**: A 1D matrix indicating whether the corresponding image represents a digit or a character.

## Output

The program outputs the character label associated with the given test image based on the image data provided in the matrices.

# The Algorithm

This project uses a basic image classification approach to convert images into their respective characters. The key algorithm used is the **K-Nearest Neighbors (K-NN)** classifier. Here's how it works:

1. **Data Representation**: The images are stored in a matrix format where each row is a flattened grayscale image. The brightness values of each pixel are represented as integers.

2. **Distance Calculation**: For each test image, the squared Euclidean distance is calculated between the test image and all images in the training set. This is done using a distance matrix D:

    $D(i, j) = \text{Squared Euclidean Distance } (T[i], X[j])$

    where $T[i]$ is the $i^{th}$ test image and $X[j]$ is the $j^{th}$ training image.

3. **K-Nearest Neighbors**: Once the distance matrix is computed, the algorithm finds the K nearest neighbors (images with the smallest distances) for each test image. For this project, \( K = 5 \).

4. **Classification**: For each test image, the algorithm checks the labels of its nearest neighbors. It counts how many neighbors are associated with the digit "1". If 3 or more of the 5 nearest neighbors are labeled "1", the algorithm predicts the label "1" for the test image. Otherwise, it predicts "Not 1".

5.  **Output:** The algorithm outputs whether each test image is classified as a "1" or "Not 1".

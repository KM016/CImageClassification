#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

struct matrix
{
    int numrow;
    int numcol;
    int *elements;
};
typedef struct matrix Matrix;

/*
Print an image to the console. 
image: an array stores the flattened image stored in row major order.
Height: the height of the image.
Width: the width of the image.
*/
void image2char(int image[], int Height, int Width)
{
    for(int i = 0; i<Height; i++){
        for(int j = 0; j<Width; j++){
            if(image[i*(Width) + j] < 85){
                printf("  ");
            }
            else if(image[i*(Width) + j] < 170){
                printf("I ");
            }
            else{
                printf("M ");
            }
        }
        printf("\n");
    }
    
    
}


/*
Read a matrix from file. Don't change it!
filename: the file that contains the matrix.
return: a matrix structure containing the matrix.
*/
Matrix read_matrix(char *filename)
{
    FILE *f = fopen(filename, "rb");
    // read int variables to the file.
    int numrow = getw(f);
    int numcol = getw(f);
    Matrix M = {numrow, numcol, calloc(numrow * numcol, sizeof(int))};

    for (int i = 0; i < M.numrow; i++)
    {
        for (int j = 0; j < M.numcol; j++)
        {
            M.elements[i*numcol + j] = getc(f);
        }
    }

    fclose(f);
    return M;
}

/*
Retrieve an element from a matrix.
M: the matrix.
i,j: the row and column of the element.
return: the element at row i and column j.
*/
int get_elem(Matrix M, int i, int j)
{
//returns the i,jth element of M
    return M.elements[(i*M.numcol)+j];
}

/*
Assign value to an element in a matrix.
M: the matrix.
i,j: the row and column of the element.
value: the value to be assigned.
*/
void set_elem(Matrix M, int i, int j, int value)
{
// sets the i,j th element of M to value 
    M.elements[(i*M.numcol)+j] = value;
}

/*
Compute the pairwise squared distance of the i-th row of M1 and the j-th row of M2.
M1: the first matrix.
M2: the second matrix.
return: a matrix D where D_ij is the squared distance between the i-th row of M1 and the j-th row of M2.
*/
void pairwise_dist2(Matrix M1, Matrix M2, Matrix D)
{
//calculates the pairwise distance between the ith row of M1 and jth row of M2 and makes a matrix D out of the outputs 
    for (int i = 0; i < M1.numrow; i++){
        for (int j = 0; j < M2.numrow; j++){

            int sum = 0;

            for (int k = 0; k < M1.numcol; k++){
                int diff = get_elem(M1,i,k) - get_elem(M2,j,k);

                sum += diff * diff;

            }

            set_elem(D,i,j,sum);
        }
    }
}

// prints out a matrix
void print(struct matrix D){
    for(int i = 0; i < D.numrow; i++){
        for(int j = 0; j< 20; j++){
            printf("%d ", get_elem(D,i,j));
        }
        printf("\n");
    }
}

/*
Find the index of the minimum element in an array. 
a: the array.
len: the length of the array.
return: the index of the minimum element in the array.
example: [1,2,3,4,5] -> 0
         [5,4,3,2,1] -> 4
*/
int find_min_index(int a[], int len)
{
//finding the index of the smallest element in any array passed into the function 
    int min = a[0];
    int min_index = 0;
    for(int i = 0; i<len; i++){
        if(a[i] < min){
            min = a[i];
            min_index = i; 
        }
    }

    return min_index;
}

/*
Find the indices of 5 minimum elements in an array.
a: the array.
len: the length of the array.
return: an array of 5 integers containing the indices of the 5 minimum elements in a.
example: [1,2,33,4,5,23,6] -> [0,1,3,4,6]
*/
void minimum5(int a[], int len, int indices[])
{
//used the find_min_index to find the minimum element and sets it to INT_MAX so it can find the next smallest element 
    for(int i = 0; i<5; i++){
        int min = find_min_index(a, len);
        a[min] = INT_MAX;
        indices[i] = min;
    }   
    
}

void main()
{
    Matrix X = read_matrix("./X.matrix");
    printf("N: %d, M: %d\n", X.numrow, (int) sqrt(X.numcol));   

    Matrix T = read_matrix("./T.matrix");
    printf("L: %d\n", T.numrow);

    Matrix Y = read_matrix("./Y.matrix");
    int s = 0;
    for (int i = 0; i < Y.numrow; i++)
    {
        if(Y.elements[i*Y.numcol + 0] == 1)
            s++;
    }
    printf("Number of 1 in the training set: %d\n", s);


    // creating a matrix D
    int *D_elements = malloc(T.numrow * X.numrow * sizeof(int));
    Matrix D = {T.numrow, X.numrow, D_elements};

//calculating the elements of D
    pairwise_dist2(T,X,D);

//keeps a total of the number of 1s
    int total_1 = 0;


    for(int i=0; i< T.numrow; i++){ // replace 0 with T.numrow.
        printf("The %d-th testing image:\n", i);

// visualising the numbers 
        image2char(T.elements + (i*T.numcol),28,28);

//getting the ith row of D
        int row_i[D.numcol];
        int indices[5];

        for(int j =0; j < D.numcol; j ++){
            row_i[j] = get_elem(D,i,j);
        }

// getting the indexes of the minimum 5 elements of D
        minimum5(row_i, D.numcol, indices);
        // for(int o = 0; o < 5; o ++){
        //     printf("%d ", row_i[o]);
        // }

// guessing the labels
        int labels[5];
        int count = 0;

        for(int k = 0; k<5; k++){
            labels[k] = get_elem(Y, indices[k], 0);
            if(labels[k] == 1){
                count += 1;
            }

        }

        // print(D);
        
//printing the outcome
        printf("The %d-th testing image is classified as", i);

         if(count >= 3){
            printf(" 1");
            total_1 += 1;
        }
        else{
            printf(" Not 1");
        }

        printf("\n");
        printf("----------------------------------------\n");

    }

//prints the total number of 1s
    printf("The total number of 1s is %d ", total_1);



    free(X.elements);
    free(T.elements);
    free(Y.elements);
    free(D_elements);
}
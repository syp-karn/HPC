#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 10000   
#define threads 5

double seq_implem(int **A, int *x_arr, int n) {
    int *y_arr = calloc(n, sizeof(int));
    double start = omp_get_wtime();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y_arr[i] += A[i][j] * x_arr[j];
        }
    }

    double end = omp_get_wtime();
    free(y_arr);
    return end - start;
}

double parallel_1D(int **A, int *x_arr, int n) {
    int *y_arr = calloc(n, sizeof(int));
    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y_arr[i] += A[i][j] * x_arr[j];
        }
        
    }

    double end = omp_get_wtime();
    free(y_arr);
    return end - start;
}

double parallel_2D(int n, int P, int Q, int num_threads, int **A, int *x) {
    int *y = calloc(n, sizeof(int));
    double start = omp_get_wtime();

    int block_rows = n / P;
    int block_cols = n / Q;

    #pragma omp parallel for collapse(2) num_threads(num_threads) reduction(+:y[:n])
    for (int bi = 0; bi < P; bi++) {         
        for (int bj = 0; bj < Q; bj++) {     
            for (int i = 0; i < block_rows; i++) {
                for (int j = 0; j < block_cols; j++) {
                    int global_i = bi * block_rows + i;
                    int global_j = bj * block_cols + j;
                    y[global_i] += A[global_i][global_j] * x[global_j];
                }
            }
        }
    }

    double end = omp_get_wtime();
    free(y);
    return end - start;
}

int main() {
    int **A = malloc(MAX * sizeof(int *));
    for (int i = 0; i < MAX; i++) {
        A[i] = malloc(MAX * sizeof(int));
    }

    int *x = malloc(MAX * sizeof(int));
    FILE *f = fopen("values.dat", "w");
    for (int n = 500; n <= 10000; n += 500) {
        for (int i = 0; i < n; i++) {
            x[i] = 1;
            for (int j = 0; j < n; j++) {
                A[i][j] = i + j;
            }
        }

        double seq_time = seq_implem(A, x, n);
        fprintf(f, "%d seq %f\n", n, seq_time);

        double par1_time = parallel_1D(A,x,n);
        fprintf(f, "%d par1 %f\n", n, par1_time);

        double par2_time = parallel_2D(n,2,2,threads,A,x);
        fprintf(f, "%d par2 %f\n", n, par2_time);
    }

    fclose(f);

    for (int i = 0; i < MAX; i++) free(A[i]);
    free(A);
    free(x);

    printf("Results saved to values.dat\n");
    return 0;
}

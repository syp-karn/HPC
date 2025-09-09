#include <stdio.h>
#include <omp.h>

#define MAX 2000   // largest matrix size we want to test
#define threads 6

double multiply_seq(int A[MAX][MAX], int x_arr[MAX], int n) {
    int y_arr[MAX] = {0};
    double start = omp_get_wtime();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y_arr[i] += A[i][j] * x_arr[j];
        }
    }

    double end = omp_get_wtime();
    return end - start;
}

double parallel_1D(int A[MAX][MAX], int x_arr[MAX], int n) {
    int y_arr[MAX] = {0};
    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y_arr[i] += A[i][j] * x_arr[j];
        }
    }

    double end = omp_get_wtime();
    return end - start;
}

int main() {
    int A[MAX][MAX];
    int x[MAX];

    FILE *f = fopen("results.dat", "w");

    for (int n = 500; n <= 2000; n += 500) {
        for (int i = 0; i < n; i++) {
            x[i] = 1;
            for (int j = 0; j < n; j++) {
                A[i][j] = i + j;
            }
        }
        double seq_time = multiply_seq(A, x, n);
        fprintf(f, "%d %d %f\n", n, 1, seq_time);

        double par_time = parallel_1D(A, x, n);
        fprintf(f, "%d %d %f\n", n,par_time);
    }

    fclose(f);
    printf("Results saved to results.dat\n");
    return 0;
}

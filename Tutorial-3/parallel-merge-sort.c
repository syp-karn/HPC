#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_THRESHOLD 10000 

typedef struct {
    int *arr;
    int left;
    int right;
} thread_data;

void merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void* merge_sort(void *arg);

void exec_merge(int *arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;

    if (right - left > THREAD_THRESHOLD) {
        pthread_t t1, t2;
        thread_data d1 = {arr, left, mid};
        thread_data d2 = {arr, mid + 1, right};
        pthread_create(&t1, NULL, merge_sort, &d1);
        pthread_create(&t2, NULL, merge_sort, &d2);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
    } else {
        exec_merge(arr, left, mid);
        exec_merge(arr, mid + 1, right);
    }

    merge(arr, left, mid, right);
}

void* merge_sort(void *arg) {
    thread_data *data = (thread_data *)arg;
    exec_merge(data->arr, data->left, data->right);
    return NULL;
}

int main() {
    int n = 30;
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = rand() % 100;

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    thread_data d = {arr, 0, n - 1};
    merge_sort(&d);

    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            printf("Sort failed!\n");
            free(arr);
            return 1;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}

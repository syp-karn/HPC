#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>


int main(){
    omp_set_num_threads(4);
    int m = 100;                        

    int v1[100];
    int v2[100];

    srand(time(NULL));

    int indices[100];

    for (int i = 0; i < m; i++) {
        v1[i] = rand() % 100;   // random number between 0–99
        v2[i] = v1[i];          // copy to v2 for consistency
        indices[i] = rand() % 10;
    }

#pragma omp parallel for default(none) shared (v1, indices, m)
for(int i=0;i<m;i++){
    v1[indices[i]] += 1;
}

#pragma omp parallel for default(none) shared (v2, indices, m)
for(int i=0;i<m;i++){
    #pragma omp critical
    v2[indices[i]] += 1;
}


for (int i = 0; i < m; i++) {
        printf("%d ", v1[i]);
    }
printf("\n");
for (int i = 0; i < m; i++) {
        printf("%d ", v2[i]);
    }
}
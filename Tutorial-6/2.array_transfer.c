#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    
    int rank, size, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int arr[1000000];
    int arr_sz = sizeof(arr)/sizeof(arr[0]);
    for (i=0;i< (sizeof(arr)/sizeof(arr[0],i++)){
        arr[i] = 1;
    }

    int chunk_size = arr_sz / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? n : start + chunk_size;

    if(rank==0){
            for(i=0; i<n;i++){
                MPI_Send(&arr[])
            }
    }


}
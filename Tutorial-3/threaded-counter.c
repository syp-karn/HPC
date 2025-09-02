#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

# define N 2

void* increment(void* arg){
    for (int i=0;i<1000000;i++){
        (*(int*)arg)++;
    }   
    return NULL;
} 

int main(){
    pthread_t threads[N];
    int counter=0;
    for (int 
}
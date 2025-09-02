#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

# define N 2

pthread_mutex_t lock;

void* increment(void* arg){
    int* counter = (int*)arg;
    for (int i=0;i<1000000;i++){
        pthread_mutex_lock(&lock);
        (*counter)++;
        pthread_mutex_unlock(&lock);
    }   
    return NULL;
} 

int main(){
    pthread_t threads[N];
    int counter=0;

    pthread_mutex_init(&lock, NULL); 

    for (int i=0; i<N;i++){
           pthread_create(&threads[i],NULL,increment,&counter); 
}
    for (int i=0; i<N; i++){
           pthread_join(threads[i],NULL);
}
    
    pthread_mutex_destroy(&lock);
    printf("Final counter value: %d",counter);
    return 0;
}

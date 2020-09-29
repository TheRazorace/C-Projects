#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#define pi 3.14159265
#define N 100000

int thread_count;
pthread_mutex_t mutex;
long long n;
double sum;
int x[N];

float single_thread_compute(int arr[]);
void create_random_vector(int arr[]);
void single_thread_evaluate(int arr[]);
void *quad_thread_compute(void *rank);
void quad_thread_evaluate();


int main(int argc, char *argv[]) {
	srand((unsigned int)time(NULL));
	
	
	create_random_vector(x);
	sum = 0.0;
	single_thread_evaluate(x);
	
	n = 1e7;

    if (argc > 2) {
        thread_count = atoi(argv[1]);
        n = atoi(argv[2]);
    }
    sum = 0.0;
	quad_thread_evaluate();


	return 0;
}

void create_random_vector(int arr[]){
	int i;
	for (i=0; i<N; i++){
		arr[i] = rand()%360;
	}
}


float single_thread_compute(int arr[]){
	int i;
	float val = pi/180;
	for (i=0; i<N; i++){
		sum += (sin(arr[i]*val))*(sin(arr[i]*val)) + (cos(arr[i]*val))*(cos(arr[i]*val)) ; 
	}
	return sum;
}

void single_thread_evaluate(int arr[]){
	struct timeval t0, t1;
	float sum;
	int a;
	
	gettimeofday(&t0, NULL);
	sum = single_thread_compute(arr);
    gettimeofday(&t1, NULL);
    printf("Size of table: %d\n", N);
    printf("Single thread sum = %.2lf time = %.3lf\n\n", 
        sum, (t1.tv_sec - t0.tv_sec + ((double)t1.tv_usec-t0.tv_usec)/1e6));
         
}

void quad_thread_evaluate(){
	long t; 
    pthread_t *thread_handles;
	thread_count = 4;

    thread_handles = (pthread_t *)malloc(thread_count * sizeof(pthread_t)); 
    pthread_mutex_init(&mutex, NULL);
    
    struct timeval t0, t1;
    
    gettimeofday(&t0, NULL);
    for (t = 0; t < thread_count; t++)
        pthread_create(&thread_handles[t], NULL,
                       quad_thread_compute, (void *)t);

    for (t = 0; t < thread_count; t++)
        pthread_join(thread_handles[t], NULL);

    gettimeofday(&t1, NULL);
    
    printf("With n = %lld terms, threads=%d\n", n, thread_count);
    printf("Quad thread result = %.2f time = %.3lf\n", 
            sum, (t1.tv_sec - t0.tv_sec + ((double)t1.tv_usec-t0.tv_usec)/1e6));
            
    pthread_mutex_destroy(&mutex);
    free(thread_handles);
}

void *quad_thread_compute(void *rank){
	long my_rank = (long)rank;
    double my_sum = 0;
    long long i;
    float val = pi/180;

    long long my_n = n / thread_count;
    
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;

    if (my_rank == thread_count - 1) my_last_i = n;

    for (i = my_first_i; i < my_last_i; i++) {
        my_sum += (sin(x[i]*val))*(sin(x[i]*val)) + (cos(x[i]*val))*(cos(x[i]*val)) ;
    }
    pthread_mutex_lock(&mutex);
    sum += my_sum;
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}
    




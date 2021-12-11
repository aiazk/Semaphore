#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define MaxItems 10 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 10 // Size of the buffer
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;
void producer(int pno)
{
 int item;
 int i;
 for( i = 0; i < MaxItems; i++) {
 item = rand(); // Produce an random item
 sem_wait(&empty);
 pthread_mutex_lock(&mutex);
 buffer[in] = item;
 printf("Producer %d: Insert Item %d at %d\n", pno,buffer[in],in);
 in = (in+1)%BufferSize;
 pthread_mutex_unlock(&mutex);
 sem_post(&full);

 }
}
void consumer(int cno)
{
int i;
 for( i = 0; i < MaxItems; i++) {
 sem_wait(&full);
pthread_mutex_lock(&mutex);
 int item = buffer[out];
 printf("Consumer %d: Remove Item %d from %d\n",cno,item, out);
 out = (out+1)%BufferSize;
pthread_mutex_unlock(&mutex);
sem_post(&empty);
 }
}
int main()
{
 pthread_t pro[10],con[10];
 pthread_mutex_init(&mutex, NULL);
 sem_init(&empty,0,BufferSize);
 sem_init(&full,0,0);
 int a[10] = {1,2,3,4,5,6,7,8,9,10}; //Just used for numbering the producer and consumer
int i;
 for( i = 0; i <10; i++) {
 pthread_create(&pro[i], NULL, producer, &a[i]);
 }
 for( i = 0; i <10; i++) {
 pthread_create(&con[i], NULL, consumer, &a[i]);
 }
 for( i = 0; i <10; i++) {
 pthread_join(pro[i], NULL);
 }
 for( i = 0; i <10; i++) {
 pthread_join(con[i], NULL);
 }
 pthread_mutex_destroy(&mutex);
 sem_destroy(&empty);
 sem_destroy(&full);
 return 0;

}


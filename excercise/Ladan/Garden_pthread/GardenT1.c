#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


pthread_t tid[100];
int counter;
int entrance[100]={1,0,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0,1,0,1,0,1,0}; // 0= East, 1= West;
pthread_mutex_t lock;

void* eastEnter(void* arg)
{
    pthread_mutex_lock(&lock);

    counter += 1;
    printf("Visitor entered from East, counter: %d\n", counter);

    pthread_mutex_unlock(&lock);

    return NULL;
}
void* westEnter(void* arg)
{
    pthread_mutex_lock(&lock);

    counter += 1;
    printf("Visitor entered from West, counter: %d\n", counter);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    int i = 0;
    int error;



    while (i < 100) {
        if( entrance[i]==0)
            error = pthread_create(&(tid[i]), NULL, &eastEnter, NULL);
        else if( entrance[i]==1)
            error = pthread_create(&(tid[i]), NULL, &westEnter, NULL);

        if (error != 0) {
            printf("ERROR; return code from pthread_create() is %d\n", error);
            exit(-1);
        }
        i++;
    }
    i=0;

    while (i < 100) {
        pthread_join(tid[i], NULL);

    }

    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);

    return 0;
}

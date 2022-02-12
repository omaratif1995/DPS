#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t test_mutex = PTHREAD_MUTEX_INITIALIZER;

void *func1(void* tid)
{
    long * myID = (long *)tid;


//    do{
//
//
//        //Lock mutex before going to change variable
//        pthread_mutex_lock(&test_mutex);
//        printf("Hello i am thread number %d\n",*myID);
//        x++;
//        printf("x = %d\n",x);
//
//        //Unlock mutex after changing the variable
//        pthread_mutex_unlock(&test_mutex);
//    }while(x < 99);

    for (int i = 0; i < 100; i++ )
    {
        pthread_mutex_lock(&test_mutex);
        if(counter < 100){
        //Lock mutex before going to change variable

        printf("Hello i am the gate number %d\n",*myID);
        counter++;
        printf("counter = %d\n",counter);


        }
        //Unlock mutex after changing the variable
        pthread_mutex_unlock(&test_mutex);
    }

}

int main()
{
    pthread_t right;
    pthread_t left;
    pthread_t * pthreads[] = {&right,&left};
    for(int i = 0;i<2;i++){
        pthread_create(pthreads[i], NULL, func1, (void *)pthreads[i]);
    }

    pthread_join(right,NULL);
    pthread_join(left,NULL);
    return 0;
}


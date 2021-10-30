#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t test_mutex;

void *func1(void* tid)
{
    long * myID = (long *)tid;



    for (int i = 0; i < 100; i++ )
    {
        pthread_mutex_lock(&test_mutex);
        if(x < 100){
        //Lock mutex before going to change variable

        printf("Hello i am thread number %d\n",*myID);
        x++;
        printf("x = %d\n",x);

        //Unlock mutex after changing the variable
        pthread_mutex_unlock(&test_mutex);
        }

    }
}

int main()
{
    pthread_t tid0;
    pthread_t tid1;
    pthread_t * pthreads[] = {&tid0,&tid1};
    for(int i = 0;i<2;i++){
        pthread_create(pthreads[i], NULL, func1, (void *)pthreads[i]);
    }

    pthread_join(tid0,NULL);
    pthread_join(tid1,NULL);
    return 0;
}


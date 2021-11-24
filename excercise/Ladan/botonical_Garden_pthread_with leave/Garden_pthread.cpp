#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;

pthread_t tid[3];
int counter=0;
int entrance[100]; // 0= East_enterance, 1= West_enterance , 2=leave;
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

void* leave(void* arg)
{
    pthread_mutex_lock(&lock);
    if (counter>0)
    {
	counter -= 1;
    printf("A visitor wants to leave the Garden, counter: %d\n", counter);
	}
	else
	printf("there is no one in the Garden, counter: %d\n", counter);
	
	
    pthread_mutex_unlock(&lock);

    return NULL;
}


int main(void)
{
    int i = 0;
    int error;
    int a=0;
	int j=0;

    while ( i < 100) {
    	
    	printf("please enter 0 for East enterance, 1 for West enterance and 2 for leaving the garden:\n ");
    	scanf("%d", &a);
    	
        if( a==0)
		{
	        entrance[i]=a;
            error = pthread_create(&(tid[i]), NULL, &eastEnter, NULL);
       	}
        else if( a==1)
        {
        	entrance[i]=a;
            error = pthread_create(&(tid[i]), NULL, &westEnter, NULL);
		}    
        else if (a==2)
             error = pthread_create(&(tid[i]), NULL, &leave, NULL);
             
        if (error != 0) {
            printf("ERROR; return code from pthread_create() is %d\n", error);
            exit(-1);
        }
        i++;
    }
   

    while (j < 3) {
        pthread_join(tid[j], NULL);

    }

    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);

    return 0;
}


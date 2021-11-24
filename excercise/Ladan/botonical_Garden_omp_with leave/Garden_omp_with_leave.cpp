#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>

using namespace std;

int counter=0;


void* counter_update(int arg)
{  
 
    if( arg==0)
		{
	        counter += 1;
            printf("Visitor entered from East, counter is: %d\n", counter);
       	}
    else if( arg==1)
        {
            counter += 1;
            printf("Visitor entered from West, counter is: %d\n", counter);
		}    
    else if (arg==2)
            if (counter>0)
         	{ 
			  counter -= 1;
    		  printf("A visitor leave the Garden, counter is: %d\n", counter);
			}
            else
        	printf("there is no one in the Garden, counter is: %d\n", counter); 
   
   return NULL;
}

int main(void)
{
	int a;
	
//omp_set_num_threads(2);
    #pragma omp parallel num_threads(3)
    {
    #pragma omp parallel
    {
    	while(counter<100)
   		 { 
        	printf("please enter 0 for East enterance, 1 for West enterance and 2 for leaving the garden:\n ");
        	scanf("%d", &a);
      	    counter_update(a);
       
         }
    }
    
     printf("The garden is full,please wait.") ;
     return 0;
    }
}



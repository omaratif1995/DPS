
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>
using namespace std;

int counter=0;


int main()
{
    //omp_set_num_threads(2);
    #pragma omp parallel num_threads(2)
    {
    #pragma omp parallel
    {
    while(counter<100)
    {
    	string enterance;
        cout << "did Visitor enter from east or west?";
        cin>> enterance;
        if (enterance== "east" or enterance=="west")
		{
	    	counter += 1;
            printf("Visitor entered, counter: %d\n", counter);
        }
        else
        {
        	cout << "error: the typed enterance is wrong, please try again";
		}
    }
    
    cout << "The garden is full,no one can not come to the garden.";

    }


    }

    return 0;
}



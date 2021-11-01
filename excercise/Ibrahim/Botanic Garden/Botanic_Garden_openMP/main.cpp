#include <iostream>
#include <omp.h>

void main() {
	int counter = 0;
    #pragma omp parallel num_threads(2)
	{
		char c;
		while (true) {
            #pragma omp critical
			{
				if (counter < 10) {
					std::cout << "Hey I am Thread " << omp_get_thread_num() << " Please enter \"+\" or \"-\": ";
					std::cin >> c;
					if (c == '+')
					{counter++;}
					else if (c == '-')
					{counter--;}
					std::cout << "Thread " << omp_get_thread_num() << ": " << counter << " Person(s)" << std::endl;
				}
				else {
					omp_destroy_lock;
					break;
				}
			}
		}
	}
}

#include "Functions.h"
#include <omp.h>

/*4 trucks, non of them is a leader at instantiation*/
Truck truck0(0);
Truck truck1(1);
Truck truck2(2);
Truck truck3(3);

int main() {
	/*The driver rides on one of the trucks (say truck0) and requests a leadership for this truck*/
	truck0.makeLeader();
	
// DONE BY LEADER ONLY
#pragma omp parallel num_threads(3)
{
#pragma omp task
	truck0.connect(truck1);
#pragma omp task
	truck0.connect(truck2);
#pragma omp task
	truck0.connect(truck3);
}
	
	// DONE BY: LEADER ONLY
	std::thread t1(thread_maintainConnection);
	
	// DONE BY: FOLLOWERS ONLY
	std::thread t2(thread_speedControl);
	std::thread t3(thread_steering);
	std::thread t4(thread_braking);
	std::thread t5(thread_maintainDistance);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	std::cin.get();
}
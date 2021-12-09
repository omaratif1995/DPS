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
	/*Connecting to the trailing trucks in a parallel implementation*/
#pragma omp parallel num_threads(3)
{
#pragma omp task
	truck0.connect(truck1);
#pragma omp task
	truck0.connect(truck2);
#pragma omp task
	truck0.connect(truck3);
}

	/*Thread for maintaining the connection*/
	std::thread t1(thread_maintainConnection);
	/*Thread for adjusting the trailing trucks velocities according to the leader*/
	std::thread t2(thread_speedControl);
	/*Thread for adjusting the steering wheel of the trailing trucks according to the leader*/
	std::thread t3(thread_steering);
	/*Thread for checking on the leader braking status and sync the trailers accordingly*/
	std::thread t4(thread_braking);
	/*Thread for maintaining constant distance between the trucks*/
	std::thread t5(thread_maintainDistance);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	std::cin.get();
}
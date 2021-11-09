#include "Functions.h"

int main() {
	std::thread t1(connection_thread);
	t1.join();
	std::thread t2(maintainConnection_thread);
	std::thread t3(velocity_thread);
	std::thread t4(acceleration_thread);
	std::thread t5(angle_thread);
	std::thread t6(brake_thread);
	std::thread t7(maintainDistance_thread);

	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();

	std::cin.get();
}
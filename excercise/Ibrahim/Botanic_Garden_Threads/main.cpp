#include <iostream>
#include <thread>
#include <mutex>

static int counter = 0;
std::mutex mtx;
using namespace std::chrono_literals;

void left_sensor() {
	char c_left;
	while (counter < 10){
	mtx.lock();
	std::cout << "Hey I am the left gate! Please enter \"+\" or \"-\":" << std::endl;
	std::cin >> c_left;
	if(c_left=='+')
	{
		counter++;
	}
	else if(c_left=='-')
	{
		counter--;
	}
	else{}
	std::cout << "Left Gate: " << counter << " Person(s)" << std::endl;
	mtx.unlock();
	std::this_thread::sleep_for(1s);
	}

}

void right_sensor() {
	char c_right;
	while (counter < 10){
	mtx.lock();
	std::cout << "Hey I am the right gate! Please enter \"+\" or \"-\":" << std::endl;
	std::cin >> c_right;
	if(c_right=='+')
	{
		counter++;
	}
	else if(c_right=='-')
	{
		counter--;
	}
	else{}
	std::cout << "Right Gate: " << counter << " Person(s)" << std::endl;
	mtx.unlock();
	std::this_thread::sleep_for(1s);
	}
}

int main() {
	std::thread left_gate(left_sensor);
	std::thread right_gate(right_sensor);

	left_gate.join();
	right_gate.join();

	std::cin.get();
}

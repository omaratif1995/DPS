#include <iostream>
#include <thread>
#include <mutex>

static int counter = 0;
std::mutex mtx;
using namespace std::chrono_literals;

void update_counter() {
	char c;
	while (counter < 10){
	mtx.lock();
	std::cout << "Hey I am Thread " << std::this_thread::get_id()<<" Please enter \"+\" or \"-\":" << std::endl;
	std::cin >> c;
	if(c=='+')
	{
		counter++;
	}
	else if(c=='-')
	{
		counter--;
	}
	else{}
	std::cout << "Thread " <<std::this_thread::get_id()<<": "<< counter << " Person(s)" << std::endl;
	mtx.unlock();
	std::this_thread::sleep_for(1s);
	}

}

int main() {
	std::thread left_gate(update_counter);
	std::thread right_gate(update_counter);

	left_gate.join();
	right_gate.join();

	std::cin.get();
}

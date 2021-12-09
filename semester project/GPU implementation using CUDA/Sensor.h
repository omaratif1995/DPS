#pragma once
#include <iostream>

class Sensor {
	
public:
	double read() {
		std::cout << "I am reading ..." << std::endl;
		return 10.0;
	}
};
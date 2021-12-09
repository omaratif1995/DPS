#pragma once
#include <iostream>
#include <thread>
using namespace std::chrono_literals;

class Truck {
private:
	int m_id;
	double m_v = 0;
	double m_a = 0;
	double m_angle = 0;
	bool m_isLeader = false;

public:
	bool isBraking = false;
	bool isConnected = false;

	/*Contructor*/
	Truck(int id) {
		m_id = id;
	}
	/*Methods of the Truck class*/
	void makeLeader() {
		this->m_isLeader = true;
		std::cout << "Truck " << m_id << " is now the Leader!" << std::endl;
	}
	void connect(Truck& client) {
		if (this->m_isLeader) {
			std::cout << "Leader: Connecting to client " << client.get_id() << " ..." << std::endl;
			client.isConnected = true;
			std::cout << "Client " << client.get_id() << ": connected successfully!" << std::endl;
		}
		else {
			std::cout << "Connection request is not possible. This truck is not a leader!"<< std::endl;
		}
	}
	double get_velocity() {
		return m_v;
	}
	void accelerate(int targetVel) {
		std::cout << "Client " << m_id << " is accelerating ..." << std::endl;
		std::cout << "Client " << m_id << " has reached the target velocity!" << std::endl;
	}
	void deccelerate(int targetVel) {
		std::cout << "Client " << m_id << " is deccelerating ..." << std::endl;
		std::cout << "Client " << m_id << " has reached the target velocity!" << std::endl;
	}
	double get_angle() {
		return m_angle;
	}
	void set_angle(double targetAngle) {
		m_angle = targetAngle;
		std::cout << "Client " << m_id << ": Steering Angle has been adjusted successfully!" << std::endl;
	}
	void brake() {
		this->isBraking = true;
		std::cout << "Client " << m_id << ": is braking!!" << std::endl;
	}
	void maintain_distance() {
		std::cout << "Client " << m_id << ": distance is being adjusted ..." << std::endl;
		std::cout << "Client " << m_id << ": distance to the next vehicle is adjusted succesfully!" << std::endl;
	}
	int get_id() {
		return m_id;
	}
}; 


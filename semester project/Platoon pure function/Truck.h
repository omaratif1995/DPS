#pragma once
#include <iostream>
#include <thread>
using namespace std::chrono_literals;

class Truck {
private:
	int m_rank;
	double m_v = 0;
	double m_a = 0;
	double m_angle = 0;
	bool m_isLeader = false;

public:
	bool isBraking = false;
	bool isConnected = false;

	/*Contructor*/
	Truck(int rank) {
		m_rank = rank;
	}
	/*Methods of the Truck class*/
	void makeLeader() {
		this->m_isLeader = true;
		std::cout << "Truck " << m_rank << " is now the Leader!" << std::endl;
	}
	void connect(Truck& node) {
		if (this->m_isLeader) {
			std::cout << "Leader: Connecting to node " << node.get_rank() << " ..." << std::endl;
			node.isConnected = true;
			std::cout << "Node " << node.get_rank() << ": connected successfully!" << std::endl;
		}
		else {
			std::cout << "Connection request is not possible. This truck is not a leader!"<< std::endl;
		}
	}
	double get_velocity() {
		return m_v;
	}
	void accelerate(int targetVel) {
		std::cout << "Node " << m_rank << " is accelerating ..." << std::endl;
		std::cout << "Node " << m_rank << " has reached the target velocity!" << std::endl;
	}
	void deccelerate(int targetVel) {
		std::cout << "Node " << m_rank << " is deccelerating ..." << std::endl;
		std::cout << "Node " << m_rank << " has reached the target velocity!" << std::endl;
	}
	double get_angle() {
		return m_angle;
	}
	void set_angle(double targetAngle) {
		m_angle = targetAngle;
		std::cout << "Node " << m_rank << ": Steering Angle has been adjusted successfully!" << std::endl;
	}
	void brake() {
		this->isBraking = true;
		std::cout << "Node " << m_rank << ": is braking!!" << std::endl;
	}
	void maintain_distance() {
		std::cout << "Node " << m_rank << ": distance is being adjusted ..." << std::endl;
		std::cout << "Node " << m_rank << ": distance to the next vehicle is adjusted succesfully!" << std::endl;
	}
	int get_rank() {
		return m_rank;
	}
}; 


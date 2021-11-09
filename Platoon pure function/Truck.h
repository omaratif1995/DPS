#pragma once
#include <iostream>
#include <thread>
using namespace std::chrono_literals;

class Truck {
public:
	int m_id;
	double m_v = 0;
	double m_a = 0;
	double m_angle = 0;
	bool m_brake_status = false;
	bool isConnected = false;
	std::string gps_coordinate = "GPS";
	int sensors[4] = { 0 };
	
	Truck(int id) {
		m_id = id;
	}

	void connect(Truck& client) {
		std::cout << "Leader: Connecting to client " << client.m_id << " ..." << std::endl;
		std::this_thread::sleep_for(1.5s);
		client.set_connection(true);
	}
	void set_connection(bool connect) {
		isConnected = connect;
		std::cout << "Client " << m_id << ": connected successfully!" << std::endl;
	}

	double get_velocity() {
		return m_v;
	}
	void set_velocity(double v) {
		m_v = v;
		std::cout << "Client " << m_id << ": Velocity adjusted successfully!" << std::endl;
	}
	double get_acceleration() {
		return m_a;
	}
	void set_acceleration(double a) {
		m_a = a;
		std::cout << "Client " << m_id << ": Acceleration adjusted successfully!" << std::endl;
	}
	double get_angle() {
		return m_angle;
	}
	void set_angle(double angle) {
		m_angle = angle;
		std::cout << "Client " << m_id << ": Steering Angle adjusted successfully!" << std::endl;
	}
	bool isBraking() {
		return m_brake_status;
	}
	void brake() {
		std::cout << "Client " << m_id << ": is braking!!" << std::endl;
	}
	void read_gps() {
		std::cout << "Client " << m_id << ": reading GPS coordinates ..." << std::endl;
	}
	void read_sensors() {
		std::cout << "Client " << m_id << ": reading Sensors values ..." << std::endl;
	}
	void maintain_distance() {
		read_gps();
		std::this_thread::sleep_for(1s);
		read_sensors();
		std::this_thread::sleep_for(1s);
		std::cout << "Client " << m_id << ": distance is being adjusted ..." << std::endl;
		std::this_thread::sleep_for(2s);
		std::cout << "Client " << m_id << ": distance to the next vehicle is adjusted succesfully!" << std::endl;
	}
}; 


Truck leader(0);
Truck follower1(1);
Truck follower2(2);
Truck follower3(3);

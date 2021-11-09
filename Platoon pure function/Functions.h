#pragma once
#include "Truck.h"

void connection_thread() {
	leader.connect(follower1);
	std::this_thread::sleep_for(2s);
	leader.connect(follower2); 
	std::this_thread::sleep_for(2s);
	leader.connect(follower3);
	std::this_thread::sleep_for(1s);
}

void maintainConnection_thread() {
	while (1) {
		if (!follower1.isConnected) leader.connect(follower1);
		std::this_thread::sleep_for(500ms);
		if (!follower2.isConnected) leader.connect(follower2);
		std::this_thread::sleep_for(500ms);
		if (!follower3.isConnected) leader.connect(follower3);
		std::this_thread::sleep_for(50ms);
	}
}

void velocity_thread() {
	std::this_thread::sleep_for(200ms);
	while (1) {
		double current_v= leader.get_velocity();
		follower1.set_velocity(current_v);
		std::this_thread::sleep_for(1.5s);
		follower2.set_velocity(current_v);
		std::this_thread::sleep_for(1.5s);
		follower3.set_velocity(current_v);

		std::this_thread::sleep_for(500ms);
	}
}

void acceleration_thread() {
	std::this_thread::sleep_for(500ms);
	while (1) {
		double current_a= leader.get_acceleration();
		follower1.set_acceleration(current_a);
		std::this_thread::sleep_for(1.5s);
		follower2.set_acceleration(current_a);
		std::this_thread::sleep_for(1.5s);
		follower3.set_acceleration(current_a);

		std::this_thread::sleep_for(500ms);
	}
}

void angle_thread() {
	std::this_thread::sleep_for(600ms);
	while (1) {
		double current_angle = leader.get_angle();
		follower1.set_acceleration(current_angle);
		std::this_thread::sleep_for(1.5s);
		follower2.set_acceleration(current_angle);
		std::this_thread::sleep_for(1.5s);
		follower3.set_acceleration(current_angle);

		std::this_thread::sleep_for(500ms);
	}
}

void brake_thread() {
	
	while (1) {
		if (leader.isBraking())
		{
			follower1.brake();
			follower2.brake();
			follower3.brake();
		}
		std::this_thread::sleep_for(50ms);
	}
}

void maintainDistance_thread() {
	std::this_thread::sleep_for(800ms);
	while (1) {
		follower1.maintain_distance();
		std::this_thread::sleep_for(1.5s);
		follower2.maintain_distance();
		std::this_thread::sleep_for(1.5s);
		follower3.maintain_distance();
		std::this_thread::sleep_for(500ms);
	}
}
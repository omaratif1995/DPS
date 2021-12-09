#pragma once
#include "Truck.h"
#include<omp.h>
using namespace std::chrono_literals;

void thread_maintainConnection() {
	while (1) {
#pragma omp parallel num_threads(3)
{
#pragma omp task
{
	if (!truck1.isConnected) truck0.connect(truck1);
	std::this_thread::sleep_for(100ms);
}		
#pragma omp task
{
	if (!truck2.isConnected) truck0.connect(truck2);
	std::this_thread::sleep_for(100ms);
}
#pragma omp task
{
	if (!truck3.isConnected) truck0.connect(truck3);
	std::this_thread::sleep_for(100ms);
}
}	
	}
}

void thread_speedControl() {
	while (1) {
#pragma omp parallel num_threads(3)
{	
#pragma omp task
{
	double v_target = truck0.get_velocity();
	double v_current = truck1.get_velocity();
	if (v_current < v_target) { truck1.accelerate(v_target); }
	else if (v_current > v_target) { truck1.deccelerate(v_target); }
	std::this_thread::sleep_for(200ms);
}
#pragma omp task
{
	double v_target = truck0.get_velocity();
	double v_current = truck2.get_velocity();
	if (v_current < v_target) { truck2.accelerate(v_target); }
	else if (v_current > v_target) { truck2.deccelerate(v_target); }
	std::this_thread::sleep_for(200ms);
}
#pragma omp task
{
	double v_target = truck0.get_velocity();
	double v_current = truck3.get_velocity();
	if (v_current < v_target) { truck3.accelerate(v_target); }
	else if (v_current > v_target) { truck3.deccelerate(v_target); }
	std::this_thread::sleep_for(200ms);
}
}
	}
}

void thread_steering() {
	while (1) {
#pragma omp parallel num_threads(3)
{
#pragma omp task
{
	double target_angle = truck0.get_angle();
	truck1.set_angle(target_angle);
	std::this_thread::sleep_for(100ms);
}
#pragma omp task
{
	double target_angle = truck0.get_angle();
	truck2.set_angle(target_angle);
	std::this_thread::sleep_for(100ms);
}
#pragma omp task
{
	double target_angle = truck0.get_angle();
	truck3.set_angle(target_angle);
	std::this_thread::sleep_for(100ms);
}
}
	}
}

void thread_braking() {	
	while (1) {
#pragma omp parallel num_threads(3)
{
#pragma omp task
{
	if (truck0.isBraking) truck1.brake();
	std::this_thread::sleep_for(100ms);
}
#pragma omp task
{
	if (truck0.isBraking) truck2.brake();
	std::this_thread::sleep_for(100ms);
}
#pragma omp task
{
	if (truck0.isBraking) truck3.brake();
	std::this_thread::sleep_for(100ms);	
}
}
	}
}

void thread_maintainDistance() {
	while (1) {
#pragma omp parallel num_threads(3)
{
#pragma omp task
{
	truck1.maintain_distance();
	std::this_thread::sleep_for(200ms);
}
#pragma omp task
{
	truck1.maintain_distance();
	std::this_thread::sleep_for(200ms);
}
#pragma omp task
{
	truck1.maintain_distance();
	std::this_thread::sleep_for(200ms);
}
}
	}
}
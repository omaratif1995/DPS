#pragma once
#include "Truck.h"
#include<omp.h>
using namespace std::chrono_literals;

// DONE BY: LEADER ONLY
void thread_maintainConnection() {
	while (1) {
#pragma omp parallel num_threads(3)
{
#pragma omp task
{
	if (!truck1.isConnected) truck0.connect(truck1);
}		
#pragma omp task
{
	if (!truck2.isConnected) truck0.connect(truck2);
}
#pragma omp task
{
	if (!truck3.isConnected) truck0.connect(truck3);
}
}	
	}
}

void thread_speedControl() {
	while (1) {
#pragma omp parallel num_threads(3)
{	
// DONE BY:	FOLLOWER (RANK1)
#pragma omp task
{
	double v_target = truck0.get_velocity();
	double v_current = truck1.get_velocity();
	if (v_current < v_target) { truck1.accelerate(v_target); }
	else if (v_current > v_target) { truck1.deccelerate(v_target); }
}
// DONE BY:	FOLLOWER (RANK2)
#pragma omp task
{
	double v_target = truck0.get_velocity();
	double v_current = truck2.get_velocity();
	if (v_current < v_target) { truck2.accelerate(v_target); }
	else if (v_current > v_target) { truck2.deccelerate(v_target); }
}
// DONE BY:	FOLLOWER (RANK3)
#pragma omp task
{
	double v_target = truck0.get_velocity();
	double v_current = truck3.get_velocity();
	if (v_current < v_target) { truck3.accelerate(v_target); }
	else if (v_current > v_target) { truck3.deccelerate(v_target); }
}
}
	}
}

void thread_steering() {
	while (1) {
#pragma omp parallel num_threads(3)
{
// DONE BY:	FOLLOWER (RANK1)
#pragma omp task
{
	double target_angle = truck0.get_angle();
	truck1.set_angle(target_angle);
}
// DONE BY:	FOLLOWER (RANK2)
#pragma omp task
{
	double target_angle = truck0.get_angle();
	truck2.set_angle(target_angle);
}
// DONE BY:	FOLLOWER (RANK3)
#pragma omp task
{
	double target_angle = truck0.get_angle();
	truck3.set_angle(target_angle);
}
}
	}
}

void thread_braking() {	
	while (1) {
#pragma omp parallel num_threads(3)
{
// DONE BY:	FOLLOWER (RANK1)
#pragma omp task
{
	if (truck0.isBraking) truck1.brake();
}
// DONE BY:	FOLLOWER (RANK2)
#pragma omp task
{
	if (truck0.isBraking) truck2.brake();
}
// DONE BY:	FOLLOWER (RANK3)
#pragma omp task
{
	if (truck0.isBraking) truck3.brake();
}
}
	}
}

void thread_maintainDistance() {
	while (1) {
#pragma omp parallel num_threads(3)
{
// DONE BY:	FOLLOWER (RANK1)
#pragma omp task
{
	truck1.maintain_distance();
}
// DONE BY:	FOLLOWER (RANK2)
#pragma omp task
{
	truck2.maintain_distance();
}
// DONE BY:	FOLLOWER (RANK3)
#pragma omp task
{
	truck3.maintain_distance();
}
}
	}
}
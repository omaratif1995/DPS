
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Sensor.h"
#include <stdio.h>

#define NUM_SENSORS 50

__global__ void readSensorVals(double *readings, Sensor *sensors)
{
    int i = threadIdx.x;
    if(i < NUM_SENSORS)
    readings[i] = sensors[i].read();
}

int main()
{
    double readings[NUM_SENSORS];
    Sensor sensors[NUM_SENSORS];

    cudaMalloc(&readings, NUM_SENSORS * sizeof(double));
    cudaMalloc(&sensors, NUM_SENSORS * sizeof(Sensor));

    readSensorVals <<<1, NUM_SENSORS >>> (&readings,&sensors);

    cudaFree(readings);
    cudaFree(sensors);

}

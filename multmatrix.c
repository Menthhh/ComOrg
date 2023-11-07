#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NUM_SAMPLES 10000000
#define NUM_THREADS 1

double calculate_projectile_factor(double initial_velocity, double angle) {
    const double g = 9.81; // acceleration due to gravity
    double time_of_flight = (2.0 * initial_velocity * sin(angle)) / g;
    double horizontal_distance = initial_velocity * cos(angle) * time_of_flight;
    return horizontal_distance;
}

int main() {
    double initial_velocity = 50.0; // m/s
    double angle = 45.0 * (M_PI / 180.0); // 45 degrees in radians

    double start, stop, t_parallel, t_serial;

    // Without OpenMP
    start = omp_get_wtime();
    for (int i = 0; i < NUM_SAMPLES; i++) {
        calculate_projectile_factor(initial_velocity, angle);
    }
    stop = omp_get_wtime();
    t_serial = stop - start;

    // With OpenMP
    omp_set_num_threads(NUM_THREADS);
    start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < NUM_SAMPLES; i++) {
        calculate_projectile_factor(initial_velocity, angle);
        
    }

    #pragma omp parallel
    {
        printf("Number of threads: %i\n", omp_get_num_threads());
    }
    stop = omp_get_wtime();
    t_parallel = stop - start;

    printf("Time without OpenMP: %2.4f seconds\n", t_serial);
    printf("Time with OpenMP: %2.4f seconds\n", t_parallel);
    printf("Speedup: %2.4f\n", t_serial / t_parallel);
    printf("max number of threads: %i\n", omp_get_max_threads());

    return 0;
}

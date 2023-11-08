#include <stdio.h>
#include <math.h>
#include <omp.h>

// Shared variables
double initial_velocity = 30.0; // m/s
double angle = 45.0; // degrees
double g = 9.81; // acceleration due to gravity (m/s^2)
double height;
double final_velocity;

// Function to compute height
void compute_height() {
    double angle_rad = angle * M_PI / 180;
    height = initial_velocity * sin(angle_rad) * initial_velocity * sin(angle_rad) / (2 * g);
}

// Function to compute final velocity
void compute_final_velocity() {
    double angle_rad = angle * M_PI / 180;
    final_velocity = initial_velocity * cos(angle_rad);
}

int main() {
    // Set the number of threads for OpenMP
    int num_threads = 16; // You can adjust this as needed
    omp_set_num_threads(num_threads);

    // Parallel region for computing height and final velocity
    #pragma omp parallel sections
    {
        #pragma omp section
        compute_height();

        #pragma omp section
        compute_final_velocity();
    }

    #pragma omp parallel
    {
        printf("Number of threads: %i\n", omp_get_num_threads());
    }


    printf("Max height: %.2f meters\n", height);
    printf("Final velocity: %.2f m/s\n", final_velocity);
    printf("max number of threads: %i\n", omp_get_max_threads());

    return 0;
}

#include <stdio.h>
#include <math.h>
#include <omp.h>
#define NUMBER_OF_THREADS 16

// Function to compute height
double compute_height(double initial_velocity, double angle) {
    double angle_rad = angle * M_PI / 180;
    const double g = 9.81; // acceleration due to gravity
    return initial_velocity * sin(angle_rad) * initial_velocity * sin(angle_rad) / (2 * g);
}

// Function to compute final velocity
double compute_final_velocity(double initial_velocity, double angle) {
    double angle_rad = angle * M_PI / 180;
    return initial_velocity * cos(angle_rad);
}

int main() {
    int num_samples = 10000000; // Number of samples
    omp_set_num_threads(NUMBER_OF_THREADS);

    // Varying projectile variables
    double initial_velocities[] = {30.0, 40.0, 50.0};
    double angles[] = {30.0, 45.0, 60.0};

    // Measure time without using threads
    double start_time = omp_get_wtime();

    for (int i = 0; i < num_samples; i++) {
        // Compute height for various projectile variables
        for (int iv = 0; iv < 3; iv++) {
            for (int a = 0; a < 3; a++) {
                double height = compute_height(initial_velocities[iv], angles[a]);
                // Do something with the height, e.g., store or print it
            }
        }

        // Compute final velocity for various projectile variables
        for (int iv = 0; iv < 3; iv++) {
            for (int a = 0; a < 3; a++) {
                double final_velocity = compute_final_velocity(initial_velocities[iv], angles[a]);
                // Do something with the final velocity, e.g., store or print it
            }
        }
    }

    double stop_time = omp_get_wtime();

    // Print the time taken without threads
    printf("Without threads - Time taken: %.5f seconds\n", stop_time - start_time);

    // Reset shared variables
    start_time = omp_get_wtime();

    // Measure time using OpenMP parallelization
    #pragma omp parallel for
    for (int i = 0; i < num_samples; i++) {
        // Compute height and final velocity in parallel
        for (int iv = 0; iv < 3; iv++) {
            for (int a = 0; a < 3; a++) {
                double height = compute_height(initial_velocities[iv], angles[a]);
                double final_velocity = compute_final_velocity(initial_velocities[iv], angles[a]);
                // Do something with the height and final velocity, e.g., store or print them
            }
        }
    }

    stop_time = omp_get_wtime();

    // Print the time taken using OpenMP parallelization
    printf("Using OpenMP - Time taken: %.5f seconds\n", stop_time - start_time);
    printf("Max number of threads: %i\n", omp_get_max_threads());

    return 0;
}

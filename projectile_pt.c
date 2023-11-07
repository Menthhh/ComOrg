#include <stdio.h>
#include <pthread.h>
#include <math.h>

// Shared variables
double initial_velocity = 30.0; // m/s
double angle = 45.0; // degrees
double g = 9.81; // acceleration due to gravity (m/s^2)
double height; 
double final_velocity;

// Thread function to compute height
void* compute_height(void* arg) {
    double angle_rad = angle * M_PI / 180;
    height = initial_velocity * sin(angle_rad) * initial_velocity * sin(angle_rad) / (2 * g);
    
    return NULL;
}

// Thread function to compute final velocity
void* compute_final_velocity(void* arg) {
    double angle_rad = angle * M_PI / 180; //MP
    final_velocity = initial_velocity * cos(angle_rad);
    
    return NULL;
}


int main() {
    pthread_t height_thread, velocity_thread;

    // Create two threads to compute height and final velocity
    pthread_create(&height_thread, NULL, compute_height, NULL);
    pthread_create(&velocity_thread, NULL, compute_final_velocity, NULL);

    // Wait for both threads to finish
    pthread_join(height_thread, NULL);
    pthread_join(velocity_thread, NULL);

    printf("Max height: %.2f meters\n", height);
    printf("Final velocity: %.2f m/s\n", final_velocity);
    return 0;
}

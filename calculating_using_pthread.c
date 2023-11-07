#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to hold data for the object's height and velocity
struct ObjectData {
    double height;
    double velocity;
};

// Function to calculate the height of the object
void* calculateHeight(void* data) {
    struct ObjectData* objData = (struct ObjectData*)data;
    // Simulate a simple height calculation
    objData->height = 0.5 * 9.81 * 3.0 * 3.0; // h = (1/2) * g * t^2
    return NULL;
}

// Function to calculate the velocity of the object
void* calculateVelocity(void* data) {
    struct ObjectData* objData = (struct ObjectData*)data;
    // Simulate a simple velocity calculation
    objData->velocity = 9.81 * 3.0; // v = g * t
    return NULL;
}

int main() {
    struct ObjectData objData;
    pthread_t heightThread, velocityThread;

    int start_1 = omp_get_wtime();
    // Create threads for height and velocity calculations
    pthread_create(&heightThread, NULL, calculateHeight, &objData);
    pthread_create(&velocityThread, NULL, calculateVelocity, &objData);

    // Wait for both threads to finish
    pthread_join(heightThread, NULL);
    pthread_join(velocityThread, NULL);
    int stop_1 = omp_get_wtime();

    printf("Time with threads: %i seconds\n", stop_1 - start_1);

    //without threads
    int start = omp_get_wtime();
    calculateHeight(&objData);
    calculateVelocity(&objData);
    int stop = omp_get_wtime();

    printf("Time without threads: %i seconds\n", stop - start);

    // Access the results
    printf("Object's Height: %f meters\n", objData.height);
    printf("Object's Velocity: %f m/s\n", objData.velocity);

    return 0;
}

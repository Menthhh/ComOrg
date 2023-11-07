#include <stdio.h>
#include <string.h>
#include <omp.h>

int main() {
    char userQuestion[100];
    double start_time, end_time;

    printf("Ask me a question: ");
    fgets(userQuestion, sizeof(userQuestion), stdin); // Read user input, ensuring a maximum of 100 characters.


    //print number of threads
    printf("Max number of threads: %i \n", omp_get_max_threads());

    // Measure time without OpenMP
    start_time = omp_get_wtime();

    int hasKeyword = 0; // Variable to indicate if a keyword is found (0 for no, 1 for yes).

    for (int i = 0; i < strlen(userQuestion); i++) {
        if (strstr(&userQuestion[i], "who") || strstr(&userQuestion[i], "what") ||
            strstr(&userQuestion[i], "where") || strstr(&userQuestion[i], "when") ||
            strstr(&userQuestion[i], "why") || strstr(&userQuestion[i], "how")) {
            hasKeyword = 1;
        }
    }

    end_time = omp_get_wtime();
    printf("Execution Time without OpenMP: %f seconds\n", end_time - start_time);

    // Measure time with OpenMP
    start_time = omp_get_wtime();

    hasKeyword = 0; // Reset the variable for the OpenMP version

    #pragma omp parallel for reduction(+:hasKeyword)
    for (int i = 0; i < strlen(userQuestion); i++) {
        if (strstr(&userQuestion[i], "who") || strstr(&userQuestion[i], "what") ||
            strstr(&userQuestion[i], "where") || strstr(&userQuestion[i], "when") ||
            strstr(&userQuestion[i], "why") || strstr(&userQuestion[i], "how")) {
            hasKeyword = 1;
        }
    }

    end_time = omp_get_wtime();
    printf("Execution Time with OpenMP: %f seconds\n", end_time - start_time);

    if (hasKeyword) {
        printf("I don't know the answer to that question.\n");
    } else {
        printf("I'm not programmed to answer that question.\n");
    }

    return 0;
}

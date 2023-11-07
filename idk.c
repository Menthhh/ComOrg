#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t response_mutex = PTHREAD_MUTEX_INITIALIZER;
char response[100];

void* chatbot_response(void* user_input) {
    // Simulate some basic chatbot responses
    if (strstr((const char*)user_input, "hello") != NULL) {
        strcpy(response, "Hello there!");
    } else if (strstr((const char*)user_input, "how are you") != NULL) {
        strcpy(response, "I'm just a program, so I don't have feelings.");
    } else {
        strcpy(response, "I don't know how to respond to that.");
    }

    // Simulate a delay to make it seem like the chatbot is processing
    sleep(2);

    // Lock the mutex to ensure the response is printed without interference
    pthread_mutex_lock(&response_mutex);

    printf("Chatbot: %s\n", response);

    // Unlock the mutex
    pthread_mutex_unlock(&response_mutex);

    return NULL;
}

void* user_thread(void* arg) {
    pthread_t chat_bot;

    while (1) {
        char user_input[100];
        printf("User: ");
        fgets(user_input, sizeof(user_input), stdin);

        // Remove the trailing newline character
        user_input[strcspn(user_input, "\n")] = '\0';

        pthread_create(&chat_bot, NULL, chatbot_response, &user_input);
        pthread_join(chat_bot, NULL);
    }

    return NULL;
}

int main() {
    pthread_t user;

    pthread_create(&user, NULL, user_thread, NULL);
    pthread_join(user, NULL);

    return 0;
}

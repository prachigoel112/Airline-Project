#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000 // Adjust this value based on the maximum number of passengers

// Define a structure for passengers
typedef struct {
    int seatNumber;
    char class; // 'F' for first class, 'E' for economy class
    char status; // 'S' for senior citizen, 'W' for woman traveler, 'O' for other travelers
} Passenger;

// Define a structure for a queue
typedef struct {
    Passenger data[MAX_SIZE];
    int front, rear;
} Queue;

// Function to initialize a queue
void initializeQueue(Queue* queue) {
    queue->front = queue->rear = -1;
}

// Function to check if a queue is empty
int isEmpty(Queue* queue) {
    return queue->front == -1;
}

// Function to check if a queue is full
int isFull(Queue* queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

// Function to enqueue a passenger into a queue
void enqueue(Queue* queue, Passenger passenger) {
    if (isFull(queue)) {
        printf("Queue is full.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_SIZE;
    }
    queue->data[queue->rear] = passenger;
}

// Function to dequeue a passenger from a queue
Passenger dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        Passenger nullPassenger = {-1, 'N', 'N'}; // Null passenger
        return nullPassenger;
    }
    Passenger passenger = queue->data[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }
    return passenger;
}

// Function to board passengers based on priority and seat number
void boardPassengers(Queue* queues, int numQueues) {
    for (int i = 0; i < numQueues; i++) {
        while (!isEmpty(&queues[i])) {
            Passenger passenger = dequeue(&queues[i]);
            printf("Boarding passenger %d from queue %d.\n", passenger.seatNumber, i + 1);
        }
    }
}

int main() {
    Queue queues[2]; // Two queues: 0 for first class, 1 for economy class
    initializeQueue(&queues[0]);
    initializeQueue(&queues[1]);

    // Read passenger data from file
    FILE* file = fopen("passenger_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    Passenger passengers[MAX_SIZE];
    int numPassengers = 0;

    // Read passenger data from file
    while (fscanf(file, "%d %c %c\n", &passengers[numPassengers].seatNumber,
                  &passengers[numPassengers].class, &passengers[numPassengers].status) == 3) {
        numPassengers++;
        if (numPassengers >= MAX_SIZE) {
            printf("Maximum number of passengers exceeded.\n");
            break;
        }
    }

    fclose(file);

    // Board passengers
    for (int i = 0; i < numPassengers; i++) {
        Passenger passenger = passengers[i];
        int queueIndex = 0; // Default to first class
        if (passenger.class == 'E') {
            queueIndex = 1; // Economy class
        }

        enqueue(&queues[queueIndex], passenger);
    }

    // Example of boarding passengers
    boardPassengers(queues, 2);

    return 0;
}

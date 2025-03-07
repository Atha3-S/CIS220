#include <stdio.h>
#include <stdlib.h>

// Define a Node structure for each element in the queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a Queue structure to represent the queue implemented as a linked list
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create and initialize an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Enqueue operation: adds an item to the end of the queue, pseudocode found in PA 5.5.1
void enqueue(Queue* queue, int item) {
    // Allocate new node and assign data (newNode->next is set to NULL)
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
	// Set the node's member values
    newNode->data = item;
    newNode->next = NULL;
    
    if (queue->front == NULL) {
        // If the queue is empty, set front to the new node
        queue->front = newNode;
    } else {
        // Otherwise, link the new node at the end of the queue
        queue->rear->next = newNode;
    }
    // Update the rear pointer to the new node
    queue->rear = newNode;
}

// Dequeue operation: removes and returns the item from the front of the queue, pseudocode found in PA 5.5.1
int dequeue(Queue* queue) {
	// If queue is empty return -1 (assuming only positive integers will be added) 
    if (queue->front == NULL) {
        return -1;
    }
    // Save the data from the front node and move the front pointer
    Node* temp = queue->front;
    int dequeuedItem = temp->data;
    queue->front = temp->next;
    // If the queue becomes empty, update the rear pointer to NULL
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
	// free memory for the dequeued node
    free(temp); 
    return dequeuedItem;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to peek at the front item without removing it
int peek(Queue* queue) {
    if (queue->front == NULL) {
        return 0;
    }
    return queue->front->data;
}

// Function to get the length of the queue
int getLength(Queue* queue) {
    int length = 0;
    Node* current = queue->front;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// Function to traverse and display the queue
void displayQueue(Queue* queue) {
    Node* current = queue->front;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Queue* queue = createQueue();

    displayQueue(queue);
    printf("The queue is %sempty.\n", isEmpty(queue) ? "" : "not ");
    printf("The queue is empty.\n");
    printf("The queue's length is: %d\n", getLength(queue));

    enqueue(queue, 1);
    enqueue(queue, 2);
    printf("The top item on the queue is: %d\n", peek(queue));
    enqueue(queue, 3);
    printf("The queue's length is: %d\n", getLength(queue));
    printf("Item %d was removed from the queue.\n", dequeue(queue));
    printf("The top item on the queue is: %d\n", peek(queue));
    enqueue(queue, 4);
    displayQueue(queue);
    enqueue(queue, 5);
    printf("Item %d was removed from the queue.\n", dequeue(queue));
    enqueue(queue, 6);
    printf("The queue's length is: %d\n", getLength(queue));
    displayQueue(queue);
    printf("Item %d was removed from the queue.\n", dequeue(queue));
    printf("The queue is %sempty.\n", isEmpty(queue) ? "" : "not ");
    printf("Item %d was removed from the queue.\n", dequeue(queue));
    printf("Item %d was removed from the queue.\n", dequeue(queue));
    printf("The queue's length is: %d\n", getLength(queue));
    printf("Item %d was removed from the queue.\n", dequeue(queue));
    printf("An item was not dequeued.\n");
    printf("The queue is %sempty.\n", isEmpty(queue) ? "" : "not ");

    // Free the queue structure (all nodes should have been dequeued by now)
    free(queue);

    return 0;
}

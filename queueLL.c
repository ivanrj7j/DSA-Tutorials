#include <stdio.h>
#include <stdlib.h>

struct QNode {
    int key;
    struct QNode* next;
};

struct Queue {
    struct QNode *front, *rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Queue* q, int k) {
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        printf("Enqueued %d to the queue.\n", k);
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
    printf("Enqueued %d to the queue.\n", k);
}

void dequeue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }
    struct QNode* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    printf("Dequeued element: %d\n", temp->key);
    free(temp);
}

void displayQueue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    struct QNode* temp = q->front;
    printf("Queue elements: FRONT -> ");
    while (temp != NULL) {
        printf("%d -> ", temp->key);
        temp = temp->next;
    }
    printf("REAR\n");
}

int main() {
    struct Queue* q = createQueue();
    int choice, value;

    while (1) {
        printf("\n--- Queue Menu (Linked List) ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(q, value);
                displayQueue(q);
                break;
            case 2:
                dequeue(q);
                displayQueue(q);
                break;
            case 3:
                displayQueue(q);
                break;
            case 4:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
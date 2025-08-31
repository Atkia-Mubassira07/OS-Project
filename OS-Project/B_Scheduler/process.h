#ifndef PROCESS_H
#define PROCESS_H

// Define the Process struct
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int start_time;
    int completion_time;
    int waiting_time;
    int response_time;
} Process;

// Define a Node for the linked list (to act as a queue)
typedef struct Node {
    Process process;
    struct Node* next;
} Node;

// Function prototypes for queue operations
void push(Node** head, Process p);
Process pop(Node** head);
int is_empty(Node* head);

#endif
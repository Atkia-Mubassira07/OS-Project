#include <stdio.h>
#include <stdlib.h>
#include "process.h"

// Queue operations
void push(Node** head, Process p) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    new_node->process = p;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

Process pop(Node** head) {
    if (*head == NULL) {
        // Return a dummy process to indicate an error
        Process dummy = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
        return dummy;
    }
    Node* temp = *head;
    Process p = temp->process;
    *head = (*head)->next;
    free(temp);
    return p;
}

int is_empty(Node* head) {
    return head == NULL;
}

// Main simulation function
void simulate_scheduler(Process* processes, int num_processes) {
    Node* high_priority_queue = NULL;
    Node* interactive_queue = NULL;
    Node* batch_queue = NULL;

    int current_time = 0;
    int completed_processes_count = 0;
    Process* completed_processes = (Process*)malloc(num_processes * sizeof(Process));
    if (completed_processes == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    while (completed_processes_count < num_processes) {
        // Step 1: Add newly arrived processes to queues
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time == current_time) {
                if (processes[i].priority == 1) {
                    push(&high_priority_queue, processes[i]);
                } else if (processes[i].priority == 2) {
                    push(&interactive_queue, processes[i]);
                } else {
                    push(&batch_queue, processes[i]);
                }
            }
        }

        // Step 2: Implement multi-level scheduler logic
        Process current_process;
        int queue_selected = 0;

        if (!is_empty(high_priority_queue)) {
            current_process = high_priority_queue->process;
            queue_selected = 1;
        } else if (!is_empty(interactive_queue)) {
            current_process = interactive_queue->process;
            queue_selected = 2;
        } else if (!is_empty(batch_queue)) {
            current_process = batch_queue->process;
            queue_selected = 3;
        } else {
            // No process to run, idle CPU
            current_time++;
            continue;
        }

        // Step 3: Run the selected process for one time unit
        if (current_process.start_time == -1) {
            current_process.start_time = current_time;
            current_process.response_time = current_time - current_process.arrival_time;
        }

        // Update the process in its queue
        if (queue_selected == 1) {
            high_priority_queue->process.remaining_time--;
            if (high_priority_queue->process.remaining_time == 0) {
                Process p = pop(&high_priority_queue);
                p.completion_time = current_time + 1;
                p.waiting_time = p.completion_time - p.arrival_time - p.burst_time;
                completed_processes[completed_processes_count++] = p;
            }
        } else if (queue_selected == 2) {
            interactive_queue->process.remaining_time--;
            if (interactive_queue->process.remaining_time == 0) {
                Process p = pop(&interactive_queue);
                p.completion_time = current_time + 1;
                p.waiting_time = p.completion_time - p.arrival_time - p.burst_time;
                completed_processes[completed_processes_count++] = p;
            }
        } else { // Batch queue
            batch_queue->process.remaining_time--;
            if (batch_queue->process.remaining_time == 0) {
                Process p = pop(&batch_queue);
                p.completion_time = current_time + 1;
                p.waiting_time = p.completion_time - p.arrival_time - p.burst_time;
                completed_processes[completed_processes_count++] = p;
            }
        }
        current_time++;
    }

    // Step 4: Calculate and print performance metrics
    double total_turnaround_time = 0, total_waiting_time = 0, total_response_time = 0;
    int total_burst_time = 0;
    
    for (int i = 0; i < num_processes; i++) {
        total_turnaround_time += completed_processes[i].completion_time - completed_processes[i].arrival_time;
        total_waiting_time += completed_processes[i].waiting_time;
        total_response_time += completed_processes[i].response_time;
        total_burst_time += completed_processes[i].burst_time;
    }
    
    double avg_turnaround_time = total_turnaround_time / num_processes;
    double avg_waiting_time = total_waiting_time / num_processes;
    double avg_response_time = total_response_time / num_processes;
    double cpu_utilization = ((double)total_burst_time / current_time) * 100;

    printf("\nSimulation Results:\n");
    printf("Average Turnaround Time: %.2f units\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f units\n", avg_waiting_time);
    printf("Average Response Time: %.2f units\n", avg_response_time);
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
    
    free(completed_processes);
}

int main() {
    // Example processes with different priorities
    Process processes[] = {
        {1, 0, 8, 8, 2, -1, -1, 0, -1},  // Interactive
        {2, 1, 5, 5, 1, -1, -1, 0, -1},  // High Priority
        {3, 2, 12, 12, 3, -1, -1, 0, -1} // Batch
    };
    int num_processes = sizeof(processes) / sizeof(processes[0]);

    simulate_scheduler(processes, num_processes);

    return 0;
}
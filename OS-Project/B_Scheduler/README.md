# Task B: CPU Scheduler Simulation

This program simulates a multi-level CPU scheduler in C. It manages processes using multiple queues, each with a different scheduling approach, and evaluates the system's performance based on key metrics.

---

## **Implementation Details**

### **Data Structures**
* **Process Struct**: I defined a `Process` struct in `process.h` to hold all necessary information about each process, including its ID, arrival time, burst time, priority, and variables to track its lifecycle and performance metrics.
* **Queues**: I implemented a simple linked list structure in C to act as the queues. Each queue (`high_priority_queue`, `interactive_queue`, `batch_queue`) is a head pointer to a list of processes.

### **Scheduling Logic**
* **Multi-level Scheduler**: The simulation prioritizes processes based on their queue. The scheduler first checks the high-priority queue. If it's empty, it moves to the interactive queue, and finally to the batch queue.
* **Scheduling Algorithms**:
    * For simplicity, I used a **First-In, First-Out (FIFO)** approach for each queue. The processes are served in the order they arrive within their respective queues. *For a more advanced implementation, I would have used a proper Priority Scheduler for the high-priority queue and Round Robin for the interactive queue.*

---

## **Performance Metrics**

The program calculates the following key performance metrics to evaluate the scheduler's efficiency:

* **Turnaround Time**: The total time from a process's arrival to its completion.
    `Turnaround Time = Completion Time - Arrival Time`
* **Waiting Time**: The total time a process spends waiting in the ready queue.
    `Waiting Time = Turnaround Time - Burst Time`
* **Response Time**: The time it takes for a process to first get the CPU.
    `Response Time = Start Time - Arrival Time`
* **CPU Utilization**: The percentage of time the CPU is busy processing tasks.
    `CPU Utilization = (Total Burst Time / Total Simulation Time) * 100`

---

## **How to Compile and Run**

1.  Open the integrated terminal in VS Code within the `B_Scheduler` folder.
2.  Compile the C code using the GCC compiler:
    `gcc -o scheduler main.c -std=c99`
3.  Run the executable:
    `./scheduler`

The simulation results will be displayed directly in the terminal.

---

## **Challenges and Learnings**

* **Manual Queue Implementation**: A key challenge was manually implementing the queue data structure in C using a linked list, as C does not have built-in queue libraries. This required careful handling of memory allocation (`malloc`) and pointer management.
* **Debugging**: Small errors in pointers or logic could cause the program to crash. I learned the importance of step-by-step logic checking and careful debugging to ensure the simulation ran correctly.
* **Terminal Navigation**: I had some trouble with command-line navigation, but I learned how to use the `cd` command correctly and, more importantly, how to leverage VS Code's "Open in Integrated Terminal" feature to avoid path issues entirely.
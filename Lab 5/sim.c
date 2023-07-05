// PID: 730389109
// I pledge the COMP211 honor code.
// -----------------------------------
//  COMP 211 - Systems Fundamentals
//
//  Fall 2022 - Lab 6
// -----------------------------------

#include "task.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//    Runs the linked list of task_structs using a scheduling queue. 
//    This should be done by:
//      - Scheduling the tasks (min heapifying the linked list)
//      - Until the queue is empty:
//          - remove and run the highest priority task in the queue
//          - appending the task back on to the queue if it was not completed
//          - re-scheduling the tasks
//
//  Arguments:
//    cycles_per_task: positive integer number of CPU cycles
//
//  Return:
//    None

void dispatcher(unsigned int cycles_per_task) {
   task_struct *current_task = NULL;
   schedule();
   unsigned int size0 = size();
   while (size0 != 0){
       current_task = remove_task(get_task(0)->pid);
       run(current_task, cycles_per_task);
       if (current_task->remaining_cycles > 0){
         append_task(current_task->pid, current_task->priority, current_task->remaining_cycles);
       }
       schedule();
       size0 = size();  
   }  
  
} // end dispatcher() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//    Simulate running a task by:
//      - decrementing the number of remaining cycles for the task
//      - printing out "Task {pid} run for {num_cycles} cycle(s)."
//      - if the task is completed, also printing out "Task {pid} Completed."
//
//  Arguments:
//    task: a pointer to the task_struct to be run
//    num_cycles: the number of CPU cycles to simulate
//
//  Return:
//    None

void run(task_struct* task, unsigned int num_cycles) {
    task->remaining_cycles -= num_cycles;

    printf("Task %d run for %d cycle(s).\n", task->pid, num_cycles);

    if (task->remaining_cycles <= 0) {
        printf("Task %d Completed.\n", task->pid);
    }
  
} // end run() function

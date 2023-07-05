// PID: 730389109
// I pledge the COMP211 honor code.

// -----------------------------------
// 	COMP 211 - Systems Fundamentals
//
//	Fall 2022 - Lab 6
// -----------------------------------

#include "task.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TASK_OP_PASS 0
#define TASK_OP_ERROR 1
#define NOT_FOUND 0
#define DEBUG 0

task_struct* head = NULL;
task_struct* tail = NULL;

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Remove all task_structs in the linked list
//      (i.e., size = 0 ).
//
//      ** This includes unallocating memory used by
//      each task_struct in the linked list. **
//
//  Arguments:
//      None
//
//  Return:
//      None

void clear() {
  task_struct* current = head;
  task_struct* next = NULL;

  while ( current != NULL){
      next = current->next;
      free(current);
      current = next;
  }

  head = NULL;

} // end clear() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Total number of task_structs in the linked list
//
//  Arguments:
//      None
//
//  Return:
//      non-negative integer value (if 0, then the list is empty)

unsigned int size() {
    
    int counter = 0;
    task_struct* current = head;
    while (current != NULL){
      counter++;
      current = current->next;
    }
    return counter; 

} // end size() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Create a new task_struct:
//          - allocate memory,
//          - set task_struct priority to specified priority,
//          - set task_struct pid to specified pid.
//          - set task_struct remaining_cycles to specified cycles.
//      Then append the task_struct to the end of the linked list
//
//  Arguments:
//      pid: unsigned integer value (zero or positive integer number)
//      priority: unsigned integer value (zero or positive integer number)
//      cycles: integer value
//
//  Return:
//      0 (TASK_OP_PASS):	append operation is successful
//      1 (TASK_OP_ERROR):	append operation is not successful
//                      i.e., duplicate pid in the linked list

unsigned int append_task(unsigned int pid, unsigned int priority, int cycles) {

    task_struct *task = (task_struct*) malloc(sizeof(task_struct));

   task->pid = pid;
   task->priority = priority;
   task->remaining_cycles = cycles;
   task->next = NULL;

   if (size() == 0){
       head = task;
   } else {
       task_struct *current_task = head;
       while (current_task->next != NULL) {
           if (current_task->pid == pid) {
               free(task);
               return TASK_OP_ERROR;
           }
           current_task = current_task->next;
        }
        current_task->next = task;
   }
   return TASK_OP_PASS;

} // end append_task() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Create a new task_struct:
//          - allocate memory,
//          - set task_struct priority to specified priority,
//          - set task_struct pid to specified pid.
//          - set task_struct remaining_cycles to specified cycles.
//      Then insert the task_struct at the specified index position
//      in the linked list.
//
//      Note: Shifts the task_struct currently at specified index
//      position (if any) and any subsequent task_structs to the
//      right (effectively adding one to their index position).
//
//  Arguments:
//      index: unsigned integer value (zero or positive integer value)
//      pid: unsigned integer value (zero or positive integer value)
//      priority: unsigned integer value (zero or positive integer value)
//      cycles: integer value
//
//  Return:
//      0 (TASK_OP_PASS):	insert operation is successful
//      1 (TASK_OP_ERROR):	insert operation is not successful
//                      i.e., duplicate pid in the linked list -or- index is out of range (index < 0 || index > size())

unsigned int insert_task(unsigned int index, unsigned int pid,
                         unsigned int priority, int cycles) {

    if (index < 0 || index > size() || exists(pid)!=NULL) {
      return TASK_OP_ERROR;
    }

    task_struct *task = (task_struct*) malloc(sizeof(task_struct));

    task->pid = pid;
    task->priority = priority;
    task->remaining_cycles = cycles;
    task->next = NULL;

    if (index == 0){
        task->next = head;
        head = task;
    } else{
        task_struct *current_task = head;
        unsigned int i = 0;
        while ( i < index - 1){
            current_task = current_task->next;
            i++;
        }
        if (current_task->next != NULL && current_task->next->pid == pid) {
            free(task);
            return TASK_OP_ERROR;
        } 
        task->next = current_task->next;
        current_task->next = task;
    }

    return TASK_OP_PASS;
         

} // end insert_task() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Change the location of an existing task_struct (using pid)
//      in the linked list to the specified index position.
//
//      Note: Shifts the task_struct currently at specified index
//      position that (if any) and any subsequent task_structs to
//      the right (effectively adding one to their index position).
//
//  Arguments:
//      index: unsigned integer value (zero or positive integer value)
//      pid: unsigned integer value (zero or positive integer value)
//  Return:
//      0 (TASK_OP_PASS):	set operation is successful
//      1 (TASK_OP_ERROR):	set operation is not successful
//                      i.e., pid is not in the linked list -or- index is out of range ( index < 0 || index >= size() )

unsigned int set_task(unsigned int index, unsigned int pid) {

    task_struct *current_task = head;
    task_struct *prev_task = NULL;
    while (current_task !=NULL && current_task->pid != pid){
       prev_task = current_task;
       current_task = current_task->next;
    }

    if (current_task == NULL){
       return TASK_OP_ERROR;
    }

    
   if (index < 0 || index >= size()){
      return TASK_OP_ERROR;
   }
   if (current_task->pid == head->pid) {
      head = current_task->next;
   } else {
      prev_task->next = current_task->next;
   } 

   task_struct *index_task = head;
   task_struct *prev_index_task = NULL;

   for (unsigned int i = 0; i < index; i++){
       prev_index_task = index_task;
       index_task = index_task->next;
   }

   if (prev_index_task->next != current_task) {
       prev_index_task->next = current_task;
   } else {
       head = current_task;
   }
   current_task->next = index_task;

   return TASK_OP_PASS;
    
}
      

 // end set_task() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Remove a task_struct (using pid) in the linked list and
//      return it.
//
//      ** This operation does not unallocate memory occupied
//      by the task_struct. **
//
//      Note: Shifts any subsequent task_structs to the left
//      in the linked list (effectively subtracts one from their
//      index position).
//
//  Arguments:
//      pid: unsigned integer value (zero or positive integer value)
//
//  Return:
//      task_stuct*:	if the operation is successful
//      NULL:	if the pid is not in the linked list

task_struct* remove_task(unsigned int pid) {

  if (!exists(pid)){
      return NULL;
  }

  task_struct *current_task = head;
  task_struct *prev_task = NULL;

  while (current_task != NULL) {
    if (current_task->pid == pid) {
        if (prev_task == NULL) {
            head = current_task->next;
        } else {
            prev_task->next = current_task->next;
        }
        return current_task;
    }
    prev_task = current_task;
    current_task = current_task->next;
     
  }
  return NULL; 

} // end remove_task() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Get the task_struct for the specified pid value
//      in the linked list and returns the task_struct.
//
//      ** This operation does not unallocate memory occupied
//      by the task_struct. **
//
//  Arguments:
//      pid: unsigned integer value (zero or positive integer value)
//
//  Return:
//      task_stuct*:	operation is successful
//      NULL:	pid is not in the linked list

task_struct* exists(unsigned int pid) {

  task_struct *current_task = head;
  while (current_task != NULL) {
      if (current_task->pid == pid) {
          return current_task;
      }
      current_task = current_task->next;
  }

  
  return NULL; // this is just a place holder 

} // end exists() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Get the task_struct at the specified index position
//      in the linked list and returns the task_struct.
//
//      ** This operation does not unallocate memory occupied
//      by the task_struct. **
//
//  Arguments:
//      index: unsigned integer value (zero or positive integer value)
//
//  Return:
//      task_stuct*:	operation is successful
//      NULL:	index is out of range ( index < 0 || index >= size() )

task_struct* get_task(unsigned int index) {

  if (index < 0 || index >= size()) {
     return NULL;
  }
  
  task_struct *current_task = head;
 unsigned int i = 0;
  while (current_task != NULL && i < index) {
     current_task = current_task->next;
     i++;
 }
 return current_task; 

} // end get_task() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Swap the position of two pids (e.g., pid_1 and pid_2)
//      in the linked list
//
//      Note: there is an easy and a hard way to achieve
//      operation, you decide :)
//
//  Arguments:
//      pid_1: unsigned integer value (zero or positive integer value)
//      pid_2: unsigned integer value (zero or positive integer value)
//
//  Return:
//      0 (TASK_OP_PASS):	swap operation is successful //      1 (TASK_OP_ERROR):	swap operation is not successful //                      i.e., pid_1 and/or pid_2 are not in the linked list -or- //                              pid_1 == pid_2 //

unsigned int swap(unsigned int pid_1, unsigned int pid_2) {

    task_struct *task1 = get_task(pid_1);
    task_struct *task2 = get_task(pid_2);
    task_struct *current_task = head;
    unsigned int t1index = 0;
    unsigned int t2index = 0;
    if (pid_1 == pid_2 || task1 == NULL || task2 == NULL){
        return TASK_OP_ERROR;
    }
    for (unsigned int i = 0; i < size(); i++){
        if (current_task->pid == pid_1){
            break;
        }
        current_task = current_task->next;
        t1index = i;
    }
    current_task = head;
    for (unsigned int i = 0; i< size(); i++){
        if (current_task->pid == pid_2){
            break;
        }
        current_task = current_task->next;
        t2index = i;
    }
    set_task(t2index, pid_1);
    set_task(t1index, pid_2);
    return TASK_OP_PASS;
} // end swap() function

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Perform the min heapify algorithm on the linked list.
//      See Heaps.pdf documentation in github repo.
//
//  Arguments:
//      None
//
//  Return:
//      None
//

void schedule() {
     for (int i = floor((size()-2) / 2); (i = 0); i--){
         unsigned int k = i;
         task_struct *current_task = get_task(k);
         task_struct *task_start = head;
         unsigned int taskIndex = 0;
         while (task_start != NULL){
             if (task_start->pid == current_task->pid){
                 break;
             }
             taskIndex++;
         }
         bool heap = false;
         while (heap == false && (2*k+2) <= size()){
             unsigned int j = 2*k+1;
             if (j+1 <= size()-1 && get_task(taskIndex)->priority < current_task->priority){
                 j++;
             }
             if (current_task->priority <= get_task(j)->priority) {
                 heap = true;
             } else {
                 swap(get_task(k)->pid, get_task(j)->pid);
                 k = j;
             }
        }
     }
}

// ------------------------------------
// Function prototype
// ------------------------------------
//  Description:
//      Print the pid and priority of each task_struct in the
//      linked list.
//
//  ** DO NOT MODIFY THE CODE IN THIS FUNCTION **
//  ** USED BY THE AUTOGRADER TO EVALUATE TESTCASES **
//
//  Arguments:
//      None
//
//  Return:
//      None
//

void print_tasks() {
  task_struct* p_task = head;

  if (p_task == NULL) {
    printf("[ empty ]\n");
  } else {
    printf("(%d)[", size());

    while (p_task != NULL) {
      printf(" %d:%d:%d:%.2f", p_task->pid, p_task->priority, p_task->remaining_cycles, (float)p_task->priority/(float)p_task->remaining_cycles);
      p_task = p_task->next;
    }

    printf(" ]\n");
  }

} // end print_tasks() function

// ------------------------------------
// Function implementation
// ------------------------------------
//  Description:
//      Compares two floating point numbers.
//
//  ** DO NOT MODIFY THE CODE IN THIS FUNCTION **
//  ** USED BY THE AUTOGRADER TO EVALUATE TESTCASES **
//
//  Arguments:
//      a: float
//      b: float
//
//  Return:
//       0: |a - b| < epsilon
//       1:  a < b
//      -1:  a > b
//

int compare_floats(float a, float b) {
    const float epsilon = 0.0001;
    return fabs(a - b) < epsilon ? 0 : a < b ? 1 : -1;
} // end compare_floats() function

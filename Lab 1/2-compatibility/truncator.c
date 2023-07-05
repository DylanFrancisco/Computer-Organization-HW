// PID: 730389109
// I pledge the COMP 211 honor code.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main()
{
    
    int total_lines_over = 0;
    int lines_over[100];
    int line_num = 0;
    int j = 0;
    int i = 0;
    int c;
    bool line_over = false;


    while ((c = getchar()) != EOF){
        i++; 
        if (c == 10){             //While loop that reads and prints chars until it reaches the EOF. If c is a newline, we incriment line_num
           putchar(c); 
           line_num ++;           //and reset i since we are at a new line
           i = 0;
           if (line_over){
               lines_over[j] = line_num -1;
               j++;                          //If the line has >50 chars, it adds that line number to the array and incriments
               total_lines_over++;
               line_over = false;
           }
        } 
       
        else if (i != 0 && i > 50){
           putchar('\n');
           putchar(c);           //If we reach char 50 of a line, print a new line char and change line_over to true
           line_over = true;
           i = 1;
        }else{
           putchar(c);
        }
        

    }    
    
    printf("\n");       
    printf("Total lines over 50 chars: %i\n", total_lines_over);
    printf("Offending lines: ");
    for (int i = 0; i < total_lines_over; i++){    //prints here. to print the array, we will print each elements for the total num of lines >50 chars
        printf("%d, ", lines_over[i]);
        
    }
    printf("\n");
    return 0;
}   

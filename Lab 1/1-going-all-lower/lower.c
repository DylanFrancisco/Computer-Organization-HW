// PID: 730389109
// I pledge the COMP 211 honor code.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Add 32 to any char value to get that value in lowercase



int main()
{
   char input_str[300]; // Create the input for the string we will be accepting
   int size = (sizeof(input_str)/ sizeof(char)); //Find size of the string
   fgets(input_str, size, stdin); //use fgets to take in input_str to make sure all values are taken in
   int i;

   for (i=0; i < size; i++){
        
       if (input_str[i] >= 'A' && input_str[i] <= 'Z'){ //For loop that will iterate over the str and for any uppercase letter
           input_str[i] = input_str[i] + 32;            //it will add 32 to it to make the ascii code the lowercase version
       }
              
   }
   
   printf("%s", input_str);
   return 0; 

}

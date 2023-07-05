// PID: 730389109
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    char binaryArray[32];
    int i;
    for (i = 0; i < 32; i++) {
        binaryArray[i] = argv[1][i]; //for loop to copy arrary contents and flip the bits in the array
        if (binaryArray[i] == 49){   //had trouble with atoi so used 49 to represent int 1
            binaryArray[i] = 0;
        } else {
            binaryArray[i] = 1;
        } 
    }

    for (i = 31; i >= 0; i--){
        if (binaryArray[i] == 0){
            binaryArray[i] = 1;     //adds 1 to new binary number by looking left to right and flipping any 1's to 0's
            break;                  //the first 0 we see will be flipped to a 1 and the for loop breaks
        } else {
            binaryArray[i] = 0;
        }
    }

    printf("The negation of the 32-bit two's complement integer %s is: ", argv[1]);

    for (i = 0; i < 32; i++) {
        printf("%d", binaryArray[i]);
    }

    printf(".\n");
    return 0;
}

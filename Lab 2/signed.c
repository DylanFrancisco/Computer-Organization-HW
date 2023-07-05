// PID: 730389109
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int input = atoi(argv[1]);
    int sign = 1;
    if (input < 0) {         //Stores the int passed in input and if is negative, make sign = -1 
        sign = -1;             //and set input back to a postive num
        input = -input;
    }

    if (input > 32767) {
        if (sign == 1){
            printf("The signed 16-bit representation of +%d is: not possible.\n", input * sign);
        } else {
            printf("The signed 16-bit representation of %d is: not possible.\n", input * sign);
        }
    } else {
        if (sign == 1){
            printf("The signed 16-bit representation of +%d is: ", input * sign);
        } else {
            printf("The signed 16-bit representation of %d is: ", input * sign);
        }
        int i;
        int binary[16];
        for (i = 0; i < 16; i++) {
            binary[i] = input % 2;  //as long as input is a valid int, mod the input to get the correct binary digit
            input /= 2;
        }

        if (sign == -1) {
            binary[15] = 1;       //if the orignal input was negative, change the msb to 1
        }

        for (i = 15; i >= 0; i--) {
            printf("%d", binary[i]);
        }
        printf(".\n");
    }

    return 0;
}

// PID: 730389109 
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int input = atoi(argv[1]);
    if (input > 0){
        printf("The two's complement 16-bit representation of +%d is: ", input);
    } else {
        printf("The two's complement 16-bit representation of %d is: ", input);
    }
    if (input < -32767 || input > 32767){ //much better implementation to find correct sign without using an extra variable
        printf("not possible");
    } else {
        int binary[16];
        if (input < 0){
            input = input + 32768; //if an input is negative, add that input to the positive amount of avaliable ints to find the positive value
            binary[15] = 1;
        } else {
            binary[15] = 0;
        }

        int i;
        for ( i = 0; i < 15; i++ ){
            binary[i] = input % 2;
            input = input / 2;
        }
        for ( i = 15; i >= 0; i-- ){
            printf("%d", binary[i]);
        }
    }
    printf(".\n");
    return 0;

}

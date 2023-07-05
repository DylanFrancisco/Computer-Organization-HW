// PID: 730389109
// I pledge the COMP 211 honor code.
//
#include "bit_utils.h"

char* itob(int num, int size) {
    char *binNum = malloc(sizeof(size) * 8);
    unsigned int input = num;
    int i = 0;
    while (i<size){
        if (input % 2 == 1){
            binNum[size -i -1] = '1';
        } else{
            binNum[size - i - 1] = '0';
        }
        input = input / 2;
        i++;
     }
    
    return binNum;
}

int mask_bits(int num, int mask){
    return num & mask;
}

int set_bits(int num, int bits){
    return num | bits;
}

int inverse_bits(int num, int bits){
    return num ^ bits;
}

int bit_select(int num, int startbit, int endbit){
    int size = sizeof(num) * 8;
    int shiftLeft = (int)((unsigned int)num << (size - 1 - startbit));
    int shiftRight = (int)((unsigned int)shiftLeft >> (size - 1 - startbit +endbit));
    return shiftRight;
}

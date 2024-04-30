#include <stdio.h>
#include <stdint.h>

uint8_t bcd_add_overflow(uint8_t* result, uint8_t x, uint8_t y){
    uint8_t sum = x + y;
    uint8_t carry = 0;
    if(sum > 99){
        sum = (sum - 100);
        carry = 1;
    }
    
    *result = sum;
    return carry;
}

uint8_t bcd_add(uint8_t x, uint8_t y){
    uint8_t b_xh = ((x >> 4) & 0xF);
    uint8_t b_xl = ((x >> 0) & 0xF);
    uint8_t b_yh = ((y >> 4) & 0xF);
    uint8_t b_yl = ((y >> 0) & 0xF);
    
    uint8_t d_x = (b_xh*10) + b_xl;
    uint8_t d_y = (b_yh*10) + b_yl;

    uint8_t sum, carry;
    carry = bcd_add_overflow(&sum, d_x, d_y);
    carry ? printf("carry!\n") : printf("no carry!\n");
    return sum;
}

int main(int argc, char** argv){
    uint8_t test_x = 0x99;
    uint8_t test_y = 0x02;
    uint8_t test_sum = bcd_add(test_x, test_y);

    return 0;
}

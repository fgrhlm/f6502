#include <stdio.h>
#include <stdint.h>

uint8_t bcd_sub(uint8_t* res, uint8_t x, uint8_t y, uint8_t c){
    uint8_t carry_out = 1;

    int16_t t_sum = (uint16_t)(x & 0x0F) - (uint16_t)(y & 0x0F) - !c;
    if(t_sum < 0){ t_sum = ((t_sum - 6) & 0x0F) - 16; }
    
    int16_t sum = (x & 0xF0) - (y & 0xF0) + t_sum;
    if(sum < 0){ sum = sum - 0x60; }
    
    *res = (sum & 0x00FF);
    return carry_out;
}

int main(int argc, char** argv){
    uint8_t tx[] = {0x00,0x00,0x00,0x0a,0x0b,0x9a,0x9b};
    uint8_t ty[] = {0x00,0x00,0x01,0x00,0x00,0x00,0x00};
    uint8_t tz[] = {0x99,0x00,0x99,0x0a,0x0a,0x9a,0x9a};
    uint8_t tc[] = {0,   1,   1,   1,   0,   1,   0};

    for(int i=0; i<7; i++){
        uint8_t x,y,z,c,res,carry;
        x = tx[i];
        y = ty[i];
        z = tz[i];
        c = tc[i];
        carry = bcd_sub(&res, x, y, c);
        printf("%02x - %02x = %02x (%02x) C -> %x\n\n", x, y, z, res, carry);
    }

    return 0;
}

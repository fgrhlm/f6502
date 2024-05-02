#include <stdio.h>
#include <stdint.h>

uint8_t bcd_add(uint8_t* sum, uint8_t x, uint8_t y, uint8_t c){
    uint8_t hi, lo, carry;

    carry = 0;

    lo = (x & 0xF) + (y & 0xF) + c;
    hi = (x >> 4) + (y >> 4) + (lo > 0xF);
    
    if(lo >= 10){ lo = lo + 6; }
    if(hi >= 10){ hi = hi + 6; }
    
    *sum = ((hi << 4) | (lo & 0xF)) & 0xFF;
    
    return carry;
}

int main(int argc, char** argv){
    uint8_t tx[] = {0x58, 0x12, 0x15};
    uint8_t ty[] = {0x46, 0x34, 0x26};
    uint8_t tz[] = {0x05, 0x46, 0x41};
    uint8_t tc[] = {1,    0,    0};

    for(int i=0; i<3; i++){
        uint8_t x,y,z,c,res,carry;
        x = tx[i];
        y = ty[i];
        z = tz[i];
        c = tc[i];
        carry = bcd_add(&res, x, y, c);
        printf("%02x + %02x = %02x (%x) C -> %x\n\n", x, y, z, res, carry);
    }
    return 0;
}

#include <stdio.h>
#include <stdint.h>

uint8_t bcd_sub(uint8_t* res, uint8_t x, uint8_t y, uint8_t c){
    uint8_t hi, lo, out_carry, in_carry, sum, temp_sum;

    in_carry = c;
    
    out_carry = 0;
    lo = (x & 0x0F) - (y & 0x0F) - !in_carry;
    if(lo & 0x10){ lo = lo - 0x06; }

    hi = (x >> 4) - (y >> 4) - (lo & 0x10);
    if(hi & 0x10){ hi = hi - 0x06; }

    //uint8_t v_flag = get_bit((x^temp_sum) & (y^temp_sum), 7);
    

    *res = ((hi << 4) | (lo & 0xF)) & 0xFF;
  
    //set_flag(c, FLAG_C, out_carry);
    //set_flag(c, FLAG_N, get_bit(temp_sum, 7));
    //set_flag(c, FLAG_Z, sum == 0);
    //set_flag(c, FLAG_V, v_flag);
    
    return out_carry;
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

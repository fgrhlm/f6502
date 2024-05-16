#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>

#include "cpu.h"
#include "utils.h"

char* addressing_mode_to_str(addr_mode am){
    char* addr_mode_strings[] = { 
        "ACCUMULATOR", 
        "IMMEDIATE", 
        "ZERO_PAGE", 
        "ZERO_PAGE_X",
        "ZERO_PAGE_Y",
        "RELATIVE",
        "ABSOLUTE",
        "ABSOLUTE_X",
        "ABSOLUTE_Y",
        "ABSOLUTE_INDIRECT",
        "ZERO_PAGE_INDIRECT_X",
        "ZERO_PAGE_INDIRECT_Y",
        "IMPLIED",
    };

    return addr_mode_strings[am];
}

char* opcode_to_str(uint8_t op){
    char* str;
    switch(op){
        case 0x00: str = "brk"; break;
        case 0x18: str = "clc"; break;
        case 0xD8: str = "cld"; break;
        case 0x58: str = "cli"; break;
        case 0xB8: str = "clv"; break;
        case 0xCA: str = "dex"; break;
        case 0x88: str = "dey"; break;
        case 0xE8: str = "inx"; break;
        case 0xC8: str = "iny"; break;
        case 0x02: str = "jam"; break;
        case 0x12: str = "jam"; break;
        case 0x22: str = "jam"; break;
        case 0x32: str = "jam"; break;
        case 0x42: str = "jam"; break;
        case 0x52: str = "jam"; break;
        case 0x62: str = "jam"; break;
        case 0x72: str = "jam"; break;
        case 0x92: str = "jam"; break;
        case 0xB2: str = "jam"; break;
        case 0xD2: str = "jam"; break;
        case 0xF2: str = "jam"; break;
        case 0x1A: str = "nop"; break;
        case 0x3A: str = "nop"; break;
        case 0x5A: str = "nop"; break;
        case 0x7A: str = "nop"; break;
        case 0xDA: str = "nop"; break;
        case 0xEA: str = "nop"; break;
        case 0xFA: str = "nop"; break;
        case 0x48: str = "pha"; break;
        case 0x08: str = "php"; break;
        case 0x68: str = "pla"; break;
        case 0x28: str = "plp"; break;
        case 0x40: str = "rti"; break;
        case 0x60: str = "rts"; break;
        case 0x38: str = "sec"; break;
        case 0xF8: str = "sed"; break;
        case 0x78: str = "sei"; break;
        case 0xAA: str = "tax"; break;
        case 0xA8: str = "tay"; break;
        case 0xBA: str = "tsx"; break;
        case 0x8A: str = "txa"; break;
        case 0x9A: str = "txs"; break;
        case 0x98: str = "tya"; break;
        case 0x0A: str = "asl"; break;
        case 0x4A: str = "lsr"; break;
        case 0x2A: str = "rol"; break;
        case 0x6A: str = "ror"; break;
        case 0x69: str = "adc"; break;
        case 0x0B: str = "anc"; break;
        case 0x2B: str = "anc"; break;
        case 0x29: str = "and"; break;
        case 0x6B: str = "arr"; break;
        case 0x4B: str = "asr"; break;
        case 0xC9: str = "cmp"; break;
        case 0xE0: str = "cpx"; break;
        case 0xC0: str = "cpy"; break;
        case 0x49: str = "eor"; break;
        case 0xAB: str = "lax"; break;
        case 0xA9: str = "lda"; break;
        case 0xA2: str = "ldx"; break;
        case 0xA0: str = "ldy"; break;
        case 0x80: str = "nop"; break;
        case 0x82: str = "nop"; break;
        case 0x89: str = "nop"; break;
        case 0xC2: str = "nop"; break;
        case 0xE2: str = "nop"; break;
        case 0x09: str = "ora"; break;
        case 0xE9: str = "sbc"; break;
        case 0xEB: str = "sbc"; break;
        case 0xCB: str = "sbx"; break;
        case 0x8B: str = "xaa"; break;
        case 0x6D: str = "adc"; break;
        case 0x2D: str = "and"; break;
        case 0x0E: str = "asl"; break;
        case 0x2C: str = "bit"; break;
        case 0xCD: str = "cmp"; break;
        case 0xEC: str = "cpx"; break;
        case 0xCC: str = "cpy"; break;
        case 0xCF: str = "dcp"; break;
        case 0xCE: str = "dec"; break;
        case 0x4D: str = "eor"; break;
        case 0xEE: str = "inc"; break;
        case 0xEF: str = "isc"; break;
        case 0x4C: str = "jmp"; break;
        case 0x20: str = "jsr"; break;
        case 0xAF: str = "lax"; break;
        case 0xAD: str = "lda"; break;
        case 0xAE: str = "ldx"; break;
        case 0xAC: str = "ldy"; break;
        case 0x4E: str = "lsr"; break;
        case 0x0C: str = "nop"; break;
        case 0x0D: str = "ora"; break;
        case 0x2F: str = "rla"; break;
        case 0x2E: str = "rol"; break;
        case 0x6E: str = "ror"; break;
        case 0x6F: str = "rra"; break;
        case 0x8F: str = "sax"; break;
        case 0xED: str = "sbc"; break;
        case 0x0F: str = "slo"; break;
        case 0x4F: str = "sre"; break;
        case 0x8D: str = "sta"; break;
        case 0x8E: str = "stx"; break;
        case 0x8C: str = "sty"; break;
        case 0x7D: str = "adc"; break;
        case 0x3D: str = "and"; break;
        case 0x1E: str = "asl"; break;
        case 0xDD: str = "cmp"; break;
        case 0xDF: str = "dcp"; break;
        case 0xDE: str = "dec"; break;
        case 0x5D: str = "eor"; break;
        case 0xFE: str = "inc"; break;
        case 0xFF: str = "isc"; break;
        case 0xBD: str = "lda"; break;
        case 0xBC: str = "ldy"; break;
        case 0x5E: str = "lsr"; break;
        case 0x1C: str = "nop"; break;
        case 0x3C: str = "nop"; break;
        case 0x5C: str = "nop"; break;
        case 0x7C: str = "nop"; break;
        case 0xDC: str = "nop"; break;
        case 0xFC: str = "nop"; break;
        case 0x1D: str = "ora"; break;
        case 0x3F: str = "rla"; break;
        case 0x3E: str = "rol"; break;
        case 0x7E: str = "ror"; break;
        case 0x7F: str = "rra"; break;
        case 0xFD: str = "sbc"; break;
        case 0x9C: str = "shy"; break;
        case 0x1F: str = "slo"; break;
        case 0x5F: str = "sre"; break;
        case 0x9D: str = "sta"; break;
        case 0x79: str = "adc"; break;
        case 0x39: str = "and"; break;
        case 0xD9: str = "cmp"; break;
        case 0xDB: str = "dcp"; break;
        case 0x59: str = "eor"; break;
        case 0xFB: str = "isc"; break;
        case 0xBB: str = "las"; break;
        case 0xBF: str = "lax"; break;
        case 0xB9: str = "lda"; break;
        case 0xBE: str = "ldx"; break;
        case 0x19: str = "ora"; break;
        case 0x3B: str = "rla"; break;
        case 0x7B: str = "rra"; break;
        case 0xF9: str = "sbc"; break;
        case 0x9F: str = "sha"; break;
        case 0x9B: str = "shs"; break;
        case 0x9E: str = "shx"; break;
        case 0x1B: str = "slo"; break;
        case 0x5B: str = "sre"; break;
        case 0x99: str = "sta"; break;
        case 0x6C: str = "jmp"; break;
        case 0x61: str = "adc"; break;
        case 0x21: str = "and"; break;
        case 0xC1: str = "cmp"; break;
        case 0xC3: str = "dcp"; break;
        case 0x41: str = "eor"; break;
        case 0xE3: str = "isc"; break;
        case 0xA3: str = "lax"; break;
        case 0xA1: str = "lda"; break;
        case 0x01: str = "ora"; break;
        case 0x23: str = "rla"; break;
        case 0x63: str = "rra"; break;
        case 0x83: str = "sax"; break;
        case 0xE1: str = "sbc"; break;
        case 0x03: str = "slo"; break;
        case 0x43: str = "sre"; break;
        case 0x81: str = "sta"; break;
        case 0x71: str = "adc"; break;
        case 0x31: str = "and"; break;
        case 0xD1: str = "cmp"; break;
        case 0xD3: str = "dcp"; break;
        case 0x51: str = "eor"; break;
        case 0xF3: str = "isc"; break;
        case 0xB3: str = "lax"; break;
        case 0xB1: str = "lda"; break;
        case 0x11: str = "ora"; break;
        case 0x33: str = "rla"; break;
        case 0x73: str = "rra"; break;
        case 0xF1: str = "sbc"; break;
        case 0x93: str = "sha"; break;
        case 0x13: str = "slo"; break;
        case 0x53: str = "sre"; break;
        case 0x91: str = "sta"; break;
        case 0x65: str = "adc"; break;
        case 0x25: str = "and"; break;
        case 0x06: str = "asl"; break;
        case 0x24: str = "bit"; break;
        case 0xC5: str = "cmp"; break;
        case 0xE4: str = "cpx"; break;
        case 0xC4: str = "cpy"; break;
        case 0xC7: str = "dcp"; break;
        case 0xC6: str = "dec"; break;
        case 0x45: str = "eor"; break;
        case 0xE6: str = "inc"; break;
        case 0xE7: str = "isc"; break;
        case 0xA7: str = "lax"; break;
        case 0xA5: str = "lda"; break;
        case 0xA6: str = "ldx"; break;
        case 0xA4: str = "ldy"; break;
        case 0x46: str = "lsr"; break;
        case 0x04: str = "nop"; break;
        case 0x44: str = "nop"; break;
        case 0x64: str = "nop"; break;
        case 0x05: str = "ora"; break;
        case 0x27: str = "rla"; break;
        case 0x26: str = "rol"; break;
        case 0x66: str = "ror"; break;
        case 0x67: str = "rra"; break;
        case 0x87: str = "sax"; break;
        case 0xE5: str = "sbc"; break;
        case 0x07: str = "slo"; break;
        case 0x47: str = "sre"; break;
        case 0x85: str = "sta"; break;
        case 0x86: str = "stx"; break;
        case 0x84: str = "sty"; break;
        case 0x75: str = "adc"; break;
        case 0x35: str = "and"; break;
        case 0x16: str = "asl"; break;
        case 0xD5: str = "cmp"; break;
        case 0xD7: str = "dcp"; break;
        case 0xD6: str = "dec"; break;
        case 0x55: str = "eor"; break;
        case 0xF6: str = "inc"; break;
        case 0xF7: str = "isc"; break;
        case 0xB5: str = "lda"; break;
        case 0xB4: str = "ldy"; break;
        case 0x56: str = "lsr"; break;
        case 0x14: str = "nop"; break;
        case 0x34: str = "nop"; break;
        case 0x54: str = "nop"; break;
        case 0x74: str = "nop"; break;
        case 0xD4: str = "nop"; break;
        case 0xF4: str = "nop"; break;
        case 0x15: str = "ora"; break;
        case 0x37: str = "rla"; break;
        case 0x36: str = "rol"; break;
        case 0x76: str = "ror"; break;
        case 0x77: str = "rra"; break;
        case 0xF5: str = "sbc"; break;
        case 0x17: str = "slo"; break;
        case 0x57: str = "sre"; break;
        case 0x95: str = "sta"; break;
        case 0x94: str = "sty"; break;
        case 0xB7: str = "lax"; break;
        case 0xB6: str = "ldx"; break;
        case 0x97: str = "sax"; break;
        case 0x96: str = "stx"; break;
        case 0x90: str = "bcc"; break;
        case 0xB0: str = "bcs"; break;
        case 0xF0: str = "beq"; break;
        case 0x30: str = "bmi"; break;
        case 0xD0: str = "bne"; break;
        case 0x10: str = "bpl"; break;
        case 0x50: str = "bvc"; break;
        case 0x70: str = "bvs"; break;
    }

    return str;
}

uint16_t merge_bytes(uint8_t hi, uint8_t lo){ return (hi << 8) | (lo & 0xFF); }

bytes split_addr(uint16_t v){
    bytes split = { .hi = (v >> 8), .lo = (v & 0x00FF) };

    return split;
}

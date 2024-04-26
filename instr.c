#include <stdio.h>
#include <stdlib.h>

#include "instr.h"
#include "types.h"
#include "cpu.h"
#include "mem.h"
#include "utils.h"
#include "addr.h"

void instr_exec(cpu* c, mem* m, addr_mode am, void (*instr_ptr)(cpu*, mem*)){
    debug_out(LOG_FILE, "\tADDRESSING MODE: %s\n", addressing_mode_to_str(am));
    set_mode(c, am);

    (*instr_ptr)(c,m);
    debug_out(LOG_FILE, "[OP END @ %d]\n", get_pc(c));
}

void instr_parse(cpu* c, mem* m, uint8_t opcode){
    switch(opcode){
        case 0x00: instr_exec(c, m, AM_IMPLIED, &instr_brk); break;
        case 0x18: instr_exec(c, m, AM_IMPLIED, &instr_clc); break;
        case 0xD8: instr_exec(c, m, AM_IMPLIED, &instr_cld); break;
        case 0x58: instr_exec(c, m, AM_IMPLIED, &instr_cli); break;
        case 0xB8: instr_exec(c, m, AM_IMPLIED, &instr_clv); break;
        case 0xCA: instr_exec(c, m, AM_IMPLIED, &instr_dex); break;
        case 0x88: instr_exec(c, m, AM_IMPLIED, &instr_dey); break;
        case 0xE8: instr_exec(c, m, AM_IMPLIED, &instr_inx); break;
        case 0xC8: instr_exec(c, m, AM_IMPLIED, &instr_iny); break;
        case 0x02: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x12: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x22: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x32: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x42: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x52: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x62: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x72: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x92: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0xB2: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0xD2: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0xF2: instr_exec(c, m, AM_IMPLIED, &instr_jam); break;
        case 0x1A: instr_exec(c, m, AM_IMPLIED, &instr_nop); break;
        case 0x3A: instr_exec(c, m, AM_IMPLIED, &instr_nop); break;
        case 0x5A: instr_exec(c, m, AM_IMPLIED, &instr_nop); break;
        case 0x7A: instr_exec(c, m, AM_IMPLIED, &instr_nop); break;
        case 0xDA: instr_exec(c, m, AM_IMPLIED, &instr_nop); break;
        case 0xEA: instr_exec(c, m, AM_IMPLIED, &instr_nop); break;
        case 0xFA: instr_exec(c, m, AM_IMPLIED, &instr_nop); break;
        case 0x48: instr_exec(c, m, AM_IMPLIED, &instr_pha); break;
        case 0x08: instr_exec(c, m, AM_IMPLIED, &instr_php); break;
        case 0x68: instr_exec(c, m, AM_IMPLIED, &instr_pla); break;
        case 0x28: instr_exec(c, m, AM_IMPLIED, &instr_plp); break;
        case 0x40: instr_exec(c, m, AM_IMPLIED, &instr_rti); break;
        case 0x60: instr_exec(c, m, AM_IMPLIED, &instr_rts); break;
        case 0x38: instr_exec(c, m, AM_IMPLIED, &instr_sec); break;
        case 0xF8: instr_exec(c, m, AM_IMPLIED, &instr_sed); break;
        case 0x78: instr_exec(c, m, AM_IMPLIED, &instr_sei); break;
        case 0xAA: instr_exec(c, m, AM_IMPLIED, &instr_tax); break;
        case 0xA8: instr_exec(c, m, AM_IMPLIED, &instr_tay); break;
        case 0xBA: instr_exec(c, m, AM_IMPLIED, &instr_tsx); break;
        case 0x8A: instr_exec(c, m, AM_IMPLIED, &instr_txa); break;
        case 0x9A: instr_exec(c, m, AM_IMPLIED, &instr_txs); break;
        case 0x98: instr_exec(c, m, AM_IMPLIED, &instr_tya); break;
        case 0x0A: instr_exec(c, m, AM_ACCUMULATOR, &instr_asl); break;
        case 0x4A: instr_exec(c, m, AM_ACCUMULATOR, &instr_lsr); break;
        case 0x2A: instr_exec(c, m, AM_ACCUMULATOR, &instr_rol); break;
        case 0x6A: instr_exec(c, m, AM_ACCUMULATOR, &instr_ror); break;
        case 0x69: instr_exec(c, m, AM_IMMEDIATE, &instr_adc); break;
        case 0x0B: instr_exec(c, m, AM_IMMEDIATE, &instr_anc); break;
        case 0x2B: instr_exec(c, m, AM_IMMEDIATE, &instr_anc); break;
        case 0x29: instr_exec(c, m, AM_IMMEDIATE, &instr_and); break;
        case 0x6B: instr_exec(c, m, AM_IMMEDIATE, &instr_arr); break;
        case 0x4B: instr_exec(c, m, AM_IMMEDIATE, &instr_asr); break;
        case 0xC9: instr_exec(c, m, AM_IMMEDIATE, &instr_cmp); break;
        case 0xE0: instr_exec(c, m, AM_IMMEDIATE, &instr_cpx); break;
        case 0xC0: instr_exec(c, m, AM_IMMEDIATE, &instr_cpy); break;
        case 0x49: instr_exec(c, m, AM_IMMEDIATE, &instr_eor); break;
        case 0xAB: instr_exec(c, m, AM_IMMEDIATE, &instr_lax); break;
        case 0xA9: instr_exec(c, m, AM_IMMEDIATE, &instr_lda); break;
        case 0xA2: instr_exec(c, m, AM_IMMEDIATE, &instr_ldx); break;
        case 0xA0: instr_exec(c, m, AM_IMMEDIATE, &instr_ldy); break;
        case 0x80: instr_exec(c, m, AM_IMMEDIATE, &instr_nop); break;
        case 0x82: instr_exec(c, m, AM_IMMEDIATE, &instr_nop); break;
        case 0x89: instr_exec(c, m, AM_IMMEDIATE, &instr_nop); break;
        case 0xC2: instr_exec(c, m, AM_IMMEDIATE, &instr_nop); break;
        case 0xE2: instr_exec(c, m, AM_IMMEDIATE, &instr_nop); break;
        case 0x09: instr_exec(c, m, AM_IMMEDIATE, &instr_ora); break;
        case 0xE9: instr_exec(c, m, AM_IMMEDIATE, &instr_sbc); break;
        case 0xEB: instr_exec(c, m, AM_IMMEDIATE, &instr_sbc); break;
        case 0xCB: instr_exec(c, m, AM_IMMEDIATE, &instr_sbx); break;
        case 0x8B: instr_exec(c, m, AM_IMMEDIATE, &instr_xaa); break;
        case 0x6D: instr_exec(c, m, AM_ABSOLUTE, &instr_adc); break;
        case 0x2D: instr_exec(c, m, AM_ABSOLUTE, &instr_and); break;
        case 0x0E: instr_exec(c, m, AM_ABSOLUTE, &instr_asl); break;
        case 0x2C: instr_exec(c, m, AM_ABSOLUTE, &instr_bit); break;
        case 0xCD: instr_exec(c, m, AM_ABSOLUTE, &instr_cmp); break;
        case 0xEC: instr_exec(c, m, AM_ABSOLUTE, &instr_cpx); break;
        case 0xCC: instr_exec(c, m, AM_ABSOLUTE, &instr_cpy); break;
        case 0xCF: instr_exec(c, m, AM_ABSOLUTE, &instr_dcp); break;
        case 0xCE: instr_exec(c, m, AM_ABSOLUTE, &instr_dec); break;
        case 0x4D: instr_exec(c, m, AM_ABSOLUTE, &instr_eor); break;
        case 0xEE: instr_exec(c, m, AM_ABSOLUTE, &instr_inc); break;
        case 0xEF: instr_exec(c, m, AM_ABSOLUTE, &instr_isc); break;
        case 0x4C: instr_exec(c, m, AM_ABSOLUTE, &instr_jmp); break;
        case 0x20: instr_exec(c, m, AM_ABSOLUTE, &instr_jsr); break;
        case 0xAF: instr_exec(c, m, AM_ABSOLUTE, &instr_lax); break;
        case 0xAD: instr_exec(c, m, AM_ABSOLUTE, &instr_lda); break;
        case 0xAE: instr_exec(c, m, AM_ABSOLUTE, &instr_ldx); break;
        case 0xAC: instr_exec(c, m, AM_ABSOLUTE, &instr_ldy); break;
        case 0x4E: instr_exec(c, m, AM_ABSOLUTE, &instr_lsr); break;
        case 0x0C: instr_exec(c, m, AM_ABSOLUTE, &instr_nop); break;
        case 0x0D: instr_exec(c, m, AM_ABSOLUTE, &instr_ora); break;
        case 0x2F: instr_exec(c, m, AM_ABSOLUTE, &instr_rla); break;
        case 0x2E: instr_exec(c, m, AM_ABSOLUTE, &instr_rol); break;
        case 0x6E: instr_exec(c, m, AM_ABSOLUTE, &instr_ror); break;
        case 0x6F: instr_exec(c, m, AM_ABSOLUTE, &instr_rra); break;
        case 0x8F: instr_exec(c, m, AM_ABSOLUTE, &instr_sax); break;
        case 0xED: instr_exec(c, m, AM_ABSOLUTE, &instr_sbc); break;
        case 0x0F: instr_exec(c, m, AM_ABSOLUTE, &instr_slo); break;
        case 0x4F: instr_exec(c, m, AM_ABSOLUTE, &instr_sre); break;
        case 0x8D: instr_exec(c, m, AM_ABSOLUTE, &instr_sta); break;
        case 0x8E: instr_exec(c, m, AM_ABSOLUTE, &instr_stx); break;
        case 0x8C: instr_exec(c, m, AM_ABSOLUTE, &instr_sty); break;
        case 0x7D: instr_exec(c, m, AM_ABSOLUTE_X, &instr_adc); break;
        case 0x3D: instr_exec(c, m, AM_ABSOLUTE_X, &instr_and); break;
        case 0x1E: instr_exec(c, m, AM_ABSOLUTE_X, &instr_asl); break;
        case 0xDD: instr_exec(c, m, AM_ABSOLUTE_X, &instr_cmp); break;
        case 0xDF: instr_exec(c, m, AM_ABSOLUTE_X, &instr_dcp); break;
        case 0xDE: instr_exec(c, m, AM_ABSOLUTE_X, &instr_dec); break;
        case 0x5D: instr_exec(c, m, AM_ABSOLUTE_X, &instr_eor); break;
        case 0xFE: instr_exec(c, m, AM_ABSOLUTE_X, &instr_inc); break;
        case 0xFF: instr_exec(c, m, AM_ABSOLUTE_X, &instr_isc); break;
        case 0xBD: instr_exec(c, m, AM_ABSOLUTE_X, &instr_lda); break;
        case 0xBC: instr_exec(c, m, AM_ABSOLUTE_X, &instr_ldy); break;
        case 0x5E: instr_exec(c, m, AM_ABSOLUTE_X, &instr_lsr); break;
        case 0x1C: instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop); break;
        case 0x3C: instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop); break;
        case 0x5C: instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop); break;
        case 0x7C: instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop); break;
        case 0xDC: instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop); break;
        case 0xFC: instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop); break;
        case 0x1D: instr_exec(c, m, AM_ABSOLUTE_X, &instr_ora); break;
        case 0x3F: instr_exec(c, m, AM_ABSOLUTE_X, &instr_rla); break;
        case 0x3E: instr_exec(c, m, AM_ABSOLUTE_X, &instr_rol); break;
        case 0x7E: instr_exec(c, m, AM_ABSOLUTE_X, &instr_ror); break;
        case 0x7F: instr_exec(c, m, AM_ABSOLUTE_X, &instr_rra); break;
        case 0xFD: instr_exec(c, m, AM_ABSOLUTE_X, &instr_sbc); break;
        case 0x9C: instr_exec(c, m, AM_ABSOLUTE_X, &instr_shy); break;
        case 0x1F: instr_exec(c, m, AM_ABSOLUTE_X, &instr_slo); break;
        case 0x5F: instr_exec(c, m, AM_ABSOLUTE_X, &instr_sre); break;
        case 0x9D: instr_exec(c, m, AM_ABSOLUTE_X, &instr_sta); break;
        case 0x79: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_adc); break;
        case 0x39: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_and); break;
        case 0xD9: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_cmp); break;
        case 0xDB: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_dcp); break;
        case 0x59: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_eor); break;
        case 0xFB: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_isc); break;
        case 0xBB: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_las); break;
        case 0xBF: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_lax); break;
        case 0xB9: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_lda); break;
        case 0xBE: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_ldx); break;
        case 0x19: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_ora); break;
        case 0x3B: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_rla); break;
        case 0x7B: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_rra); break;
        case 0xF9: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_sbc); break;
        case 0x9F: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_sha); break;
        case 0x9B: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_shs); break;
        case 0x9E: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_shx); break;
        case 0x1B: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_slo); break;
        case 0x5B: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_sre); break;
        case 0x99: instr_exec(c, m, AM_ABSOLUTE_Y, &instr_sta); break;
        case 0x6C: instr_exec(c, m, AM_ABSOLUTE_INDIRECT, &instr_jmp); break;
        case 0x61: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_adc); break;
        case 0x21: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_and); break;
        case 0xC1: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_cmp); break;
        case 0xC3: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_dcp); break;
        case 0x41: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_eor); break;
        case 0xE3: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_isc); break;
        case 0xA3: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_lax); break;
        case 0xA1: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_lda); break;
        case 0x01: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_ora); break;
        case 0x23: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_rla); break;
        case 0x63: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_rra); break;
        case 0x83: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_sax); break;
        case 0xE1: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_sbc); break;
        case 0x03: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_slo); break;
        case 0x43: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_sre); break;
        case 0x81: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_sta); break;
        case 0x71: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_adc); break;
        case 0x31: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_and); break;
        case 0xD1: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_cmp); break;
        case 0xD3: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_dcp); break;
        case 0x51: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_eor); break;
        case 0xF3: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_isc); break;
        case 0xB3: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_lax); break;
        case 0xB1: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_lda); break;
        case 0x11: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_ora); break;
        case 0x33: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_rla); break;
        case 0x73: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_rra); break;
        case 0xF1: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_sbc); break;
        case 0x93: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_sha); break;
        case 0x13: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_slo); break;
        case 0x53: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_sre); break;
        case 0x91: instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_sta); break;
        case 0x65: instr_exec(c, m, AM_ZERO_PAGE, &instr_adc); break;
        case 0x25: instr_exec(c, m, AM_ZERO_PAGE, &instr_and); break;
        case 0x06: instr_exec(c, m, AM_ZERO_PAGE, &instr_asl); break;
        case 0x24: instr_exec(c, m, AM_ZERO_PAGE, &instr_bit); break;
        case 0xC5: instr_exec(c, m, AM_ZERO_PAGE, &instr_cmp); break;
        case 0xE4: instr_exec(c, m, AM_ZERO_PAGE, &instr_cpx); break;
        case 0xC4: instr_exec(c, m, AM_ZERO_PAGE, &instr_cpy); break;
        case 0xC7: instr_exec(c, m, AM_ZERO_PAGE, &instr_dcp); break;
        case 0xC6: instr_exec(c, m, AM_ZERO_PAGE, &instr_dec); break;
        case 0x45: instr_exec(c, m, AM_ZERO_PAGE, &instr_eor); break;
        case 0xE6: instr_exec(c, m, AM_ZERO_PAGE, &instr_inc); break;
        case 0xE7: instr_exec(c, m, AM_ZERO_PAGE, &instr_isc); break;
        case 0xA7: instr_exec(c, m, AM_ZERO_PAGE, &instr_lax); break;
        case 0xA5: instr_exec(c, m, AM_ZERO_PAGE, &instr_lda); break;
        case 0xA6: instr_exec(c, m, AM_ZERO_PAGE, &instr_ldx); break;
        case 0xA4: instr_exec(c, m, AM_ZERO_PAGE, &instr_ldy); break;
        case 0x46: instr_exec(c, m, AM_ZERO_PAGE, &instr_lsr); break;
        case 0x04: instr_exec(c, m, AM_ZERO_PAGE, &instr_nop); break;
        case 0x44: instr_exec(c, m, AM_ZERO_PAGE, &instr_nop); break;
        case 0x64: instr_exec(c, m, AM_ZERO_PAGE, &instr_nop); break;
        case 0x05: instr_exec(c, m, AM_ZERO_PAGE, &instr_ora); break;
        case 0x27: instr_exec(c, m, AM_ZERO_PAGE, &instr_rla); break;
        case 0x26: instr_exec(c, m, AM_ZERO_PAGE, &instr_rol); break;
        case 0x66: instr_exec(c, m, AM_ZERO_PAGE, &instr_ror); break;
        case 0x67: instr_exec(c, m, AM_ZERO_PAGE, &instr_rra); break;
        case 0x87: instr_exec(c, m, AM_ZERO_PAGE, &instr_sax); break;
        case 0xE5: instr_exec(c, m, AM_ZERO_PAGE, &instr_sbc); break;
        case 0x07: instr_exec(c, m, AM_ZERO_PAGE, &instr_slo); break;
        case 0x47: instr_exec(c, m, AM_ZERO_PAGE, &instr_sre); break;
        case 0x85: instr_exec(c, m, AM_ZERO_PAGE, &instr_sta); break;
        case 0x86: instr_exec(c, m, AM_ZERO_PAGE, &instr_stx); break;
        case 0x84: instr_exec(c, m, AM_ZERO_PAGE, &instr_sty); break;
        case 0x75: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_adc); break;
        case 0x35: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_and); break;
        case 0x16: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_asl); break;
        case 0xD5: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_cmp); break;
        case 0xD7: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_dcp); break;
        case 0xD6: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_dec); break;
        case 0x55: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_eor); break;
        case 0xF6: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_inc); break;
        case 0xF7: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_isc); break;
        case 0xB5: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_lda); break;
        case 0xB4: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_ldy); break;
        case 0x56: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_lsr); break;
        case 0x14: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop); break;
        case 0x34: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop); break;
        case 0x54: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop); break;
        case 0x74: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop); break;
        case 0xD4: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop); break;
        case 0xF4: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop); break;
        case 0x15: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_ora); break;
        case 0x37: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_rla); break;
        case 0x36: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_rol); break;
        case 0x76: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_ror); break;
        case 0x77: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_rra); break;
        case 0xF5: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_sbc); break;
        case 0x17: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_slo); break;
        case 0x57: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_sre); break;
        case 0x95: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_sta); break;
        case 0x94: instr_exec(c, m, AM_ZERO_PAGE_X, &instr_sty); break;
        case 0xB7: instr_exec(c, m, AM_ZERO_PAGE_Y, &instr_lax); break;
        case 0xB6: instr_exec(c, m, AM_ZERO_PAGE_Y, &instr_ldx); break;
        case 0x97: instr_exec(c, m, AM_ZERO_PAGE_Y, &instr_sax); break;
        case 0x96: instr_exec(c, m, AM_ZERO_PAGE_Y, &instr_stx); break;
        case 0x90: instr_exec(c, m, AM_RELATIVE, &instr_bcc); break;
        case 0xB0: instr_exec(c, m, AM_RELATIVE, &instr_bcs); break;
        case 0xF0: instr_exec(c, m, AM_RELATIVE, &instr_beq); break;
        case 0x30: instr_exec(c, m, AM_RELATIVE, &instr_bmi); break;
        case 0xD0: instr_exec(c, m, AM_RELATIVE, &instr_bne); break;
        case 0x10: instr_exec(c, m, AM_RELATIVE, &instr_bpl); break;
        case 0x50: instr_exec(c, m, AM_RELATIVE, &instr_bvc); break;
        case 0x70: instr_exec(c, m, AM_RELATIVE, &instr_bvs); break;

        default:
            printf("Unknown opcode: 0x%x\n", opcode);
            exit(1);
    }
}

// Loads
void instr_load(cpu* c, mem* m, reg r){
    uint8_t operand = next_byte(c, m);

    set_reg(c, r, operand);
    set_flag(c, FLAG_Z, (operand == 0));
    set_flag(c, FLAG_N, get_bit(operand, 7));
}

void instr_lda(cpu* c, mem* m){ instr_load(c, m, REG_A); }
void instr_ldx(cpu* c, mem* m){ instr_load(c, m, REG_X); }
void instr_ldy(cpu* c, mem* m){ instr_load(c, m, REG_Y); }

// Stores
void instr_store(cpu* c, mem* m, reg r){
    uint16_t addr = get_addr(c, m);
    uint8_t byte = *get_reg(c, r);

    mem_set_byte(m, addr, byte);
}

void instr_sta(cpu* c, mem* m){ instr_store(c, m, REG_A); }
void instr_stx(cpu* c, mem* m){ instr_store(c, m, REG_X); }
void instr_sty(cpu* c, mem* m){ instr_store(c, m, REG_Y); }

// Transfers
void instr_transfer(cpu* c, mem* m, reg dst, reg src){
    uint8_t byte = *get_reg(c, src); 
    
    set_reg(c, dst, byte);
    set_flag(c, FLAG_N, get_bit(byte, 7));
    set_flag(c, FLAG_Z,(byte == 0));
}

void instr_tax(cpu* c, mem* m){ instr_transfer(c, m, REG_X, REG_A); }
void instr_tay(cpu* c, mem* m){ instr_transfer(c, m, REG_Y, REG_A); }
void instr_tsx(cpu* c, mem* m){ instr_transfer(c, m, REG_X, REG_S); }
void instr_txa(cpu* c, mem* m){ instr_transfer(c, m, REG_A, REG_X); }
void instr_txs(cpu* c, mem* m){ instr_transfer(c, m, REG_S, REG_X); }
void instr_tya(cpu* c, mem* m){ instr_transfer(c, m, REG_A, REG_Y); }

// Stack Operations
void push_reg_stack(cpu* c, mem* m, reg r){
    uint8_t sp = *get_reg(c, REG_S);
    uint8_t src = *get_reg(c, r);
    
    // P register always gets pushed with bit 4 and 5 set
    if(r == REG_P){
        set_bit(&src, 4, 1);
        set_bit(&src, 5, 1);
    }

    uint16_t addr = merge_bytes(0x01,sp); 
    
    mem_set_byte(m, addr, src);
    set_reg(c, REG_S, sp - 1);
}

void push_byte_stack(cpu* c, mem* m, uint8_t b){
    uint8_t sp = *get_reg(c, REG_S);

    uint16_t addr = merge_bytes(0x01,sp); 
    mem_set_byte(m, addr, b);
    set_reg(c, REG_S, sp - 1);
}

void pull_reg_stack(cpu* c, mem* m, reg r){
    uint8_t sp = *get_reg(c, REG_S);

    uint16_t addr = merge_bytes(0x01, sp + 1); 
    uint8_t src = mem_get_byte(m, addr);

    set_reg(c, r, src);
    set_reg(c, REG_S, sp + 1);
}

uint8_t pull_byte_stack(cpu* c, mem* m){
    uint8_t sp = *get_reg(c, REG_S);
    uint16_t addr = merge_bytes(0x01, sp + 1); 
    uint8_t byte = mem_get_byte(m, addr);

    set_reg(c, REG_S, sp + 1);
    return byte;
}

void instr_pha(cpu* c, mem* m){ push_reg_stack(c, m, REG_A); }
void instr_pla(cpu* c, mem* m){
    pull_reg_stack(c, m, REG_A);

    uint8_t a = *get_reg(c, REG_A);
    
    set_flag(c, FLAG_N, get_bit(a, 7));
    set_flag(c, FLAG_Z, (a == 0));
}

void instr_php(cpu* c, mem* m){ push_reg_stack(c, m, REG_P); }
void instr_plp(cpu* c, mem* m){ pull_reg_stack(c, m, REG_P); }

void instr_asl(cpu* c, mem* m){
    uint8_t operand;
    uint8_t result;

    addr_mode am = get_mode(c);
    uint16_t addr = get_addr(c, m);
    
    if(am == AM_ACCUMULATOR){ 
        operand = *get_reg(c, REG_A); 
    }else{
        operand = mem_get_byte(m, addr);
    }
    
    uint8_t o_carry = get_bit(operand, 7);
    result = operand << 1;
    set_bit(&result, 0, 0);
    
    set_flag(c, FLAG_C, o_carry);
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_Z, result == 0);

    if(am == AM_ACCUMULATOR){
        set_reg(c, REG_A, result);
    }else{
        mem_set_byte(m, addr, result);
    }
}

void instr_lsr(cpu* c, mem* m){
    uint8_t operand;
    uint8_t result;

    addr_mode am = get_mode(c);
    
    if(am == AM_ACCUMULATOR){ 
        operand = *get_reg(c, REG_A); 
    }else{
        operand = next_byte(c, m);
    }
    
    result = operand >> 1;
    
    set_flag(c, FLAG_C, get_bit(operand, 1));
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_Z, result == 0);

    if(am == AM_ACCUMULATOR){
        set_reg(c, REG_A, result);
    }else{
        mem_set_byte(m, get_addr(c, m), result);
    }
}

void instr_rol(cpu* c, mem* m){
    addr_mode am = get_mode(c);
    uint16_t addr = get_addr(c, m);

    uint8_t operand = am == AM_ACCUMULATOR ? *get_reg(c, REG_A) : next_byte(c, m);
    uint8_t result = operand << 1;

    uint8_t carry = get_flag(c, FLAG_C);
    set_bit(&result, 0, carry);

    am == AM_ACCUMULATOR ? set_reg(c, REG_A, result) : mem_set_byte(m, addr, result); 

    set_flag(c, FLAG_C,get_bit(result, 7));
    set_flag(c, FLAG_N,get_bit(operand, 6));
    set_flag(c, FLAG_Z, result == 0);
}
void instr_ror(cpu* c, mem* m){
    addr_mode am = get_mode(c);
    uint16_t addr = get_addr(c, m);

    uint8_t operand = am == AM_ACCUMULATOR ? *get_reg(c, REG_A) : next_byte(c, m);
    uint8_t result = operand >> 1;
    uint8_t carry = get_flag(c, FLAG_C);

    set_bit(&result, 7, carry);

    am == AM_ACCUMULATOR ? set_reg(c, REG_A, result) : mem_set_byte(m, addr, result); 
    
    set_flag(c, FLAG_C, get_bit(operand, 0));
    set_flag(c, FLAG_N, get_bit(operand, 7));
    set_flag(c, FLAG_Z, (result == 0));
}

void instr_and(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte & acc;

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, (result == 0));
    set_flag(c, FLAG_N, get_bit(result, 7));
}
void instr_bit(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = (byte & acc);

    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(byte, 7));
    set_flag(c, FLAG_V, get_bit(byte, 6));
}
void instr_eor(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = (byte ^ acc);

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));
}
void instr_ora(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = (byte | acc);

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));
}

uint8_t add(cpu* c, uint8_t x, uint8_t y){
    uint8_t i_carry = get_flag(c, FLAG_C);
    uint8_t c1, c2, o_carry;
    uint8_t res;
   
    c1 = __builtin_add_overflow(x, y, &res);
    c2 = __builtin_add_overflow(res, i_carry, &res);
    o_carry = c1 | c2;

    uint8_t x_sign = get_bit(x, 7);
    uint8_t res_sign = get_bit(res,7);
    
    set_flag(c, FLAG_C, o_carry); 
    set_flag(c, FLAG_Z, (res == 0));
    set_flag(c, FLAG_N, get_bit(res, 7));
    set_flag(c, FLAG_V, x_sign != res_sign);

    return res;
}

void instr_adc(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t res = add(c, byte, acc);

    set_reg(c, REG_A, res);
}
void instr_cmp(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = acc - byte;

    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_C, byte <= acc);
}
void instr_cpx(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t reg = *get_reg(c, REG_X);
    uint8_t result = reg - byte;

    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_C, byte <= reg);
}
void instr_cpy(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t reg = *get_reg(c, REG_Y);
    uint8_t result = reg - byte;

    set_flag(c, FLAG_Z, result == 0);
    set_flag(c, FLAG_N, get_bit(result, 7));
    set_flag(c, FLAG_C, byte <= reg);
}

uint8_t sub(cpu* c, uint8_t x, uint8_t y){
    uint8_t i_carry = !get_flag(c, FLAG_C);
    uint8_t c1, c2, o_carry;
    uint8_t res;
   
    c1 = __builtin_sub_overflow(x, y, &res);
    c2 = __builtin_sub_overflow(res, i_carry, &res);
    o_carry = c1 | c2;

    uint8_t x_sign = get_bit(x, 7);
    uint8_t res_sign = get_bit(res,7);
    
    set_flag(c, FLAG_C, o_carry); 
    set_flag(c, FLAG_Z, (res == 0));
    set_flag(c, FLAG_N, get_bit(res, 7));
    set_flag(c, FLAG_V, x_sign != res_sign);

    return res;
}

void instr_sbc(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t res = sub(c, byte, acc);

    set_reg(c, REG_A, res);
}

void instr_dec_reg(cpu* c, reg r){
    uint8_t n = *get_reg(c, r);
    n = n - 1;
    set_reg(c, r, n);

    set_flag(c, FLAG_N, get_bit(n, 7));
    set_flag(c, FLAG_Z, n == 0);
}
void instr_dec(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    uint8_t n = next_byte(c, m);

    n = n - 1;

    mem_set_byte(m, addr, n);
    
    set_flag(c, FLAG_N, get_bit(n, 7));
    set_flag(c, FLAG_Z, n == 0);
}

void instr_dex(cpu* c, mem* m){ instr_dec_reg(c, REG_X); }
void instr_dey(cpu* c, mem* m){ instr_dec_reg(c, REG_Y); }

void instr_inc_reg(cpu* c, reg r){
    uint8_t n = *get_reg(c, r);
    n = n + 1;
    set_reg(c, r, n);

    set_flag(c, FLAG_N, get_bit(n, 7));
    set_flag(c, FLAG_Z, n == 0);
}

void instr_inc(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    uint8_t n = next_byte(c, m);

    n = n + 1;

    mem_set_byte(m, addr, n);
    
    set_flag(c, FLAG_N, get_bit(n, 7));
    set_flag(c, FLAG_Z, n == 0);
}

void instr_inx(cpu* c, mem* m){ instr_inc_reg(c, REG_X); }
void instr_iny(cpu* c, mem* m){ instr_inc_reg(c, REG_Y); }

void instr_brk(cpu* c, mem* m){
    uint16_t pc = get_pc(c);

    bytes addr_bytes = split_addr(pc);

    push_byte_stack(c, m, addr_bytes.hi);
    push_byte_stack(c, m, addr_bytes.lo);
    push_reg_stack(c, m, REG_P);

    uint8_t hi = mem_get_byte(m, 0xFFFE);
    uint8_t lo = mem_get_byte(m, 0xFFFF);
    uint16_t new_pc = merge_bytes(hi, lo);

    set_pc(c, new_pc+1);
    set_flag(c, FLAG_B, 1);
}

void instr_jmp(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    set_pc(c, addr);
}
void instr_jsr(cpu* c, mem* m){
    bytes addr;
    addr.lo = next_byte(c, m);
    addr.hi = next_byte(c, m);

    bytes pc = split_addr(get_pc(c));
    push_byte_stack(c, m, pc.hi);
    push_byte_stack(c, m, pc.lo);

    set_pc(c, merge_bytes(addr.hi, addr.lo));
}

void instr_rti(cpu* c, mem* m){
    pull_reg_stack(c, m, REG_P);
    
    bytes pc;
    pc.lo = next_byte(c, m);
    pc.hi = next_byte(c, m);

    set_pc(c, merge_bytes(pc.hi, pc.lo));
}

void instr_rts(cpu* c, mem* m){
    bytes addr;

    addr.lo = pull_byte_stack(c, m);
    addr.hi = pull_byte_stack(c, m);

    uint16_t pc = merge_bytes(addr.hi, addr.lo);
    debug_out(LOG_FILE,"RTS -> %d\n", pc);
    set_pc(c, pc);
}

void instr_branch(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    set_pc(c, addr); 
}

void instr_bcc(cpu* c, mem* m){ if(!get_flag(c, FLAG_C)){ instr_branch(c, m); } }
void instr_bcs(cpu* c, mem* m){ if(get_flag(c, FLAG_C)){  instr_branch(c, m); } }
void instr_beq(cpu* c, mem* m){ if(get_flag(c, FLAG_Z)){  instr_branch(c, m); } }
void instr_bmi(cpu* c, mem* m){ if(get_flag(c, FLAG_N)){  instr_branch(c, m); } }
void instr_bne(cpu* c, mem* m){ if(!get_flag(c, FLAG_Z)){ instr_branch(c, m); } }
void instr_bpl(cpu* c, mem* m){ if(!get_flag(c, FLAG_N)){ instr_branch(c, m); } }
void instr_bvc(cpu* c, mem* m){ if(!get_flag(c, FLAG_V)){ instr_branch(c, m); } }
void instr_bvs(cpu* c, mem* m){ if(get_flag(c, FLAG_V)){  instr_branch(c, m); } }

void instr_clc(cpu* c, mem* m){ set_flag(c, FLAG_C, 0); }
void instr_cld(cpu* c, mem* m){ set_flag(c, FLAG_D, 0); }
void instr_cli(cpu* c, mem* m){ set_flag(c, FLAG_I, 0); }
void instr_clv(cpu* c, mem* m){ set_flag(c, FLAG_V, 0); }
void instr_sec(cpu* c, mem* m){ set_flag(c, FLAG_C, 1); }
void instr_sed(cpu* c, mem* m){ set_flag(c, FLAG_D, 1); }
void instr_sei(cpu* c, mem* m){ set_flag(c, FLAG_I, 1); }
void instr_nop(cpu* c, mem* m){ }

// Undocumented
void instr_jam(cpu* c, mem* m){ cpu_stop(c); };

void instr_anc(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte & acc;

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, (result == 0));
    uint8_t v_bit = get_bit(result, 7);
    set_flag(c, FLAG_N, v_bit);
    set_flag(c, FLAG_C, v_bit);
}

void instr_arr(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte & acc;
    
    uint8_t i_carry = get_flag(c, FLAG_C);
    //uint8_t o_carry = get_bit(result, 0);
    
    result = result >> 1;
    set_bit(&result, 7, i_carry);

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, (result == 0));
    
    // FIX DECIMAL MODE
    uint8_t v_bit = get_bit(result, 7);
    set_flag(c, FLAG_N, v_bit);
};

void instr_asr(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t acc = *get_reg(c, REG_A);
    uint8_t result = byte & acc;
    
    //uint8_t i_carry = get_flag(c, FLAG_C);
    uint8_t o_carry = get_bit(result, 0);
    
    result = result >> 1;
    set_bit(&result, 7, 0);

    set_reg(c, REG_A, result);
    set_flag(c, FLAG_Z, (result == 0));
    set_flag(c, FLAG_N, 0);
    set_flag(c, FLAG_C, o_carry);   
};

void instr_lax(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);

    set_reg(c, REG_A, byte);
    set_reg(c, REG_X, byte);

    set_flag(c, FLAG_Z, byte == 0);
    set_flag(c, FLAG_N, get_bit(byte, 7));
};

void instr_sbx(cpu* c, mem* m){
    uint8_t byte = next_byte(c, m);
    uint8_t a = *get_reg(c, REG_A);
    uint8_t x = *get_reg(c, REG_X);

    uint8_t res = sub(c, byte, (a & x));

    set_reg(c, REG_X, res);
};

void instr_shs(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    
    uint8_t a = *get_reg(c, REG_A);
    uint8_t x = *get_reg(c, REG_X);
    uint8_t res = (a & x);

    set_reg(c, REG_S, res);
    bytes s = split_addr(addr);

    res = (res & s.hi) + 1;
    mem_set_byte(m, addr, res);
};

void instr_sax(cpu* c, mem* m){
    uint16_t addr = get_addr(c, m);
    
    uint8_t a = *get_reg(c, REG_A);
    uint8_t x = *get_reg(c, REG_X);
    uint8_t res = (a & x);

    mem_set_byte(m, addr, res);
};

void instr_sha(cpu* c, mem* m){};

void instr_shx(cpu* c, mem* m){};
void instr_shy(cpu* c, mem* m){};
void instr_las(cpu* c, mem* m){};

void instr_xaa(cpu* c, mem* m){};

void instr_dcp(cpu* c, mem* m){};

void instr_isc(cpu* c, mem* m){};
void instr_rla(cpu* c, mem* m){};
void instr_rra(cpu* c, mem* m){};
void instr_slo(cpu* c, mem* m){};
void instr_sre(cpu* c, mem* m){};

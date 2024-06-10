#include <stdio.h>
#include <stdlib.h>

#include "instr.h"
#include "instr_arith.h"
#include "instr_branch.h"
#include "instr_ctrl.h"
#include "instr_flags.h"
#include "instr_inc.h"
#include "instr_load.h"
#include "instr_logic.h"
#include "instr_shift.h"
#include "instr_stack.h"
#include "instr_trans.h"

#include "cpu.h"

void instr_exec(cpu *c, mem *m, addr_mode am, void (*instr_ptr)(cpu *, mem *)) {
  set_mode(c, am);
  (*instr_ptr)(c, m);
}

void instr_parse(cpu *c, mem *m, uint8_t opcode) {
  switch (opcode) {
  case 0x00:
    instr_exec(c, m, AM_IMPLIED, &instr_brk);
    break;
  case 0x18:
    instr_exec(c, m, AM_IMPLIED, &instr_clc);
    break;
  case 0xD8:
    instr_exec(c, m, AM_IMPLIED, &instr_cld);
    break;
  case 0x58:
    instr_exec(c, m, AM_IMPLIED, &instr_cli);
    break;
  case 0xB8:
    instr_exec(c, m, AM_IMPLIED, &instr_clv);
    break;
  case 0xCA:
    instr_exec(c, m, AM_IMPLIED, &instr_dex);
    break;
  case 0x88:
    instr_exec(c, m, AM_IMPLIED, &instr_dey);
    break;
  case 0xE8:
    instr_exec(c, m, AM_IMPLIED, &instr_inx);
    break;
  case 0xC8:
    instr_exec(c, m, AM_IMPLIED, &instr_iny);
    break;
  case 0x02:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x12:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x22:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x32:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x42:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x52:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x62:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x72:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x92:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0xB2:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0xD2:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0xF2:
    instr_exec(c, m, AM_IMPLIED, &instr_jam);
    break;
  case 0x1A:
    instr_exec(c, m, AM_IMPLIED, &instr_nop);
    break;
  case 0x3A:
    instr_exec(c, m, AM_IMPLIED, &instr_nop);
    break;
  case 0x5A:
    instr_exec(c, m, AM_IMPLIED, &instr_nop);
    break;
  case 0x7A:
    instr_exec(c, m, AM_IMPLIED, &instr_nop);
    break;
  case 0xDA:
    instr_exec(c, m, AM_IMPLIED, &instr_nop);
    break;
  case 0xEA:
    instr_exec(c, m, AM_IMPLIED, &instr_nop);
    break;
  case 0xFA:
    instr_exec(c, m, AM_IMPLIED, &instr_nop);
    break;
  case 0x48:
    instr_exec(c, m, AM_IMPLIED, &instr_pha);
    break;
  case 0x08:
    instr_exec(c, m, AM_IMPLIED, &instr_php);
    break;
  case 0x68:
    instr_exec(c, m, AM_IMPLIED, &instr_pla);
    break;
  case 0x28:
    instr_exec(c, m, AM_IMPLIED, &instr_plp);
    break;
  case 0x40:
    instr_exec(c, m, AM_IMPLIED, &instr_rti);
    break;
  case 0x60:
    instr_exec(c, m, AM_IMPLIED, &instr_rts);
    break;
  case 0x38:
    instr_exec(c, m, AM_IMPLIED, &instr_sec);
    break;
  case 0xF8:
    instr_exec(c, m, AM_IMPLIED, &instr_sed);
    break;
  case 0x78:
    instr_exec(c, m, AM_IMPLIED, &instr_sei);
    break;
  case 0xAA:
    instr_exec(c, m, AM_IMPLIED, &instr_tax);
    break;
  case 0xA8:
    instr_exec(c, m, AM_IMPLIED, &instr_tay);
    break;
  case 0xBA:
    instr_exec(c, m, AM_IMPLIED, &instr_tsx);
    break;
  case 0x8A:
    instr_exec(c, m, AM_IMPLIED, &instr_txa);
    break;
  case 0x9A:
    instr_exec(c, m, AM_IMPLIED, &instr_txs);
    break;
  case 0x98:
    instr_exec(c, m, AM_IMPLIED, &instr_tya);
    break;
  case 0x0A:
    instr_exec(c, m, AM_ACCUMULATOR, &instr_asl);
    break;
  case 0x4A:
    instr_exec(c, m, AM_ACCUMULATOR, &instr_lsr);
    break;
  case 0x2A:
    instr_exec(c, m, AM_ACCUMULATOR, &instr_rol);
    break;
  case 0x6A:
    instr_exec(c, m, AM_ACCUMULATOR, &instr_ror);
    break;
  case 0x69:
    instr_exec(c, m, AM_IMMEDIATE, &instr_adc);
    break;
  case 0x0B:
    instr_exec(c, m, AM_IMMEDIATE, &instr_anc);
    break;
  case 0x2B:
    instr_exec(c, m, AM_IMMEDIATE, &instr_anc);
    break;
  case 0x29:
    instr_exec(c, m, AM_IMMEDIATE, &instr_and);
    break;
  case 0x6B:
    instr_exec(c, m, AM_IMMEDIATE, &instr_arr);
    break;
  case 0x4B:
    instr_exec(c, m, AM_IMMEDIATE, &instr_asr);
    break;
  case 0xC9:
    instr_exec(c, m, AM_IMMEDIATE, &instr_cmp);
    break;
  case 0xE0:
    instr_exec(c, m, AM_IMMEDIATE, &instr_cpx);
    break;
  case 0xC0:
    instr_exec(c, m, AM_IMMEDIATE, &instr_cpy);
    break;
  case 0x49:
    instr_exec(c, m, AM_IMMEDIATE, &instr_eor);
    break;
  case 0xAB:
    instr_exec(c, m, AM_IMMEDIATE, &instr_lax);
    break;
  case 0xA9:
    instr_exec(c, m, AM_IMMEDIATE, &instr_lda);
    break;
  case 0xA2:
    instr_exec(c, m, AM_IMMEDIATE, &instr_ldx);
    break;
  case 0xA0:
    instr_exec(c, m, AM_IMMEDIATE, &instr_ldy);
    break;
  case 0x80:
    instr_exec(c, m, AM_IMMEDIATE, &instr_nop);
    break;
  case 0x82:
    instr_exec(c, m, AM_IMMEDIATE, &instr_nop);
    break;
  case 0x89:
    instr_exec(c, m, AM_IMMEDIATE, &instr_nop);
    break;
  case 0xC2:
    instr_exec(c, m, AM_IMMEDIATE, &instr_nop);
    break;
  case 0xE2:
    instr_exec(c, m, AM_IMMEDIATE, &instr_nop);
    break;
  case 0x09:
    instr_exec(c, m, AM_IMMEDIATE, &instr_ora);
    break;
  case 0xE9:
    instr_exec(c, m, AM_IMMEDIATE, &instr_sbc);
    break;
  case 0xEB:
    instr_exec(c, m, AM_IMMEDIATE, &instr_sbc);
    break;
  case 0xCB:
    instr_exec(c, m, AM_IMMEDIATE, &instr_sbx);
    break;
  case 0x8B:
    instr_exec(c, m, AM_IMMEDIATE, &instr_xaa);
    break;
  case 0x6D:
    instr_exec(c, m, AM_ABSOLUTE, &instr_adc);
    break;
  case 0x2D:
    instr_exec(c, m, AM_ABSOLUTE, &instr_and);
    break;
  case 0x0E:
    instr_exec(c, m, AM_ABSOLUTE, &instr_asl);
    break;
  case 0x2C:
    instr_exec(c, m, AM_ABSOLUTE, &instr_bit);
    break;
  case 0xCD:
    instr_exec(c, m, AM_ABSOLUTE, &instr_cmp);
    break;
  case 0xEC:
    instr_exec(c, m, AM_ABSOLUTE, &instr_cpx);
    break;
  case 0xCC:
    instr_exec(c, m, AM_ABSOLUTE, &instr_cpy);
    break;
  case 0xCF:
    instr_exec(c, m, AM_ABSOLUTE, &instr_dcp);
    break;
  case 0xCE:
    instr_exec(c, m, AM_ABSOLUTE, &instr_dec);
    break;
  case 0x4D:
    instr_exec(c, m, AM_ABSOLUTE, &instr_eor);
    break;
  case 0xEE:
    instr_exec(c, m, AM_ABSOLUTE, &instr_inc);
    break;
  case 0xEF:
    instr_exec(c, m, AM_ABSOLUTE, &instr_isc);
    break;
  case 0x4C:
    instr_exec(c, m, AM_ABSOLUTE, &instr_jmp);
    break;
  case 0x20:
    instr_exec(c, m, AM_ABSOLUTE, &instr_jsr);
    break;
  case 0xAF:
    instr_exec(c, m, AM_ABSOLUTE, &instr_lax);
    break;
  case 0xAD:
    instr_exec(c, m, AM_ABSOLUTE, &instr_lda);
    break;
  case 0xAE:
    instr_exec(c, m, AM_ABSOLUTE, &instr_ldx);
    break;
  case 0xAC:
    instr_exec(c, m, AM_ABSOLUTE, &instr_ldy);
    break;
  case 0x4E:
    instr_exec(c, m, AM_ABSOLUTE, &instr_lsr);
    break;
  case 0x0C:
    instr_exec(c, m, AM_ABSOLUTE, &instr_nop);
    break;
  case 0x0D:
    instr_exec(c, m, AM_ABSOLUTE, &instr_ora);
    break;
  case 0x2F:
    instr_exec(c, m, AM_ABSOLUTE, &instr_rla);
    break;
  case 0x2E:
    instr_exec(c, m, AM_ABSOLUTE, &instr_rol);
    break;
  case 0x6E:
    instr_exec(c, m, AM_ABSOLUTE, &instr_ror);
    break;
  case 0x6F:
    instr_exec(c, m, AM_ABSOLUTE, &instr_rra);
    break;
  case 0x8F:
    instr_exec(c, m, AM_ABSOLUTE, &instr_sax);
    break;
  case 0xED:
    instr_exec(c, m, AM_ABSOLUTE, &instr_sbc);
    break;
  case 0x0F:
    instr_exec(c, m, AM_ABSOLUTE, &instr_slo);
    break;
  case 0x4F:
    instr_exec(c, m, AM_ABSOLUTE, &instr_sre);
    break;
  case 0x8D:
    instr_exec(c, m, AM_ABSOLUTE, &instr_sta);
    break;
  case 0x8E:
    instr_exec(c, m, AM_ABSOLUTE, &instr_stx);
    break;
  case 0x8C:
    instr_exec(c, m, AM_ABSOLUTE, &instr_sty);
    break;
  case 0x7D:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_adc);
    break;
  case 0x3D:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_and);
    break;
  case 0x1E:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_asl);
    break;
  case 0xDD:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_cmp);
    break;
  case 0xDF:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_dcp);
    break;
  case 0xDE:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_dec);
    break;
  case 0x5D:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_eor);
    break;
  case 0xFE:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_inc);
    break;
  case 0xFF:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_isc);
    break;
  case 0xBD:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_lda);
    break;
  case 0xBC:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_ldy);
    break;
  case 0x5E:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_lsr);
    break;
  case 0x1C:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop);
    break;
  case 0x3C:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop);
    break;
  case 0x5C:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop);
    break;
  case 0x7C:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop);
    break;
  case 0xDC:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop);
    break;
  case 0xFC:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_nop);
    break;
  case 0x1D:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_ora);
    break;
  case 0x3F:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_rla);
    break;
  case 0x3E:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_rol);
    break;
  case 0x7E:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_ror);
    break;
  case 0x7F:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_rra);
    break;
  case 0xFD:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_sbc);
    break;
  case 0x9C:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_shy);
    break;
  case 0x1F:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_slo);
    break;
  case 0x5F:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_sre);
    break;
  case 0x9D:
    instr_exec(c, m, AM_ABSOLUTE_X, &instr_sta);
    break;
  case 0x79:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_adc);
    break;
  case 0x39:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_and);
    break;
  case 0xD9:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_cmp);
    break;
  case 0xDB:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_dcp);
    break;
  case 0x59:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_eor);
    break;
  case 0xFB:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_isc);
    break;
  case 0xBB:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_las);
    break;
  case 0xBF:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_lax);
    break;
  case 0xB9:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_lda);
    break;
  case 0xBE:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_ldx);
    break;
  case 0x19:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_ora);
    break;
  case 0x3B:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_rla);
    break;
  case 0x7B:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_rra);
    break;
  case 0xF9:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_sbc);
    break;
  case 0x9F:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_sha);
    break;
  case 0x9B:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_shs);
    break;
  case 0x9E:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_shx);
    break;
  case 0x1B:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_slo);
    break;
  case 0x5B:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_sre);
    break;
  case 0x99:
    instr_exec(c, m, AM_ABSOLUTE_Y, &instr_sta);
    break;
  case 0x6C:
    instr_exec(c, m, AM_ABSOLUTE_INDIRECT, &instr_jmp);
    break;
  case 0x61:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_adc);
    break;
  case 0x21:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_and);
    break;
  case 0xC1:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_cmp);
    break;
  case 0xC3:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_dcp);
    break;
  case 0x41:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_eor);
    break;
  case 0xE3:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_isc);
    break;
  case 0xA3:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_lax);
    break;
  case 0xA1:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_lda);
    break;
  case 0x01:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_ora);
    break;
  case 0x23:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_rla);
    break;
  case 0x63:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_rra);
    break;
  case 0x83:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_sax);
    break;
  case 0xE1:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_sbc);
    break;
  case 0x03:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_slo);
    break;
  case 0x43:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_sre);
    break;
  case 0x81:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_X, &instr_sta);
    break;
  case 0x71:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_adc);
    break;
  case 0x31:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_and);
    break;
  case 0xD1:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_cmp);
    break;
  case 0xD3:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_dcp);
    break;
  case 0x51:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_eor);
    break;
  case 0xF3:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_isc);
    break;
  case 0xB3:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_lax);
    break;
  case 0xB1:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_lda);
    break;
  case 0x11:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_ora);
    break;
  case 0x33:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_rla);
    break;
  case 0x73:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_rra);
    break;
  case 0xF1:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_sbc);
    break;
  case 0x93:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_sha);
    break;
  case 0x13:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_slo);
    break;
  case 0x53:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_sre);
    break;
  case 0x91:
    instr_exec(c, m, AM_ZERO_PAGE_INDIRECT_Y, &instr_sta);
    break;
  case 0x65:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_adc);
    break;
  case 0x25:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_and);
    break;
  case 0x06:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_asl);
    break;
  case 0x24:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_bit);
    break;
  case 0xC5:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_cmp);
    break;
  case 0xE4:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_cpx);
    break;
  case 0xC4:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_cpy);
    break;
  case 0xC7:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_dcp);
    break;
  case 0xC6:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_dec);
    break;
  case 0x45:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_eor);
    break;
  case 0xE6:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_inc);
    break;
  case 0xE7:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_isc);
    break;
  case 0xA7:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_lax);
    break;
  case 0xA5:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_lda);
    break;
  case 0xA6:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_ldx);
    break;
  case 0xA4:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_ldy);
    break;
  case 0x46:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_lsr);
    break;
  case 0x04:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_nop);
    break;
  case 0x44:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_nop);
    break;
  case 0x64:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_nop);
    break;
  case 0x05:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_ora);
    break;
  case 0x27:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_rla);
    break;
  case 0x26:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_rol);
    break;
  case 0x66:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_ror);
    break;
  case 0x67:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_rra);
    break;
  case 0x87:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_sax);
    break;
  case 0xE5:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_sbc);
    break;
  case 0x07:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_slo);
    break;
  case 0x47:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_sre);
    break;
  case 0x85:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_sta);
    break;
  case 0x86:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_stx);
    break;
  case 0x84:
    instr_exec(c, m, AM_ZERO_PAGE, &instr_sty);
    break;
  case 0x75:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_adc);
    break;
  case 0x35:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_and);
    break;
  case 0x16:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_asl);
    break;
  case 0xD5:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_cmp);
    break;
  case 0xD7:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_dcp);
    break;
  case 0xD6:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_dec);
    break;
  case 0x55:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_eor);
    break;
  case 0xF6:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_inc);
    break;
  case 0xF7:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_isc);
    break;
  case 0xB5:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_lda);
    break;
  case 0xB4:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_ldy);
    break;
  case 0x56:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_lsr);
    break;
  case 0x14:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop);
    break;
  case 0x34:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop);
    break;
  case 0x54:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop);
    break;
  case 0x74:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop);
    break;
  case 0xD4:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop);
    break;
  case 0xF4:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_nop);
    break;
  case 0x15:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_ora);
    break;
  case 0x37:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_rla);
    break;
  case 0x36:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_rol);
    break;
  case 0x76:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_ror);
    break;
  case 0x77:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_rra);
    break;
  case 0xF5:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_sbc);
    break;
  case 0x17:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_slo);
    break;
  case 0x57:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_sre);
    break;
  case 0x95:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_sta);
    break;
  case 0x94:
    instr_exec(c, m, AM_ZERO_PAGE_X, &instr_sty);
    break;
  case 0xB7:
    instr_exec(c, m, AM_ZERO_PAGE_Y, &instr_lax);
    break;
  case 0xB6:
    instr_exec(c, m, AM_ZERO_PAGE_Y, &instr_ldx);
    break;
  case 0x97:
    instr_exec(c, m, AM_ZERO_PAGE_Y, &instr_sax);
    break;
  case 0x96:
    instr_exec(c, m, AM_ZERO_PAGE_Y, &instr_stx);
    break;
  case 0x90:
    instr_exec(c, m, AM_RELATIVE, &instr_bcc);
    break;
  case 0xB0:
    instr_exec(c, m, AM_RELATIVE, &instr_bcs);
    break;
  case 0xF0:
    instr_exec(c, m, AM_RELATIVE, &instr_beq);
    break;
  case 0x30:
    instr_exec(c, m, AM_RELATIVE, &instr_bmi);
    break;
  case 0xD0:
    instr_exec(c, m, AM_RELATIVE, &instr_bne);
    break;
  case 0x10:
    instr_exec(c, m, AM_RELATIVE, &instr_bpl);
    break;
  case 0x50:
    instr_exec(c, m, AM_RELATIVE, &instr_bvc);
    break;
  case 0x70:
    instr_exec(c, m, AM_RELATIVE, &instr_bvs);
    break;

  default:
    printf("Unknown opcode: 0x%x\n", opcode);
    exit(1);
  }
}

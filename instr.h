#ifndef INSTR_H
#define INSTR_H

#include "types.h"
void instr_exec(cpu* c, mem* m, addr_mode am, void (*instr_ptr)(cpu*, mem*));
void instr_parse(cpu* c, mem* m, uint8_t opcode);

void instr_lda(cpu* c, mem* m);
void instr_ldx(cpu* c, mem* m);
void instr_ldy(cpu* c, mem* m);
void instr_sta(cpu* c, mem* m);
void instr_stx(cpu* c, mem* m);
void instr_sty(cpu* c, mem* m);
void instr_tax(cpu* c, mem* m);
void instr_tay(cpu* c, mem* m);
void instr_tsx(cpu* c, mem* m);
void instr_txa(cpu* c, mem* m);
void instr_txs(cpu* c, mem* m);
void instr_tya(cpu* c, mem* m);
void instr_pha(cpu* c, mem* m);
void instr_pla(cpu* c, mem* m);
void instr_php(cpu* c, mem* m);
void instr_plp(cpu* c, mem* m);
void instr_asl(cpu* c, mem* m);
void instr_lsr(cpu* c, mem* m);
void instr_rol(cpu* c, mem* m);
void instr_ror(cpu* c, mem* m);
void instr_and(cpu* c, mem* m);
void instr_bit(cpu* c, mem* m);
void instr_eor(cpu* c, mem* m);
void instr_ora(cpu* c, mem* m);
void instr_adc(cpu* c, mem* m);
void instr_cmp(cpu* c, mem* m);
void instr_cpx(cpu* c, mem* m);
void instr_cpy(cpu* c, mem* m);
void instr_sbc(cpu* c, mem* m);
void instr_dec(cpu* c, mem* m);
void instr_dex(cpu* c, mem* m);
void instr_dey(cpu* c, mem* m);
void instr_inc(cpu* c, mem* m);
void instr_inx(cpu* c, mem* m);
void instr_iny(cpu* c, mem* m);
void instr_brk(cpu* c, mem* m);
void instr_jmp(cpu* c, mem* m);
void instr_jsr(cpu* c, mem* m);
void instr_rti(cpu* c, mem* m);
void instr_rts(cpu* c, mem* m);
void instr_bcc(cpu* c, mem* m);
void instr_bcs(cpu* c, mem* m);
void instr_beq(cpu* c, mem* m);
void instr_bmi(cpu* c, mem* m);
void instr_bne(cpu* c, mem* m);
void instr_bpl(cpu* c, mem* m);
void instr_bvc(cpu* c, mem* m);
void instr_bvs(cpu* c, mem* m);
void instr_clc(cpu* c, mem* m);
void instr_cld(cpu* c, mem* m);
void instr_cli(cpu* c, mem* m);
void instr_clv(cpu* c, mem* m);
void instr_sec(cpu* c, mem* m);
void instr_sed(cpu* c, mem* m);
void instr_sei(cpu* c, mem* m);
void instr_nop(cpu* c, mem* m);

// Undocumented
void instr_jam(cpu* c, mem* m);
void instr_anc(cpu* c, mem* m);
void instr_arr(cpu* c, mem* m);
void instr_asr(cpu* c, mem* m);
void instr_lax(cpu* c, mem* m);
void instr_sbx(cpu* c, mem* m);
void instr_xaa(cpu* c, mem* m);
void instr_dcp(cpu* c, mem* m);
void instr_isc(cpu* c, mem* m);
void instr_rla(cpu* c, mem* m);
void instr_rra(cpu* c, mem* m);
void instr_sax(cpu* c, mem* m);
void instr_slo(cpu* c, mem* m);
void instr_sre(cpu* c, mem* m);
void instr_shy(cpu* c, mem* m);
void instr_las(cpu* c, mem* m);
void instr_sha(cpu* c, mem* m);
void instr_shs(cpu* c, mem* m);
void instr_shx(cpu* c, mem* m);

#endif


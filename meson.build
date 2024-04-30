project('sfotemu', 'c')

add_global_arguments(language : 'c')

sources = files(
  'src/emu.c',
  'src/cpu.c',
  'src/addr.c', 
  'src/mem.c',
  'src/utils.c',
  'src/instr.c',
  'src/instr_arith.c',
  'src/instr_branch.c',
  'src/instr.c',
  'src/instr_ctrl.c',
  'src/instr_flags.c',
  'src/instr_inc.c',
  'src/instr_load.c',
  'src/instr_logic.c',
  'src/instr_shift.c',
  'src/instr_stack.c',
  'src/instr_trans.c'
)

incdir = include_directories('include')
executable('sfotemu', sources, include_directories: incdir)

project('sfotemu', 'c')

add_global_arguments(language : 'c')

incdir = include_directories('include')

src_lib = files(
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

src_tui = files('src/tui.c')

lib = library('6502cpu', src_lib, include_directories: incdir)

executable('tui', src_tui, include_directories: incdir, link_with : lib, link_args : ['-lncurses'])

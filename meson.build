project(
  'sfotemu',
  'c',
  default_options : [
    'c_std=c17',
    'werror=true',
    'warning_level=1',
    'c_args=-Wpedantic'
  ]
)


# 6502 CPU Lib
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
  'src/instr_trans.c',
  'src/bin.c',
)

lib = library('6502cpu', src_lib, include_directories: incdir)

# Dependencies
dep_lib = declare_dependency(link_with : lib, include_directories : incdir)
dep_jsonc = dependency('json-c')

# Single Step Tests
src_single_step_tests = files('tests/single-step-tests/test.c')
single_step_tests = executable('single-step-tests', src_single_step_tests, dependencies : [dep_jsonc, dep_lib])

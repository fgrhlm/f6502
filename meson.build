project('sfotemu', 'c')

add_global_arguments('-Werror', '-fsanitize=leak', language : 'c')

sources = files('emu.c','cpu.c','addr.c', 'instr.c','mem.c','utils.c')
executable('sfotemu', sources)

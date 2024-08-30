## f6502 
is an emulation of the MOS Technology 6502 microprocessor, a popular 8-bit processor used in many classic home computers like the Commodore 64 and Apple II. This project aims to provide a faithful and accurate emulation of the 6502 architecture for educational and research purposes.

### Features

- Supports all legal opcodes of the 6502 processor.
- Written in C for optimal performance and portability.
- Modular design allows for easy integration with other tools and libraries.
- Boilerplate for running the most popular tests (atm Tom Harte's single step tests and klaus2m5's functional tests)

### Status

This project is still under active development, but it already provides a solid foundation for emulating the 6502 processor.

### Building

This project uses the [Meson Build System](https://mesonbuild.com)

2. Clone the repository: `git clone https://github.com/fgrhlm/f6502.git`
3. Build the project: `meson setup build && meson compile`

### Contributing

This project is not accepting contributions at the moment.

# SingleStepTests (previously TomHartes ProcessorTests)

## Dependencies

[SingleStepTests/65x02](https://github.com/SingleStepTests/65x02)
[json-c/json-c](https://github.com/json-c/json-c)

## Setup
Clone the SingleStepTests/65x02 repo.
Install json-c either by cloning the repo and compiling or by using your package manager.

### Arch Linux
`pacman -S json-c`

## Running (bash)
The test program takes `n` number of test files as input.
To run the complete test suite: `single-step-tests $SingleSepTestsREPO/6502/v1/*`

```bash
script $YOUR_LOG_FILE
single-step-tests $TESTS/*
exit
```

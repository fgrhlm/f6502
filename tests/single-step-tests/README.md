# SingleStepTests (previously TomHartes ProcessorTests)

## Dependencies

[SingleStepTests/65x02](https://github.com/SingleStepTests/65x02)
[json-c/json-c](https://github.com/json-c/json-c)

## Running (bash)
`single-step-tests $TESTS_REPO/6502/v1/*`

For verbose output use flag `-v`

## Log
You can generate some pretty results using the included python script.

Run the test suite with script.

```bash
script $YOUR_LOG_FILE
single-step-tests $TESTS/*
exit
```

And display results
`python results.py $YOUR_LOG_FILE`

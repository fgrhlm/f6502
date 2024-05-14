import json
import sys
import os

from ops import ops

"""
    Format:
    - Test params separated by white space
    - Tests separated by new line
    
    Cycle types:
        0 - Read
        1 - Write

    Order:
    TEST_OPCODE
    TEST_INDEX
    .. START_REGS (PC, S, A, X, Y, P)
    START_RAM_LEN
    .. START_RAM (ADDR, VALUE)
    .. FINAL_REGS (PC, S, A, X, Y, P)
    FINAL_RAM_LEN
    .. FINAL_RAM (ADDR, VALUE)
    CYCLES_LEN
    .. TYPE | RAM ADDR | RAM VALUE
"""

if __name__=="__main__":
    dest_dir = "./ProcessorTestsConverted"
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    tests_dir = sys.argv[1]
    tests = os.listdir(tests_dir)

    total_len = len(tests)
    for ifn, fn in enumerate(tests):
        print(f"converting: {fn} ({ifn}/{total_len})")
        with open(os.path.join(tests_dir, fn), "r") as f:
            data = json.load(f)

        for test_index, test in enumerate(data):
            out = []

            op = fn.split('/')[-1].split('.')[0]
            
            out_dir = os.path.join(dest_dir, ops[op]["name"])
            if not os.path.exists(out_dir):
                os.makedirs(out_dir)

            out_file = os.path.join(out_dir, f"{op}.tst")

            out.append(str(int(op, 16)))
            out.append(str(test_index))

            for x in [test["initial"], test["final"]]:
                for k,v in x.items():
                    if k == "ram":
                        out.append(str(len(v)))
                        for n in v:
                            out.append(str(n[0]))
                            out.append(str(n[1]))
                    else:
                        out.append(str(v))
            
            out.append(str(len(test["cycles"])))
            for n in test["cycles"]:
                c_type = 0 if n[2] == "read" else 1
                out.append(str(c_type))
                out.append(str(n[0]))
                out.append(str(n[1]))

            with open(out_file, "a") as f:
                f.write(" ".join(out))
                f.write('\n')

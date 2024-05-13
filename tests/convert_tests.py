import json
import sys

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
    START_PC
    START_S
    START_A
    START_X
    START_Y
    START_P
    START_RAM_LEN
    ... RAM ADDR | RAM VALUE
    FINAL_PC
    FINAL_S
    FINAL_A
    FINAL_X
    FINAL_Y
    FINAL_P
    FINAL_RAM_LEN
    ... RAM ADDR | RAM VALUE
    CYCLES_LEN
    .. TYPE | RAM ADDR | RAM VALUE
"""

if __name__=="__main__":
    fn = sys.argv[1]
    print(f"Converting {fn}")

    with open(fn, "r") as f:
        data = json.load(f)

    print(f"\n\n{data[0]}\n\n")

    for test_index, test in enumerate(data[:1]):
        out = []

        op = fn.split('/')[-1].split('.')[0]

        out.append(op)
        out.append(test_index)

        for x in [test["initial"], test["final"]]:
            for k,v in x.items():
                if k == "ram":
                    out.append(len(v))
                    for n in v:
                        out.append(n[0])
                        out.append(n[1])
                else:
                    out.append(v)
        
        out.append(len(test["cycles"]))
        for n in test["cycles"]:
            c_type = 0 if n[2] == "read" else 1
            out.append(c_type)
            out.append(n[0])
            out.append(n[1])

    print(out)

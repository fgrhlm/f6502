import json
from enum import Enum
from utils import color, ops

if __name__=="__main__":
    with open("logs/eval.json", "r") as f:
        res = json.load(f)
    
    print()
    def istr(n): return f"{n:x}".upper()
    for n in range(16): print(color("bold", f"    x{istr(n)}"), end="")
    
    print()
    
    def gen_res_str(status, s):
        match status:
            case "FAIL": return color("r", s) 
            case "PASS": return color("g", s)
            case "ERROR": return color("y", s)
            case "NONE": return color("n", s)

    for n in range(16*16):
        index = f"{n:02x}"
        status = res[index]["status"] if index in res.keys() else "NONE"

        res_str = gen_res_str(status, f" {ops[index]['name']} ")
        
        if n % 16 == 0: 
            if n > 0: print("\n")
            print(color("bold", f"{istr(int((n/16)))}x"), end=" ")
            print(res_str, end=" ")
        else:
            print(res_str, end=" ")

    print("\n")

    categories = ["load", "trans", "stack", "shift", "logic", "arith", "inc", "ctrl", "branch", "flags"]
    for c in categories:
        print(color("bold", f"{c}"))
        row_c = 0
        for n in range(16*16):
            index = f"{n:02x}"
            status = res[index]["status"] if index in res.keys() else "NONE"
            res_str = gen_res_str(status, f" {index} {ops[index]['name']} ")

            if ops[index]["category"] == c:
                if status != "NONE":
                    print(res_str, end=" ")
                    row_c += 1

            if row_c == 16: 
                print("")
                row_c = 0
        print("\n")

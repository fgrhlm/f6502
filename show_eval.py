import json
from enum import Enum

C_R = "\x1b[30;41m"
C_G = "\x1b[30;42m"
C_Y = "\x1b[30;47m"
C_N = "\x1b[39;40m"
C_RST = "\x1b[0m"

if __name__=="__main__":
    with open("tests/logs/eval.json", "r") as f:
        res = json.load(f)
    
    print()
    for n in range(16): print(f"   {n:x}", end="")
    
    print()
    
    for n in range(16*16):
        index = f"{n:02x}"
        if index in res.keys():
            status = res[index]["status"]
        else:
            status = "NONE"

        match status:
            case "FAIL": color = C_R 
            case "PASS": color = C_G
            case "ERROR": color = C_Y
            case "NONE": color = C_N

        if n % 16 == 0: 
            if n > 0: print("\n")
            print(f"{int((n/16)) :x}", end=" ")
            print(f"{color}   ", end=f"{C_RST} ")
        else:
            print(f"{color}   ", end=f"{C_RST} ")

        if n == 15:         print(f"\t{C_G}    PASS    ", end=f"{C_RST}")
        if n == (16)+15:    print(f"\t{C_R}    FAIL    ", end=f"{C_RST}")
        if n == (16*2)+15:  print(f"\t{C_Y}    ERROR   ", end=f"{C_RST}")
        if n == (16*3)+15:  print(f"\t{C_N} NOT TESTED ", end=f"{C_RST}")

    print("\n")

import json
import sys

from subprocess import run
from os import listdir, path, makedirs, remove
from threading import Thread
from enum import Enum
from shutil import copyfile
from numpy import array_split

class TestResult(Enum):
    SKIP = 0
    PASS = 1
    FAIL = 2
    ERROR = 3

doc_opcodes = [
    0x00, 0x01, 0x05, 0x06, 0x08, 0x09, 0x0a, 0x0d, 0x0e,
    0x10, 0x11, 0x15, 0x16, 0x18, 0x19, 0x1d, 0x1e,
    0x20, 0x21, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2a, 0x2c, 0x2d, 0x2e,
    0x30, 0x31, 0x35, 0x36, 0x38, 0x39, 0x3d, 0x3e,
    0x40, 0x41, 0x45, 0x46, 0x48, 0x49, 0x4a, 0x4c, 0x4d, 0x4e,
    0x50, 0x51, 0x55, 0x56, 0x58, 0x59, 0x5d, 0x5e,
    0x60, 0x61, 0x65, 0x66, 0x68, 0x69, 0x6a, 0x6c, 0x6d, 0x6e,
    0x70, 0x71, 0x75, 0x76, 0x78, 0x79, 0x7d, 0x7e,
    0x81, 0x84, 0x85, 0x86, 0x88, 0x8a, 0x8c, 0x8d, 0x8e,
    0x90, 0x91, 0x94, 0x95, 0x96, 0x98, 0x99, 0x9a, 0x9d,
    0xa0, 0xa1, 0xa2, 0xa4, 0xa5, 0xa6, 0xa8, 0xa9, 0xaa, 0xad,
    0xb0, 0xb1, 0xb4, 0xb5, 0xb6, 0xb8, 0xb9, 0xba, 0xbc, 0xbd, 0xbe,
    0xc0, 0xc1, 0xc4, 0xc5, 0xc6, 0xc8, 0xc9, 0xca, 0xcc, 0xcd, 0xce,
    0xd0, 0xd1, 0xd5, 0xd6, 0xd8, 0xd9, 0xdd, 0xde,
    0xe0, 0xe1, 0xe4, 0xe5, 0xe6, 0xe8, 0xe9, 0xea, 0xec, 0xed, 0xee,
    0xf0, 0xf1, 0xf5, 0xf6, 0xf8, 0xf9, 0xfd, 0xfe 
]

emu_path = "./build/sfotemu"
tests_dir = "tests/ProcessorTests/6502/v1"

def parse_args():
    if len(sys.argv) == 1:
        print("invalid args.")
        exit(1)
    
    test_prefs = {
        "mode": -1,
        "file": "",
        "index": 0,
        "verbose": False,
        "undocumented": False
    }

    # Test args
    ARG_VERB = "-v"
    ARG_UN = "-u"
    ARG_SINGLE = "--single"
    ARG_FULL = "--full"
    ARG_EVAL = "--eval"

    def arg_value(a, i):
        return sys.argv[sys.argv.index(a) + i]

    if ARG_VERB in sys.argv:
        test_prefs["verbose"] = True

    if ARG_UN in sys.argv:
        test_prefs["undocumented"] = True
    
    if ARG_SINGLE in sys.argv:
        test_prefs["mode"] = 0
        test_prefs["file"] = arg_value(ARG_SINGLE, 1)
        test_prefs["index"] = int(arg_value(ARG_SINGLE, 2))

    if ARG_FULL in sys.argv:
        test_prefs["mode"] = 1
        test_prefs["file"] = arg_value(ARG_FULL, 1)

    if ARG_EVAL in sys.argv:
        test_prefs["mode"] = 2
    
    return test_prefs

def make_result(status, test_index, test_filename, expected, produced, log):
    return {
        "status": status,
        "opcode": test_filename,
        "test_index": test_index,
        "expected": expected,
        "produced": produced,
        "log": log
    }

def run_t(n_test, test_data, prefs):
    test = test_data[n_test]
    # Check for undocumented opcodes
    def check_undoc():
        ops = [int(x, 16) for x in test["name"].split(" ")]
        for x in ops:
            if x not in doc_opcodes:
                return True

        return False

    undoc = check_undoc()
    if undoc and not prefs["undocumented"]: 
        if prefs["verbose"]:
            print(f"SKIP [{prefs['file']} - {n_test}]")
        
        return make_result(TestResult.SKIP,n_test,prefs["file"],{},{},"")

    init = test["initial"]
    final = test["final"]
   
    # Prepare args for emu
    args = []
    args.append(init["pc"])
    args.append(final["pc"])
    args.append(init["s"])
    args.append(init["a"])
    args.append(init["x"])
    args.append(init["y"])
    args.append(init["p"])

    args.append(len(init["ram"]))
    for n in init["ram"]:
        args.append(n[0])
        args.append(n[1])

    args = [str(n) for n in args]
    args.append(prefs["file"]);
    args.append(str(n_test));
    
    args = [emu_path] + args

    #print(" ".join(args))
    
    # Run test
    result = run(args, capture_output=True, text=True)

    # Save results
    dump_fn = result.stdout.strip()
    with open(dump_fn, "r") as f:
        dl = [n.strip() for n in f.readlines()]

    remove(dump_fn)

    res_ram = [int(n.split(": ")[-1].strip()) for n in dl[6:]]
    res = {
        "pc": int(dl[0]),
        "s": int(dl[1]),
        "a": int(dl[2]),
        "x": int(dl[3]),
        "y": int(dl[4]),
        "p": int(dl[5]),
        "ram": [[int(n[0]), int(res_ram[n[0]])] for n in final["ram"]]
    }
   
    conditions = {
        "pc": res['pc'] == final['pc'],
        "s": res['s'] == final['s'],
        "a": res['a'] == final['a'],
        "x": res['x'] == final['x'],
        "y": res['y'] == final['y'],
        "p": res['p'] == final['p'],
        "ram": res['ram'] == final['ram']
    }

    # Print results
    def print_result(k, pad='03'):
        if conditions[k]:
            print("\x1b[30;42m[Y]\x1b[0m", end=" ")
            print(f"{k.upper()}: {format(final[k], pad)} == {format(res[k], pad)}")
        else:
            print("\x1b[30;41m[N]\x1b[0m", end=" ")
            print(f"{k.upper()}: {format(final[k], pad)} != {format(res[k], pad)}")
   
    if prefs["verbose"]:
        print("")
        print_result("pc", '05')
        print("")

        for n in ["s", "a", "x", "y", "p"]: print_result(n)
        print("")
        for i,n in enumerate(final["ram"]):
            loc = n[0]
            v_l = n[1]
            v_r = res['ram'][i][1]

            v_match = (v_l == v_r)
            if v_match:
                print("\x1b[30;42m[Y]\x1b[0m", end=" ")
                print(f"{loc:05}: {v_l:03} == {v_r:03}")
            else:
                print("\x1b[30;41m[N]\x1b[0m", end=" ")
                print(f"{loc:05}: {v_l:03} != {v_r:03}")
            
            #print(f"{n[0]}: {n[1]} -> {res['ram'][i][0]}: {res['ram'][i][1]}")

    # Results

    # def make_result(status, test_index, test_filename, expected, produced, log)
    old_log_filename = "tests/logs/log"
    new_log_filename = f"tests/logs/{prefs['file']}_{n_test}.log"
    copyfile(old_log_filename, new_log_filename)

    test_status = TestResult.FAIL if sum(conditions.values()) != len(conditions.values()) else TestResult.PASS
    test_results = make_result(
        test_status,
        n_test,
        prefs["file"],
        final,
        res,
        new_log_filename
    )
    
    return test_results

def open_test(f_op):
    ftest = f"{tests_dir}/{f_op}.json"
    f = open(ftest)
    data = json.load(f)

    return data

if __name__=="__main__":
    prefs = parse_args()

    match prefs["mode"]:
        case -1:
            print("No mode selected. Exiting!")
            exit()
        case 0:
            test_data = open_test(prefs["file"]) 
            res = run_t(prefs["index"], test_data, prefs)
            exit()
        case 1:
            test_data = open_test(prefs["file"])
            for i in range(len(test_data)):
                run_t(i, test_data, prefs)

            exit()
        case 2:
            test_files = listdir(tests_dir)
            test_files = [n.split('.')[0] for n in test_files]

            if not prefs["undocumented"]:
                test_files = [n for n in test_files if int(n, 16) in doc_opcodes] 
            
            result_output = {}

            index = 0
            for i, f in enumerate(test_files):
                prefs["file"] = f
                test_data = open_test(f)

                try: 
                    res = run_t(index, test_data, prefs)
                    while res["status"] == TestResult.SKIP:
                        index += 1
                        res = run_t(index, test_data, prefs)
                except:
                    res = make_result(TestResult.ERROR,index,prefs["file"],{},{},"")
                
                result_output[res["opcode"]] = res
                print(f"({i}/{len(test_files)}) {res['opcode']} - {res['status']}")
           
            with open("tests/logs/eval.json", "w") as f:
                for k in result_output.keys():
                    status = result_output[k]["status"]
                    if status == TestResult.PASS: result_output[k]["status"] = "PASS"
                    if status == TestResult.FAIL: result_output[k]["status"] = "FAIL"
                    if status == TestResult.ERROR: result_output[k]["status"] = "ERROR"

                json.dump(result_output, f, ensure_ascii=False, indent=2)


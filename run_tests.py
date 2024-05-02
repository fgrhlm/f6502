import json
import sys
import os

from subprocess import run
from os import listdir, path, makedirs, remove
from threading import Thread, Lock
from shutil import copyfile
from numpy import array_split
from utils import ops, TestResult, color 
from time import sleep, time, perf_counter, process_time

from cProfile import Profile
from pstats import SortKey, Stats

emu_path = "./build/sfotemu"
tests_dir = "tests/ProcessorTests/6502/v1"

def print_perf(t1, t2, f):
    print("--------")
    print(f"measurement: {f}")
    print(f"real: {t2[0] - t1[0]:.2f}s")
    print(f"cpu: {t2[1] - t1[1]:.2f}s")
    print("--------")

def m_perf():
    return perf_counter(), process_time()

def parse_args():
    if len(sys.argv) == 1:
        print("invalid args.")
        exit(1)
    
    test_prefs = {
        "mode": -1,
        "file": "",
        "index": 0,
        "verbose": False,
        "undocumented": False,
        "limit": 0,
        "group": None
    }

    # Test args
    ARG_VERB = "-v"
    ARG_UN = "-u"
    ARG_SINGLE = "--single"
    ARG_FULL = "--full"
    ARG_EVAL = "--eval"
    ARG_LIMIT = "--limit"
    ARG_GROUP = "--group"

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
    
    if ARG_LIMIT in sys.argv:
        test_prefs["limit"] = int(arg_value(ARG_LIMIT, 1))
    
    if ARG_GROUP in sys.argv:
        test_prefs["mode"] = 1
        test_prefs["group"] = arg_value(ARG_GROUP, 1)
    
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

def make_cmd_args(emup, testp, testi, init, final):
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
    args.append(testp);
    args.append(str(testi));
    
    args = [emup] + args

    return args

def run_t(n_test, test_data, prefs):
    test = test_data[n_test]["test"]
    test_index = test_data[n_test]["index"]
    # Check for undocumented opcodes
    def check_undoc():
        test_ops = [x for x in test["name"].split(" ")]
        for x in test_ops:
            return ops[x]["doc"]

    undoc = check_undoc()
    if not undoc and not prefs["undocumented"]: 
        if prefs["verbose"]:
            print(f"SKIP [{prefs['file']} - {n_test}]")
        
        return make_result(TestResult.SKIP,n_test,prefs["file"],{},{},"")

    init = test["initial"]
    final = test["final"]
    args = make_cmd_args(emu_path, prefs["file"], test_index, init, final) 
   
    log_root = "logs/"
    if not os.path.exists(log_root):
        os.makedirs(log_root)
    
    dump_fn = f"{log_root}{prefs['file']}_{test_index}.dump"
    log_fn = f"{log_root}{prefs['file']}_{test_index}.log"
    # Run test
    try:
        result = run(
            args, 
            env={
                "EMU_DUMP_FILE": str(dump_fn),
                "EMU_LOG_FILE": str(log_fn)
            }
        )
    except:
        print("Exec failed!")

    # Save results
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
            print(color("g", "[Y]"), end=" ")
        else:
            print(color("r", "[N]"), end=" ")
        
        print(f"{k.upper()}: {format(final[k], pad)} ({format(hex(final[k]), pad)}) -> {format(res[k], pad)} ({format(hex(res[k]), pad)})")
   
    if prefs["verbose"]:
        print_result("pc", '05')
        print("")

        for n in ["s", "a", "x", "y", "p"]: print_result(n)
       
        print("")
        print(f"{final['p']:08b}")
        print(f"{res['p']:08b}")
        print("NVXBDIZC")

        print("")
        for i,n in enumerate(final["ram"]):
            loc = n[0]
            v_l = n[1]
            v_r = res['ram'][i][1]

            v_match = (v_l == v_r)
            if v_match:
                print(color("g", "[Y]"), end=" ")
            else:
                print(color("r", "[N]"), end=" ")
            
            print(f"{loc:05}: {v_l:03} -> {v_r:03}")
            
            #print(f"{n[0]}: {n[1]} -> {res['ram'][i][0]}: {res['ram'][i][1]}")

    # Results
    test_status = TestResult.FAIL if sum(conditions.values()) != len(conditions.values()) else TestResult.PASS
    test_results = make_result(
        test_status,
        test_index,
        prefs["file"],
        final,
        res,
        log_fn
    )
    
    return test_results

def open_test(f_op):
    ftest = f"{tests_dir}/{f_op}.json"
    f = open(ftest)
    data = json.load(f)
    data = [{"index": n, "test": d} for n,d in enumerate(data)]

    return data

class Progress():
    def __init__(self, nproc, icount):
        self.start = None
        self.elapsed = None
        self.end = None
        self.lock = Lock()
        self.icount = icount 
        self.icount_total = sum(icount)
        self.count = [0 for n in range(nproc)]
        self.last_count = [0 for n in range(nproc)]
        self.best = [0 for n in range(nproc)]
        self.results = []

    def push_result(self, n): self.results.append(n)
    def time_start(self):
        if self.start == None:
            self.start = time()
    
    def get_total(self): return sum(self.count)
    def get_last_total(self): return sum(self.last_count)

    def get_count(self, n): return self.count[n]
    def get_last_count(self, n): return self.last_count[n]
    def set_last_count(self): self.last_count = self.count

    def get_best(self): return sum(self.best)
    def get_ibest(self, n): return self.best[n]
    def time_get(self):
        if self.start:
            return time() - self.start
        
        return 0
    
    def set_last_total(self, i, n): self.last_count[i] = n

    def set_best(self, i, n):
        if n > self.best[i]:
            self.best[i] = n


    def inc(self, n):
        self.lock.acquire()
        self.count[n] += 1
        self.lock.release()

    def show(self):
        while sum(self.count) < sum(self.icount):
            rate = 0.5
            sleep(rate)
            t_time = self.time_get()
            total = self.get_total()
            global_performance = (self.get_total() - self.get_last_total()) * 1/rate
            local_performance = [(self.get_count(n) - self.get_last_count(n)) * 1/rate for n,_ in enumerate(self.count)]
            for i,n in enumerate(local_performance): self.set_best(i, n)

            os.system("clear")
            result_pass = len([n for n in self.results if n["status"] == TestResult.PASS])
            result_fail = len([n for n in self.results if n["status"] == TestResult.FAIL])

            print(color("bold", f"Time Elapsed:  {round(t_time, 2)}s"))
            print(color("bold", f"Current perf:  {global_performance}/s"))
            print(color("bold", f"Best perf:     {self.get_best()}/s"))
            print(color("bold", f"Total:         {total} / {self.icount_total}"))
            print(color("bold", f"Results:       PASS: [{result_pass}] FAIL: [{result_fail}]"))

            colors = ["y", "b", "m", "c"]
            for i,n in enumerate(self.count):
                color_i = (i+1) % len(colors)
                print(color(colors[color_i], f"[T{i}]:          {n} / {self.icount[i]}"))

            for i,n in enumerate(self.count):
                self.set_last_total(i,n)

            print(f"\n{color('bold', 'LOG:')}\n")
            for n in [n for n in self.results if n["status"] == TestResult.FAIL][-10:]:
                print(f"[OP: {n['opcode']} #{n['test_index']} -> {n['status']}]")


        print("Done!")

def thread_test(data, prefs, progn, prog):
    for i in range(len(data)):
        res = run_t(i, data, prefs)
            
        if prog:
            prog.inc(progn)
            prog.push_result(res)
        
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
            if prefs["group"]: 
                test_files = [n.split('.')[0] for n in listdir(tests_dir)]
                test_files = [n for n in test_files if ops[n]["name"] == prefs["group"]]
            else:
                test_files = [prefs["file"]]

            for n in test_files: 
                n_threads = 4
                test_data = open_test(n)
                test_data = array_split(test_data, n_threads)
                progress = Progress(n_threads, [len(n) for n in test_data])
                threads = [Thread(target=thread_test, args=(test_data[n], prefs, n, progress)) for n in range(n_threads)]
                prog_t = Thread(target=progress.show)

                progress.time_start()
                for n in threads: n.start()
                prog_t.start()
                prog_t.join()
                for n in threads: n.join()
            
            exit()

        case 2:
            test_files = listdir(tests_dir)
            test_files = [n.split('.')[0] for n in test_files]

            if not prefs["undocumented"]:
                test_files = [n for n in test_files if ops[n]["doc"]] 
            
            result_output = {}
            if prefs["limit"] > 0: print(f"Limited eval @ {prefs['limit']}")
            for i, f in enumerate(test_files):
                index = 0
                prefs["file"] = f
                test_data = open_test(f)

                try: 
                    res = run_t(index, test_data, prefs)
                    next_test = res["status"] == TestResult.SKIP or res["status"] == TestResult.PASS
                    while next_test:
                        if index >= prefs["limit"]: break
                        print(f"\r{f} {index} / {'10000' if prefs['limit'] == 0 else prefs['limit']}", end="")
                        index += 1
                        res = run_t(index, test_data, prefs)
                except:
                    res = make_result(TestResult.ERROR,index,prefs["file"],{},{},"")
                
                result_output[res["opcode"]] = res
                status = res["status"]
                res_str = color("g", f" TEST: {res['opcode']},json\tSTATUS: PASS ") if status == TestResult.PASS else color("r", f" TEST: {res['opcode']}.json\tSTATUS: FAIL @ {index} ")
                print(f"\r{res_str}")
           
            with open("tests/logs/eval.json", "w") as f:
                for k in result_output.keys():
                    status = result_output[k]["status"]
                    if status == TestResult.PASS: result_output[k]["status"] = "PASS"
                    if status == TestResult.FAIL: result_output[k]["status"] = "FAIL"
                    if status == TestResult.ERROR: result_output[k]["status"] = "ERROR"

                json.dump(result_output, f, ensure_ascii=False, indent=2)


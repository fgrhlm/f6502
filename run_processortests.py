import utils
import os
import json
import pickle

from utils import TestMode, TestResult, make_cmd_args, make_env, parse_test, open_test, run_test
from numpy import array_split
from threading import Thread

def eval(prefs):
    # Open tests
    tests = []
    files = os.listdir(utils.tests_dir)
    
    for i,n in enumerate(files):
        print(f"Parsing file {i}/{len(files)}")
        file = open_test(n)
        tests = [parse_test(n) for n in file]

        print("Starting eval..")
        
        tests = array_split(tests, utils.n_threads)
        total_len = sum([len(n) for n in tests])

        fail = False

        def t_run(t):
            for n in t:
                run_test(n["args"], n["env"])

        threads = [Thread(target=t_run, args=(tests[n],)) for n in range(utils.n_threads)]

        for t in threads: t.start()

        while len(results) < total_len:
            print(f"\r{len(results)} / {total_len}         ", end="")

        for t in threads: t.join()

if __name__=="__main__":
    prefs = utils.parse_args()

    match prefs["mode"]:
        case TestMode.EVAL:
            eval(prefs)
            exit()
        case TestMode.EVAL_GROUP:
            exit()
        case TestMode.OP_SINGLE:
            exit()
        case TestMode.OP_FULL:
            exit()
        case TestMode.NO_MODE:
            print("No test mode was specified.")
            exit()

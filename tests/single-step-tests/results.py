import sys

if __name__=="__main__":
    fn = sys.argv[1]
    with open(fn, "r") as f:
        lines = [n.rstrip('\n').split(" ") for n in f.readlines()]
        lines = [[int(n[0].split("/")[-1].rstrip(".json"), 16), int(n[1]), int(n[2])] for n in lines]

    for n in range(256):
        if n % 16 == 0: print()
        t = lines[n]

        if t[2] > 0:
            print("\x1b[31m",end="")
        else:
            print("\x1b[32m",end="")

        print("%0.2X\x1b[0m" % lines[n][0], end=" ")

    print("\n")

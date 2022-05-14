from cs50 import get_float
import sys, csv

def longestSeq(str):
    count, i, max = 0, 0, 0
    testf = open(sys.argv[2], "r")
    testr = testf.read()

    while i < len(testr)-len(str):
        if testr[i:i+len(str)] == str:
            count += 1
            i += len(str)
        else:
            i += 1
            if count > max:
                max = count
            count = 0

    testf.close()
    return max

def match():
    match = "No match"

    # open csv file
    csvf = open(sys.argv[1])

    #get list of STRs
    csvr = csv.reader(csvf)
    header = next(csvr)[1:]

    # put longest sequence of each into a list
    longest_strs = []
    for dnastr in header:
        longest_strs.append(longestSeq(dnastr))

    ls = [str(x) for x in longest_strs]

    # check if any match
    for row in csvr:
        if ls == row[1:]:
            csvf.close()
            return row[0]

    csvf.close()
    return match

def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py dict_file text_file ")
        return
    else:
        print(match())

main()

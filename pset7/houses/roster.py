import sys
from cs50 import SQL
import csv

def roster():
    given_house = sys.argv[1]
    db = SQL("sqlite:///students.db")
    students = db.execute("SELECT * FROM students WHERE house=? ORDER BY last, first", (given_house,))

    # each of students is a dict
    for stud in students:
        if stud["house"] == given_house:
            first = stud["first"]
            last = stud["last"]
            mid = stud["middle"]
            birth = stud["birth"]
            if mid == None:
                print(first, " ", last,", born in", " ", birth, sep="")
            else:
                print(first, " ", mid, " ", last,", born in", " ", birth, sep="")

def main():
    if len(sys.argv) != 2:
        print("Usage: python import.py house name ")
        return
    else:
        roster()

main()

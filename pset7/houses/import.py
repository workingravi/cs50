import sys
from cs50 import SQL
import csv

def insert():

    with open(sys.argv[1], "r") as f:
        reader = csv.DictReader(f)
        #next(reader)
        #num = 1

        for row in reader:
            full_name = row["name"]
            house = row["house"]
            birth = row["birth"]

            db = SQL("sqlite:///students.db")
            split_name = full_name.split()
            if len(split_name) == 3:
                first = split_name[0]
                middle = split_name[1]
                last = split_name[2]
            else:
                first = split_name[0]
                middle = None
                last = split_name[1]

            #record = (num, first, middle, last, house, birth,)
            #record = (num first, middle, last, house, birth,)
            db.execute("INSERT into students (first, middle, last, house, birth) VALUES (?,?,?,?,?)", first, middle, last, house, birth)
            #num += 1;

def main():
    if len(sys.argv) != 2:
        print("Usage: python import.py csv_file ")
        return
    else:
        insert()

main()

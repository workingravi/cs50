from cs50 import get_int

def print_spaces(n):
    print(" "*n, end="")

def print_hashes(n):
    print("#"*n, end="")


def main():
    ht = 0
    while ht < 1 or ht > 8:
        ht = get_int("Height: ")

    for i in range(1, ht+1):
        print_spaces(ht-i)
        print_hashes(i)
        print_spaces(2)
        print_hashes(i)
        print()
main()




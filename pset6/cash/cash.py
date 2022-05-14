from cs50 import get_float
#from math import round

def coins(cash):
    coins = 0
    cc = cash * 100

    for c in [25, 10, 5, 1]:
        coins += cc//c
        cc %= c

    return round(coins)

def main():
    ht = 0.0
    while True:
        ht = get_float("Cash: ")
        if ht > 0:
            break

    print(coins(ht))

main()


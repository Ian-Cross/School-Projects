import sys
from math import log

def eCalculation(n,f):
    m = 4
    test = (n + 1) * 2.30258509

    while (1):
        m += 1
        if (m * (log(m) - 1.0) + 0.5 * log(6.2831852 * m) > test):
            break

    coef = [1] * (m+1)

    f.write(str(2) + ".")

    for i in range(1,m+1):
        carry = 0
        for j in range(m,1,-1):
            temp = int(coef[j] * 10 + carry)
            carry = int(temp / j)
            coef[j] = int(temp - carry * j)
        f.write(str(carry))

def main():
    print("Welcome to Euler e Estimation")
    print("Please enter a file for output:")

    filename = input()

    with open(filename,"w",encoding = 'utf-8') as f:
        eCalculation(100, f);

if __name__ == '__main__':
    main()

import sys
import re
from math import ceil, log, sqrt, floor

__local_run__ = False
if __local_run__:
    sys.stdin = open('input.txt', 'r')
    sys.stdout = open('output.txt', 'w')

def main():
    a = int(input())
    b = int(input())
    print(a*b)

main()
from funcK2 import *

numbers = readNumbers()
pairs = readPairs()

for pair in pairs:
    print(greatestCommonDivisorForList(numbers[pair[0]:pair[1]+1]))
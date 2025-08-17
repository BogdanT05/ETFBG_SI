def readNumbers():
    enter = input().split(" ")
    enter = [int(i) for i in enter]
    return enter

def readPairs():
    pairs = []
    while True:
        enter = input()
        if enter == "":
            break

        pair = enter.split(",")
        pair = [int(i) for i in pair]
        pair = tuple(pair)
        pairs.append(pair)

    return pairs

def greatestCommonDivisor(value0, value1):
    value = min(value0, value1)
    i = 1
    while i <= value:
        if value0 % i == 0 and value1 % i == 0:
            najveci = i
        i+=1

    return najveci

def greatestCommonDivisorForList(listOfValues):
    gcdfl = []
    for value in range(0,len(listOfValues), 2):
        try:
            gcdfl.append(greatestCommonDivisor(listOfValues[value], listOfValues[value+1]))
        except IndexError:
            gcdfl.append(listOfValues[value])

    if len(gcdfl) == 1:
        return gcdfl[0]
    else:
        return greatestCommonDivisorForList(gcdfl)

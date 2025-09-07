def readNumbers():
    enter = input().split(",")
    enter = [int(i) for i in enter]
    return enter

def readPairs():
    pairs = []
    while True:
        enter = input()
        if enter == "":
            break

        pair = enter.split()
        pair = [int(i) for i in pair]
        pair = tuple(pair)
        pairs.append(pair)

    return pairs

def leastCommonMultiple(value0, value1=1):
    i = 1
    valuex = []
    valuey = []
    while True:
        valuex.append(value0*i)
        valuey.append(value1*i)

        for k in valuex:
            for j in valuey:
                if k == j:
                    return k
        i += 1

def leastCommonMultipleForList(listOfValues):
    lof = []
    for value in range(0,len(listOfValues), 2):
        try:
            lof.append(leastCommonMultiple(listOfValues[value], listOfValues[value+1]))
        except IndexError:
            lof.append(leastCommonMultiple(listOfValues[value]))

    if len(lof) == 1:
        return lof[0]
    else:
        return leastCommonMultipleForList(lof)


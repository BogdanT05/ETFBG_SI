def readClientTimes():
    enter = input().split()
    if len(enter) > 0:
        enter = [int(i) for i in enter]

    return enter

def writeQueue(q):
    print(*q, sep="->")

def totalWorkHours(clientTimes):
    x = clientTimes[0]
    y = clientTimes[1]

    salter1 = [x]
    salter2 = [y]

    clientTimes.pop(0)
    clientTimes.pop(0)

    while len(clientTimes) > 0:
        while x > 0 and y > 0:
            x = x - 1
            y = y - 1

        if x == 0:
            salter1.append(clientTimes[0])
            x = clientTimes[0]
            clientTimes.pop(0)
        if y == 0:
            salter2.append(clientTimes[0])
            y = clientTimes[0]
            clientTimes.pop(0)

    writeQueue(salter1)
    writeQueue(salter2)
    return max(sum(salter1), sum(salter2))

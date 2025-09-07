def readClientTimes():
    enter = input().split()
    if len(enter) > 0:
        enter = [int(i) for i in enter]

    return enter

def writeQueue(q):
    print(*q, sep=" ")

def work(clientTimes, window1, window2):
    clientTimes_copy = [i for i in clientTimes]
    clientTimes_copy[0] = "x"
    clientTimes_copy[1] = "x"

    x = clientTimes[0]
    y = clientTimes[1]

    window1.append(1)
    window2.append(2)

    clientTimes.pop(0)
    clientTimes.pop(0)

    while len(clientTimes) > 0:
        while x > 0 and y > 0:
            x = x - 1
            y = y - 1

        if x == 0:
            window1.append(clientTimes_copy.index(clientTimes[0]) + 1)
            clientTimes_copy[clientTimes_copy.index(clientTimes[0])] = 'x'
            x = clientTimes[0]
            clientTimes.pop(0)
        if y == 0:
            window2.append(clientTimes_copy.index(clientTimes[0]) + 1)
            clientTimes_copy[clientTimes_copy.index(clientTimes[0])] = 'x'
            y = clientTimes[0]
            clientTimes.pop(0)

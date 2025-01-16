def readChanges():
    changes = []
    while True:
        change = []
        enter = input()

        if enter == "":
            break

        enter = enter.split(" ")
        change.append(enter[0])
        change.append(int(enter[1]))
        changes.append(change)

    return changes

def calculateValue(startValue, changes, time):

    for change in changes:
        start_time = change[0]
        if start_time < time:
            startValue = startValue + change[1]

    return startValue



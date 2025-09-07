from func import *

changes = readChanges()
times = []
while True:
    time = input()
    if time == "":
        break
    times.append(time)

for time in times:
    if time is not times[-1]:
        print(calculate(changes, time))
    else:
        print(calculate(changes, time), end="")
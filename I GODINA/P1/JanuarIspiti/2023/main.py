from func import *

start_value = int(input())
changes = readChanges()
times = []
while True:
    time_value = input()
    if time_value == "":
        break
    times.append(time_value)

for time in times:
    if time != times[-1]:
        print(calculateValue(start_value, changes, time))
    else:
        print(calculateValue(start_value, changes, time), end="")
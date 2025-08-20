from func import *

numPages = int(input())
dict_arranged = arrange(read(), numPages)

for key, value in sorted(dict_arranged.items()):
    if key is not sorted(dict_arranged.keys())[-1]:
        if -1 in value:
            print(f"{key} = N/A")
        else:
            print(f"{key} = {sum(value):.2f}")
    else:
        if -1 in value:
            print(f"{key} = N/A", end="")
        else:
            print(f"{key} = {sum(value):.2f}", end="")
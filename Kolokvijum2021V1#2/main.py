from func import *

subtitutions = readSubtitutions()
niz_sekvenci = []
while True:
    unos_sekvence = input()
    sequence = unos_sekvence.split()

    for i in range(len(sequence)):
        sequence[i] = int(sequence[i])

    niz_sekvenci.append(sequence)

    if unos_sekvence == "":
        break

niz_sekvenci.pop(-1)

for i in niz_sekvenci:
    if i != niz_sekvenci[-1]:
        print(*encrypt(i, subtitutions))
    else:
        print(*encrypt(i, subtitutions), end='')


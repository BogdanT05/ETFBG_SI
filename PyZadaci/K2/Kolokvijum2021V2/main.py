from func import *

lista_sekvenci = []

key = readKey()
input()
zapamti_key = key

while True:
    a = input()
    if a == "":
        break

    sequence_slova = a.split()
    sequence = [int(sequence_slova[x]) for x in range(len(sequence_slova))]
    lista_sekvenci.append(sequence)

for sekvenca in lista_sekvenci:
    key = zapamti_key.copy()
    transpose(sekvenca, key)

    if sekvenca == lista_sekvenci[-1]:
        print(*sekvenca, end="")
    else:
        print(*sekvenca)
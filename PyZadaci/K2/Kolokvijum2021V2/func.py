def readKey():
    unos = input()
    lista_unosa = unos.split(",")
    key = [int(x) for x in lista_unosa]
    return key

def transpose(sequence, key):
    brojac = 0
    prazna_lista = [0 for x in range(len(sequence))]
    pozicija = 0
    ostatak = []

    while len(sequence) % len(key) != 0:
        ostatak.append(sequence[-1])
        sequence.pop(-1)
        prazna_lista.pop(-1)

    brojac_uporedjivanja = len(sequence)/len(key)

    while brojac < brojac_uporedjivanja:
        for i in range(len(key)):
            prazna_lista[i+pozicija] = sequence[key[i]]

        for i in range(len(key)):
            key[i] = key[i] + len(key)

        pozicija += len(key)
        brojac += 1

    ostatak.reverse()
    for i in ostatak:
        prazna_lista.append(i)

    sequence.clear()

    for i in range(len(prazna_lista)):
        sequence.append(prazna_lista[i])

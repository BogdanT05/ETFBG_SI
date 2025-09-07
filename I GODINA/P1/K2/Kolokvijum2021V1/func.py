
def readSubtitutions():
    lista_zamena = []
    while True:
        zamena = input()

        if zamena == "":
            break

        zamena = zamena.replace(",", "")
        zamena_lista = zamena.split(" ")

        for i in range(len(zamena_lista)):
            zamena_lista[i] = int(zamena_lista[i])

        lista_zamena.append(zamena_lista)

    return lista_zamena

def encrypt(sequence, subtitutions):
    menja = []
    sa_cime_menjati = []
    zadnji_broj = 0
    parovi = []
    if len(sequence) % 2 != 0:
        zadnji_broj = sequence[-1]
        sequence.pop(-1)

    for i in range(0, int(len(sequence)), 2):
        par = [sequence[i], sequence[i + 1]]
        parovi.append(par)


    for i in range(len(subtitutions)):
        par = []
        ne_par = []
        menjati = False
        for j in range(len(subtitutions[i])):
            if j < 2:
                par.append(subtitutions[i][j])
            else:
                ne_par.append(subtitutions[i][j])

        brojac = parovi.count(par)
        for k in range(brojac):
            if par in parovi:
                menja.append(par)
                menjati = True

            if menjati:
                sa_cime_menjati.append(ne_par)

    lista_index = []

    for i in range(len(parovi)):
        if parovi[i] not in menja:
            parovi[i] = [0, 0]
        else:
            lista_index.append(i)

    j = 0
    for i in lista_index:
        if j < len(sa_cime_menjati):
            parovi[i] = sa_cime_menjati[j]
            j += 1

    konacna_lista = []

    for i in range(len(parovi)):
        for j in parovi[i]:
            konacna_lista.append(j)

    if zadnji_broj != 0:
        konacna_lista.append(zadnji_broj)
    return konacna_lista








def readNumbers():
    br = input()
    br_lista = br.split()
    br_lista = [int(x) for x in br_lista]
    return br_lista

def readThrees():
    lista_trojki = []
    while True:
        lista_trojka = []
        trojka = input()

        if trojka == "":
            break

        lista_trojka = trojka.split(", ")
        lista_trojka = [int(x) for x in lista_trojka]
        lista_trojki.append(lista_trojka)

    return lista_trojki

def incOrDec(ind1, ind2, arr, value):
    if arr[ind1] > arr[ind2]:
        arr[ind1] -= value
        arr[ind2] += value

    elif arr[ind1] == arr[ind2]:
        arr[ind1] += value
        arr[ind2] += value

    else:
        arr[ind2] -= value
        arr[ind1] += value

def printArray(arr):
    print(*arr)

def isSorted(arr):
    kopija_arr = arr.copy()
    kopija_arr.sort()
    if arr == kopija_arr:
        return True
    else:
        return False





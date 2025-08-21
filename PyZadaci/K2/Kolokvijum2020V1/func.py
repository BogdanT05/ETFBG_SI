
def readNumbers():
    br = input()
    br_lista = br.split(",")
    br_lista = [int(x) for x in br_lista]
    return br_lista

def readPairs():
    br_parova = int(input())
    lista_parova = []
    for i in range(br_parova):
        par = []
        par_unos = input()
        par = par_unos.split(",")
        par = [int(x) for x in par]
        lista_parova.append(par)

    return lista_parova

def copyNumbers (arr):
    kopija_arr = arr.copy()
    return kopija_arr

def swap(ind1, ind2, arr):
    kopija = arr.copy()
    if ind1 < len(kopija) and ind2 < len(kopija):
        kopija[ind1], kopija[ind2] = arr[ind2], arr[ind1]

    arr.clear()
    for x in kopija:
        arr.append(x)
    return arr

def compareArrays(arr1, arr2):
    isti = False
    if len(arr1) == len(arr2):
        for i in range(len(arr1)):
            if arr1[i] != arr2[i]:
                isti = False
                break
            else:
                isti = True

    if len(arr1) == 0 and len(arr2) == 0:
        isti = True

    return isti

def printArray(arr):
    print(*arr, sep=",")






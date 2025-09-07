from func import *

niz = readNumbers()
parovi = readPairs()

niz_kopija = copyNumbers(niz)

for par in range(len(parovi)):
    swap(parovi[par][0], parovi[par][1], niz_kopija)
    printArray(niz_kopija)

if compareArrays(niz, niz_kopija):
    print("ISTI", end="")
else:
    print("NIJE ISTI", end="")
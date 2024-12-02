from func import *

niz = readNumbers()
trojke = readThrees()

for i in trojke:
    incOrDec(i[0], i[1], niz, i[2])
    printArray(niz)

if isSorted(niz):
    print("SORTIRAN")
else:
    print("NIJE SORTIRAN")

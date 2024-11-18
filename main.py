
N = int(input("Unesi broj elemenata niza: "))
lista = []
rezultat = []
for i in range(N):
    lista.append(int(input("Unesi element niza: ")))

min_el = min(lista)

for i in range(len(lista)-2):
    trojka = lista[i:i+3]

    if min_el in trojka:
        rezultat.append(trojka)

print(rezultat)



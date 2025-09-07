

def read_demands():
    red_voznje = input()
    lista_zahteva = red_voznje.split(" ")

    for zahtev in range(len(lista_zahteva)):
        lista_zahteva[zahtev] = lista_zahteva[zahtev].split("-")

    for zahtev in lista_zahteva:
        for i in range(len(zahtev)):
            zahtev[i] = int(zahtev[i])

    return lista_zahteva


def remove_invalid(demands):
    for demand in demands:
        if demand[0] == demand[1]:
            demands.remove(demand)

    return demands


def process_demands(demands):
    navise = []
    nanize = []
    niz_navise = []
    niz_nanize = []
    for demand in demands:
        if demand[0] < demand[1]:
            navise.append(demand)
        else:
            nanize.append(demand)

    for element in navise:
        for i in range(len(element)):
            niz_navise.append(element[i])

    for element in nanize:
        for i in range(len(element)):
            niz_nanize.append(element[i])

    niz_navise = sorted(niz_navise)
    niz_nanize = sorted(niz_nanize)

    bez_duplikata_navise = []
    bez_duplikata_nanize = []

    for el in niz_navise:
        if el in bez_duplikata_navise:
            continue
        bez_duplikata_navise.append(el)

    for el in niz_nanize:
        if el in bez_duplikata_nanize:
            continue
        bez_duplikata_nanize.append(el)

    konacna_lista = bez_duplikata_navise + bez_duplikata_nanize[::-1]
    return konacna_lista
from operator import index


def read_names():
    unos = input()
    lista_predmeta = unos.split(",")
    return lista_predmeta

def read_prices():
    unos_cena = input()
    lista_cena = unos_cena.split(" ")

    for i in range(len(lista_cena)):
         lista_cena[i] = int(lista_cena[i])

    return lista_cena

def read_pairs():
    lista_parove = []
    while True:
         par = input()
         if  par == "":
             break

         par_u_listi = par.split("-")
         par_u_listi[1] = int(par_u_listi[1])
         lista_parove.append(par_u_listi)

    return lista_parove

def calc_discount(names, old_prices, article):

    for i in range(len(names)):
        if article[0] == names[i]:
            artikl_cena = old_prices[i]

    popust = 100-(article[1]/artikl_cena)*100

    return popust

def print_biggest_discount(names, prices, articles):
    lista_popusta = []

    for i in range(len(articles)):
        lista_popusta.append(calc_discount(names, prices, articles[i]))

    indeks_najveceg_popusta = lista_popusta.index(max(lista_popusta))
    ime_najveceg = (articles[indeks_najveceg_popusta])
    print(ime_najveceg[0], format(max(lista_popusta), ".2f"), end="")






import re

def read_books(filename):
    lista = []
    with open(filename, 'r') as f:
        for line in f.readlines():
            lista.append(line.strip())

    return lista

def format_authors(book_data):

    plista = re.search(r",(.*)-", book_data).group(1)
    plista1 = plista.split()
    ime = plista1[0].upper()
    prezime = plista1[-1].capitalize()
    ime_prezime = f"{ime[0]}. {prezime}"
    book_data = book_data.replace(plista, ime_prezime)

    return book_data

def write_books(books, filename):
    books_format = []
    for book in books:
        books_format.append(format_authors(book))

    with open(filename, 'w') as f:
        for line in books_format:
            f.write(f"{line}\n")

def find_best_prices(filename):
    books = read_books(filename)
    cene = []
    imena_knjiga = []
    knjizare = []
    konacno_resenje = []
    for book in books:
        cena = re.search(r"(\d+)", book).group(1)
        cene.append(int(cena))

        knjizara = re.search(r"-(.*)[(]", book).group(1)
        knjizare.append(knjizara)

        imena = book.split(',')
        imena_knjiga.append(imena[0])

    for knjiga in imena_knjiga:
        za_uporediti = [knjiga]
        indeksi = []

        for i in range(len(imena_knjiga)):
            if imena_knjiga[i] in za_uporediti:
                za_uporediti.append(imena_knjiga[i])
                indeksi.append(i)

        najmanji = cene[indeksi[0]]
        najmanji_ind = indeksi[0]
        ako_isti = []
        for k in indeksi:
            if cene[k] < najmanji:
                najmanji = cene[k]
                najmanji_ind = k

            elif cene[k] == najmanji:
                ako_isti.append(k)


        if len(ako_isti) != 0:
            if ako_isti not in konacno_resenje:
                konacno_resenje.append(ako_isti)
        else:
            if najmanji_ind not in konacno_resenje:
                konacno_resenje.append(najmanji_ind)


    cena_knjiga = []
    for i in konacno_resenje:
        for j in i:
            ime = f"{imena_knjiga[j]}({cene[j]})"

        cena_knjiga.append(ime)

    svi = []
    lista_konacnih_cena = []
    for i in range(len(konacno_resenje)):
        plista = [cena_knjiga[i]]
        plista1 = []

        for k in konacno_resenje[i]:
            plista1.append(knjizare[k])
            lista_konacnih_cena.append(cene[k])

        plista.append(plista1)
        svi.append(plista)

    lista_koncCbezD = []
    for i in lista_konacnih_cena:
        if i not in lista_koncCbezD:
            lista_koncCbezD.append(i)

    lista_koncCbezD.sort()
    raspored = []

    for k in lista_koncCbezD:
        for i in svi:
            for j in i:
                if str(k) in j:
                    raspored.append(i)

    recnik = {}
    for i in raspored:
        recnik[i[0]] = i[1]

    return recnik



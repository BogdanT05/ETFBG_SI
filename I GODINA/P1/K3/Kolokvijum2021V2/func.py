def readLibrary(filename):
    library = []

    with open(filename, "r") as f:
        for line in f.readlines():
            lista = line.split(",")
            data = []

            for l in range(len(lista)):
                if l != 0 and l != len(lista) - 2:
                    data.append(lista[l])

            library_line = []
            zanr = []
            for i in range(len(data)):
                if i < 2 or i == len(data) - 1:
                    if i != len(data) - 1:
                        library_line.append(data[i].strip())
                    else:
                        library_line.append(float(data[i].strip()))
                else:
                    zanr.append(data[i].strip())

            library_line.insert(-1, zanr)
            library.append(library_line)

    return library

def checkIsbn(isbn):
    suma = 0
    for broj in range(len(isbn)):
        try:
            if int(isbn[broj]) % 2 == 0:
                suma += int(isbn[broj]*3)
            else:
                suma += int(isbn[broj]*1)
        except ValueError:
            continue

    if suma % 10 == 0:
        return True
    else:
        return False

def filterOkIsbn(books):
    filter = []
    for book in books:
        if checkIsbn(book[1]):
            filter.append(book)

    return filter

def pricesByCategory(books):
    prices_by_categ = dict()
    categories = []

    for book in books:
        for category in book[2]:
            if category not in categories:
                categories.append(category)

    for category in categories:
        cene = []
        for book in books:
            if category in book[2]:
                cene.append(book[-1])

        prices_by_categ[category] = cene

    return prices_by_categ

def averagePrice(prices):
    return sum(prices)/len(prices)

def titles(books, avgPrice, category):
    title = set()

    for book in books:
        if category in book[2] and book[-1] > avgPrice:
            title.add(book[0])

    return title





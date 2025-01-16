def readLibrary(filename):
    library = []

    with open(filename, "r") as f:
        for line in f.readlines():
            lista = line.split(",")
            data = []

            for l in range(len(lista)):
                if l != 2 and l != len(lista) - 1:
                    data.append(lista[l])

            library_line = []
            zanr = []
            for i in range(len(data)):
                if i < 2 or i == len(data) - 1:
                    library_line.append(data[i].strip())
                else:
                    zanr.append(data[i].strip())

            for godina in range(len(library_line)):
                if godina == len(library_line) - 1:
                    library_line[godina] = int(library_line[godina].split(".")[-2].strip())

            library_line.insert(-1, zanr)
            library.append(library_line)

    return library

def filterYear(books, years):
    filter_books = []
    for book in books:
        if book[-1] in years:
            filter_books.append(book)

    return filter_books

def organizeYearCategory(books):
    keys = []
    organized = {}

    for book in books:
        if book[-1] not in keys:
            keys.append(book[-1])

    for key in keys:
        values = {}
        for book in books:
            if key in book:
                for value in book[2]:
                    values[value] = 0

        for value in values:
            for book in books:
                if key in book:
                    if value in book[2]:
                        values[value] += 1

        organized[key] = values

    return organized

def largestCategory(booksByCategory):
    najveci = max(booksByCategory.values())

    for key in booksByCategory.keys():
        if booksByCategory[key] == najveci:
            return key

def titles(books, category, year):
    title = set()
    for book in books:
        if year in book and category in book[2]:
            title.add(book[0])

    return title
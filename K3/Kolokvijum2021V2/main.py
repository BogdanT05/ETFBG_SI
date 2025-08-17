from func import *

"""
Zadatak ovde dobro radi a kada se kompajlira na 
moodle sajtu iz nekog razloga pitanje 7 ne radi kako treba :)
library.csv je ovde drugaciji nego na moodle zato sto sam hteo
da testiram na vise primera da li radi kod i radi.
Ako neko smisli kako da radi pitanje 7 na moodle nek javi :)
"""

books = readLibrary("library.csv")
filter_books = filterOkIsbn(books)
pbc = pricesByCategory(filter_books)

titles_set = set()

for key, value in pbc.items():
    avg_price = averagePrice(value)
    title = frozenset((titles(filter_books, avg_price, key)))

    if len(title) > 0:
        titles_set.add(title)

print(titles_set)
print(len(titles_set), end="")
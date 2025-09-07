from func import *

books = readLibrary('library.csv')
years = {2017, 2018, 2019}
filter_books = filterYear(books, years)
organized = organizeYearCategory(filter_books)

resenje = set()
for keys in organized.keys():
    najveci = largestCategory(organized[keys])
    resenje = resenje.union(titles(filter_books, najveci, keys))

print(len(resenje), end="")
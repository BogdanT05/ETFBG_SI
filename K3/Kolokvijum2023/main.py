from func import *

tekst = read_paper("paper.txt")
reformat = write_paper(tekst, "reformatted.txt")
ponavljanja = count_occurrences("reformatted.txt", "occurrences.txt")


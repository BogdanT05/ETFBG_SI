import re
from time import process_time_ns
from traceback import print_tb


def read_polls(filename):
    list_of_polls = []
    with open(filename, "r", encoding="utf-8") as f:
        pattern = re.compile(r"([A-Z]+)\|([\wčćžšđČĆŽŠĐ]+ [ \wčćžšđČĆŽŠĐ]*)+ - ((\d\.\d+:\d+)(, \d\.\d\d:\d\d)*)+")
        lines = f.readlines()
        for line in lines:
            poll = []

            matches = pattern.search(line.strip())
            katedra = matches.group(1)
            ime_prezime = matches.group(2)
            ankete = matches.group(3)
            poll.append(katedra)
            poll.append(ime_prezime)
            ankete = ankete.split(',')
            ankete_final = []

            for anketa in ankete:
                anketa_pojedinacno = anketa.split(":")
                n_torka = (float(anketa_pojedinacno[0]), int(anketa_pojedinacno[1]))
                ankete_final.append(n_torka)

            poll.append(ankete_final)
            list_of_polls.append(poll)

    return list_of_polls

def process_polls(polls_list):
    katedre = {poll[0] for poll in polls_list}
    k_dict = {}

    for k in katedre:
        names = set()
        inner_dict = {}

        for poll in polls_list:
            if k == poll[0]:
                names.add(poll[1])

        for name in names:
            inner_dict[name] = 0
        k_dict[k] = inner_dict

    for key,value in k_dict.items():
        for v in value.keys():
            avg = []
            for poll in polls_list:
                if key == poll[0] and v == poll[1]:
                    for el in poll[2]:
                        if el[1] > 9:
                            avg.append(el[0])
            if len(avg) == 0:
                value[v] = 0
            else:
                value[v] = (sum(avg)/len(avg))

    return k_dict

def write_polls(polls_dict):
    sorted_dict = {}
    za_ispis = []
    for key in sorted(polls_dict):
        sorted_dict[key] = polls_dict[key]

    for key,value in sorted_dict.items():
        sorted_inner_dict = {}
        names = value.keys()
        names = [x for x in names]
        avgs = value.values()
        avgs = [x for x in avgs]
        avgs_sorted = sorted(avgs, reverse=True)

        for a in range(len(avgs_sorted)):
            for aa in range(len(avgs)):
                if avgs[aa] == avgs_sorted[a]:
                    sorted_inner_dict[names[aa]] = avgs_sorted[a]

        sorted_dict[key] = sorted_inner_dict

    for key, values in sorted(sorted_dict.items()):
        s = f"{key}:"
        counter = 0

        for value in values:
            if counter == 0:
                s = s + f" {value}"
                counter += 1
            else:
                if len(polls_dict[key]) > 1 and counter < 3:
                    s = s + f", {value}"
                    counter += 1
        za_ispis.append(s)

    with open("best.txt", "w", encoding="utf-8") as f:
        for line in za_ispis:
            if line is not za_ispis[-1]:
                f.write(line+"\n")
            else:
                f.write(line)



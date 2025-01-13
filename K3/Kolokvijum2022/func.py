import re

def read_paper(filename):
    paper = []
    with open(filename, 'r') as f:
        for line in f.readlines():
            paper.append(line.strip())

    return paper

def reformat_citation(line):

    nadji = re.findall(r"\{[^a-zA-Z]*}", line)
    uredjeno = []

    for i in range(len(nadji)):
        nadji[i] = nadji[i].replace("{"," ").replace("}", " ").strip()
        uredjeno.append(nadji[i].split())

    for group in uredjeno:
        zamena = ""
        for g in group:
            plista = g.split(",")
            for clan in plista:
                plista1 = clan.split("-")
                if len(plista1) > 1:
                    plista1 = [int(i) for i in plista1]
                    while plista1[0] <= plista1[1]:
                        zamena = zamena + f"[{plista1[0]}]"
                        plista1[0] += 1
                else:
                    zamena = zamena + f"[{plista1[0]}]"

        line = line.replace(re.search(r"\{[^a-zA-Z]*}", line).group(), zamena)
    return line

def write_paper(paper, filename):
    with open(filename, "w") as f:
        for line in paper:
            if line != paper[len(paper)-1]:
                f.write(reformat_citation(line) + "\n")
            else:
                f.write(reformat_citation(line))

def count_occurrences(inp_filename, out_filename):
    radna_lista = read_paper(inp_filename)
    ponavljanja = []
    recnik = {}
    for line in radna_lista:
        nadji = re.findall(r"\[\d*]", line)
        for n in nadji:
            zamena = n.replace("[", "").replace("]","").strip()
            ponavljanja.append(int(zamena))

    for i in ponavljanja:
        recnik[i] =  0
        for j in ponavljanja:
            if i == j:
                recnik[i] = recnik[i] + 1

    with open(out_filename, "w") as of:
        for i in sorted(recnik):
            if i != sorted(recnik)[-1]:
                of.write(f"{i} : {recnik[i]}\n")
            else:
                of.write(f"{i} : {recnik[i]}")

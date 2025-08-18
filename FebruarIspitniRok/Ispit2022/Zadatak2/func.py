def readChanges():
    list_of_changes = []
    while True:
        change = input()

        if change == "":
            break

        changes_not_formated = change.split()
        changes = []
        for change in changes_not_formated:
            try:
                changes.append(int(change))
            except ValueError:
                changes.append(change)

        list_of_changes.append(changes)

    return list_of_changes

def calculate(changes, time):
    dict_of_articles = {}
    sales = 0

    #Svi artikli do tog vremena
    for change in changes:
        if change[0] <= time:
            dict_of_articles[change[1]] = 0

    for key in dict_of_articles.keys():
        current_state = 0
        for change in changes:
            if key == change[1] and change[0] <= time:
                #Povecavamo stanje artikala ako su stigli novi artikli
                if change[2] > 0:
                    current_state += change[2]
                #Ako je stanje artikala vece od nula i ako je prodaja u pitanju
                if change[2] < 0 < current_state:
                    #Ako prodaja nece isprazniti magacin ili ce ga mozda isprazniti
                    if current_state + change[2] >= 0:
                        sales = sales + abs(change[2])
                        #Smanjujemo za prodate artikle
                        current_state = current_state + change[2]
                    else:
                        #Prodajemo sve artikle na stanju
                        sales = sales + current_state
                        current_state = 0

    return sales








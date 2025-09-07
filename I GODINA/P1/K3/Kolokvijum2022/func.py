
def read_tests(filename):
    tests_all = []
    with open(filename, 'r') as f:
        lista = f.readline()
        for line in f.readlines():
            if line != lista[0]:
                line = line.strip().split(",")
                line[0] = int(line[0])
                contact = line[-1].split(":")

                if contact[0] != "":
                    contact = [int(i) for i in contact]
                else:
                    contact = []
                line[-1] = contact
                tests_all.append(line)
            else:
                continue
    return tests_all

def filter_tests(tests_all, begin, end):
    tests_date = []
    for test in tests_all:
        if begin <= test[2] <= end:
            tests_date.append(test)

    return tests_date

def positive_citizens(tests_all):
    postive_test = {}

    for test in tests_all:
        isti = []
        for svaki in tests_all:
            if test[0] in svaki:
                isti.append(svaki)

        najveci_datum = isti[0][2]
        for el in isti:
            if el[2] >= najveci_datum:
                najveci_datum = el[2]

        hronoloski = []
        for el in isti:
            if najveci_datum  in el:
                hronoloski = el

        if hronoloski[1] == "+":
            postive_test[hronoloski[0]] = set(hronoloski[-1])

    return postive_test

def count_contacts(contacts):
    all_positive = []
    count_contact = {}
    tests_oldest = []

    for test in tests:
        plista = [test]
        for ponavljanje in tests:
            if ponavljanje[0] == plista[0][0] and ponavljanje not in plista:
                plista.append(ponavljanje)

        najmladji = plista[0][2]

        for datum in range(len(plista)):
            if najmladji < plista[datum][2]:
                najmladji = plista[datum][2]

        for izbaci in plista:
            if izbaci[2] == najmladji:
                tests_oldest.append(izbaci)
                break

    for test in tests_oldest:
        if test[1] == "+":
            all_positive.append(test)

    all_contacts_keys = set()
    for values in contacts.values():
        all_contacts_keys = all_contacts_keys.union(values)

    for key in contacts.keys():
        if key in all_contacts_keys:
            all_contacts_keys.remove(key)

    for contact in all_contacts_keys:
        count_contact[contact] = 0

    for key in count_contact.keys():
        count = 0
        testirano = []
        for test in all_positive:

            if key in test[-1] and test[0] not in testirano:
                count += 1
                testirano.append(test[0])

        count_contact[key] = count

    return count_contact

def print_contacts(contacts):
    for i in sorted(contacts):
        if i != sorted(contacts)[-1]:
            print(f"{i}:{contacts[i]}")
        else:
            print(f"{i}:{contacts[i]}", end="")

begin = input()
end = input()

tests = read_tests('tests.csv')
tests = filter_tests(tests, begin, end)

citizens = positive_citizens(tests)
contacts = count_contacts(citizens)

print_contacts(contacts)



import re

def read_transactions(transactionsFilename):
    transactions = []
    pattern = r"([A-Z]{2})(\d{2})([A-Z]*)(\d*)(\d{2})"

    with open(transactionsFilename, 'r') as f:
        for line in f.readlines():
            full_data = []
            data = line.split(",")

            if data[0] == "":
                first_part = []
                second_part = list(re.search(pattern, data[1]).groups())

            elif data[1] == "":
                first_part = list(re.search(pattern, data[0]).groups())
                second_part = []
            else:
                first_part = list(re.search(pattern, data[0]).groups())
                second_part = list(re.search(pattern, data[1]).groups())

            full_data.append(first_part)
            full_data.append(second_part)

            for d in data:
                if d != data[0] and d != data[1]:
                    try:
                        full_data.append(float(d))
                    except ValueError:
                        full_data.append(d.strip())

            transactions.append(full_data)

    return transactions

def remove_invalid(transactions):
    for transaction in transactions:
        counter = 2
        for i in range(len(transaction)):
            if i < 2:
                value = ""
                if len(transaction[i]) != 0:
                    for j in transaction[i]:
                        if j == transaction[i][0] or j == transaction[i][2]:
                            for ch in j:
                                val = -55+ord(ch)
                                value = value + str(val)

                    if int(value+transaction[i][3]) % int(transaction[i][4]) == int(transaction[i][1]):
                        counter -= 1
                else:
                    counter -= 1

        if counter != 0:
            transactions.remove(transaction)

    return transactions

def remove_foreign(transactions):
    transactions_rem = []
    for transaction in transactions:
        if len(transaction[0]) > 0 and len(transaction[1]) > 0:
            if transaction[0][0] == transaction[1][0]:
                transactions_rem.append(transaction)
        else:
            transactions_rem.append(transaction)

    return transactions_rem

def domestic_internal_transfers(transactions):
    counted_trans = {}
    countries = []
    for transaction in transactions:
        if len(transaction[0]) > 0:
            if transaction[0][0] not in countries:
                countries.append(transaction[0][0])
        else:
            if transaction[1][0] not in countries:
                countries.append(transaction[1][0])

    for country in countries:
        counted_trans[country] = []

    for key in counted_trans:
        inner_dict = {}
        banks = []
        for transaction in transactions:
            if len(transaction[0]) > 0:
                if transaction[0][0] == key:
                    if transaction[0][2] not in banks:
                        banks.append(transaction[0][2])
            if len(transaction[1]) > 0:
                if transaction[1][0] == key:
                    if transaction[1][2] not in banks:
                        banks.append(transaction[1][2])

        for bank in banks:
            value = 0
            for transaction in transactions:
                if len(transaction[0]) > 0 and len(transaction[1]) > 0:
                    if transaction[0][0] == key or transaction[1][0] == key:
                        if transaction[0][2] == bank and transaction[1][2] == bank:
                            value = value + transaction[2]
                else:
                    if len(transaction[0]) == 0:
                        if transaction[1][0] == key:
                            if transaction[1][2] == bank:
                                value = value + transaction[2]

                    if len(transaction[1]) == 0:
                        if transaction[0][0] == key:
                            if transaction[0][2] == bank:
                                value = value + transaction[2]

            inner_dict[bank] = value

        counted_trans[key] = inner_dict

    return counted_trans

def most_internal_transfers_sum(transfers):
    most_internal = {}
    for keys, values in transfers.items():
        hightest = max(values.values())
        for key, value in values.items():
            if value == hightest:
                most_internal[keys] = key

    return most_internal

from funcK3 import *

transactions = read_transactions('transactions.csv')
remove_invalid(transactions)
transactions_rem = remove_atm(transactions)
transfers = count_internal_transfers(transactions_rem)

transfers_most = most_internal_transfers(transfers)
keys = sorted(transfers_most.keys())
for k in keys:
    print(k, ':', transfers_most[k])
from funcK3 import *

transactions = read_transactions("transactions.csv")
transactions_rem = remove_foreign(transactions)
transfers = domestic_internal_transfers(transactions_rem)

transfers_most = most_internal_transfers_sum(transfers)
keys = sorted(transfers_most.keys())
for k in keys:
    print(k, ':', transfers_most[k])
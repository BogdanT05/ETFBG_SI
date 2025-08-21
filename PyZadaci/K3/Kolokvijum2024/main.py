from func import *

best_prices = find_best_prices('ulaz.txt')
for keys,values in best_prices.items():
    print('{}-{}'.format(keys, values))
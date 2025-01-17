from func import *

#V1 i V2 su isti zadaci ne razumem zasto je odvojeno.

places, candidates = read_candidates()
votes = read_votes()
result = obtain_results(places, candidates, votes)
print_result(result)

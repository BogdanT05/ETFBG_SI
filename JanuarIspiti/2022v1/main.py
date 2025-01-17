from func import *

places, candidates = read_candidates()
votes = read_votes()
result = obtain_results(places, candidates, votes)
print_result(result)

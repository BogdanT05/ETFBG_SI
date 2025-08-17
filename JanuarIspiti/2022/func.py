def read_candidates():
    candidates = int(input())
    id = input().split(" ")
    id = [int(i) for i in id]

    return candidates, id

def read_votes():
    votes = []

    while True:
        vote = input()
        if vote == "":
            break

        vote = vote.split(", ")
        vote = [int(i) for i in vote]
        votes.append(vote)

    return votes

def obtain_results(places, candidates, votes):
    counter_list = []
    for candidate in candidates:
        counter = 0
        for vote in votes:
            if candidate in vote:
                counter += 1
        counter_list.append(int(counter))

    while len(candidates) > places:
        counter_list_sorted = []
        least_votes = min(counter_list)
        indeks = []
        for i in range(len(counter_list)):
            if counter_list[i] != least_votes:
                counter_list_sorted.append(counter_list[i])
                indeks.append(i)
        counter_list = [i for i in counter_list_sorted]
        candidates = [candidates[i] for i in indeks]

    results = []
    for i in range(len(counter_list)):
        id = []
        res = []
        for candidate in range(len(candidates)):
            if counter_list[i] == counter_list[candidate]:
                id.append(candidates[candidate])
        res.append(sorted(id))
        res.append(counter_list[i])
        if res not in results:
            results.append(res)

    results_sorted = results[::-1]
    return results_sorted

def print_result(result):
    for res in range(len(result)):
        print(*result[res][0], sep=",", end="")
        if res == len(result)-1:
            print(f":{result[res][1]}", end="")
        else:
            print(f":{result[res][1]}")

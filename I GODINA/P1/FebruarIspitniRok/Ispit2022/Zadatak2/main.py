from func import *

stats = read_stats(input())
by_position = group_by_position(stats)
sorted_postions = dict(sorted(by_position.items(), key=lambda x: x[1], reverse=True))

for key in list(sorted_postions.keys()):
    if key is not list(sorted_postions.keys())[-1]:
        print(f"{key}: {sorted_postions[key]:.2f}")
    else:
        print(f"{key}: {sorted_postions[key]:.2f}", end='')

write_players(stats, by_position)

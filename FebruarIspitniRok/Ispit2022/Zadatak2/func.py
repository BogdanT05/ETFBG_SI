import re

def read_stats(filename):
    list_of_stats = []
    with open(filename, "r") as f:
        text = f.read()
        pattern = re.compile(r"[a-zA-Z]+ ([a-zA-Z]+\s*[a-zA-Z.-]*), ([a-zA-Z],*\s*[a-zA-Z]*,*\s*[a-zA-Z]*), (\d+), (\d+\.*\d*)")
        matches = pattern.findall(text)

        for match in matches:
            pos = match[1].split(',')
            pos = [x.strip() for x in pos]

            list_stat = [match[0], pos, int(match[2]), int(round(float(match[3])*int(match[2])))]
            list_of_stats.append(list_stat)

        return list_of_stats

def group_by_position(stats):
    stats_dict = {}
    positions = []
    for i in stats:
        for j in i[1]:
            if j not in positions:
                positions.append(j)

    for position in positions:
        avg_points = 0
        avg_matces = 0
        for stat in stats:
            if position in stat[1]:
                 avg_points += stat[3]
                 avg_matces += stat[2]

        stats_dict[position] = avg_points/avg_matces

    return stats_dict

def write_players(stats, by_position):
    by_position_keys = list(by_position.keys())
    max_pos = by_position_keys[0]

    for pos in by_position:
        if by_position[pos] > by_position[max_pos]:
            max_pos = pos

    players_to_write = []
    for stat in stats:
        if max_pos in stat[1]:
            players_to_write.append(stat[0])

    with open('players.txt', 'w') as f:
        for player in sorted(players_to_write):
            if player is not sorted(players_to_write)[-1]:
                f.write(f"{player}\n")
            else:
                f.write(f"{player}")

from enum import nonmember


def compact_format(period):
    compact_period = period
    for p in range(len(period)):
        if period[p] == "0":
            compact_period = compact_period.replace(f"{period[p-1]}0", "")

    for_removal = []
    for c in range(0, len(compact_period)-2, 2):
        if compact_period[c] == compact_period[c+2]:
            for_removal.append(c+2)

    final_str = ""
    for c in range(len(compact_period)):
        if c not in for_removal:
            final_str += compact_period[c]

    return final_str

def read_game(filename):
    with open(filename, 'r') as f:
        game_data = f.read().split('\n')

    game_data.pop(-1)
    game_data_compact = [compact_format(game) for game in game_data]

    return game_data_compact

def highest_streaks(game):
    print(game)

    highest_streak_v = 0
    highest_streak_h = 0
    ending_team = None
    for period in game:

        for p in range(len(period)):

            if period[p] == 'v':
                first_iteration = True
                if ending_team != 'v' and period[0] != 'v':
                    streakv = 0
                try:
                    while period[p] != 'h':
                        if first_iteration:
                            first_iteration = False
                        else:
                            streakv += int(period[p])
                        p += 1
                    if streakv > highest_streak_v:
                        highest_streak_v = streakv

                except IndexError:
                    continue

            if period[p] == 'h':
                if ending_team != "h" and period[0] != 'h':
                    streakh = 0

                first_iteration = True
                try:
                    while period[p] != 'v':
                        if first_iteration:
                            first_iteration = False
                        else:
                            streakh += int(period[p])
                        p += 1
                    if streakh > highest_streak_h:
                        highest_streak_h = streakh

                except IndexError:
                    continue

        for l in period[::-1]:
            if l == "v":
                ending_team = l
                break
            if l == "h":
                ending_team = l
                break



    print(highest_streak_v, highest_streak_h)


highest_streaks(read_game('game.txt'))
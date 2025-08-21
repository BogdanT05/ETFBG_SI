
def read_heights():
    initial_state = input().split()
    initial_state = [int(x) for x in initial_state]
    return initial_state

def print_board(heights):
    board = []

    for i in range(max(heights)):
        empty_row = []
        for j in range(len(heights)):

            empty_row.append(0)
        board.append(empty_row)

    for i in range(len(board), 0, -1):
        row = []
        for h in heights:
            if h > 0:
                row.append(1)
            else:
                row.append(0)

        heights = [x-1 for x in heights]
        board[i-1] = row

    for i in board:
        print(*i,sep=" " ,end="")
        if i is not board[-1]:
            print()

def update_heights(heights, column):
    heights_update = [heights[i]+1 if i == column else heights[i] for i in range(len(heights))]
    heights.clear()

    for i in heights_update:
        remove_layer = True
        if i == 0:
            remove_layer = False
            break

    if remove_layer:
        heights_update = [x-1 for x in heights_update]

    for i in heights_update:
        heights.append(i)

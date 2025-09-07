from func import *

heights = read_heights()
columns = []
while True:
    column = input()

    if column == "":
        break

    columns.append(int(column))

print("INITIAL")
print_board(heights)

for column in columns:
    print()
    print(f"AFTER {column}")
    update_heights(heights, column)
    print_board(heights)

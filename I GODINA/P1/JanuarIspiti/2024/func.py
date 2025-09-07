def read_data():
    shoes = input().split()
    shoes_start = int(shoes[0])
    quantity = shoes[1].split(",")
    quantity = [int(i) for i in quantity]
    shoes_quantity = []

    for shoe in quantity:
        cur_shoe = [shoes_start, shoe]
        shoes_start += 1
        shoes_quantity.append(cur_shoe)

    return shoes_quantity

def update_data(data):
    size = []
    sell_buy = []

    while True:
        enter = input()
        if enter == "":
            break

        size.append(int(enter.split()[0]))
        sell_buy.append(int(enter.split()[1]))

    for d in data:
        for shoe in range(len(size)):
            if size[shoe] in d:
                neg_or_pos = d[len(d)-1] + sell_buy[shoe]
                if neg_or_pos < 0:
                    d.append(d[len(d)-1])
                else:
                    d.append(neg_or_pos)
            else:
                d.append(d[len(d)-1])

    return data

def write_data(data):
    for i in range(len(data)):
        for j in range(len(data[i])):
            if j != len(data[i])-1:
                print(data[i][j], end="")
                print("  ", end="")
            else:
                if i != len(data)-1:
                    print(data[i][j], end="\n")
                else:
                    print(data[i][j], end="")

import re

def read():
    input_text = []
    pattern = re.compile(r"(.{5})-(\d) (\d{1,3}.\d+)")
    while True:
        line = input()
        if line == "":
            break

        matches = pattern.match(line)

        line_el = (matches.group(1), int(matches.group(2)), float(matches.group(3)))
        input_text.append(line_el)

    return input_text

def arrange(testData, numberOfPages):
    dictOfData = {}

    for data in testData:
        dictOfData[data[0]] = []

    for key in dictOfData.keys():
        inner_list = []
        counter = 0
        while counter < numberOfPages:
            lenOfInnerList = len(inner_list)
            for data in testData:
                if data[0] == key and data[1] == counter:
                    inner_list.append(data[2])

            if len(inner_list) == lenOfInnerList:
                inner_list.append(-1)

            counter += 1

        dictOfData[key] = inner_list

    return dictOfData

import func as f

raspored_lifta = f.process_demands(f.remove_invalid(f.read_demands()))

str_raspored_lifta = ""
for i in raspored_lifta:
    str_raspored_lifta += str(i)
    str_raspored_lifta += " "

print(str_raspored_lifta[:-1])

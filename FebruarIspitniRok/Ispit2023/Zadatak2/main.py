from func import *

polls = read_polls("input.txt")
polls_dict = process_polls(polls)
write_polls(polls_dict)
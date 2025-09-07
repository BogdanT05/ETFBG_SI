from func import *

clientTimes = readClientTimes()
window1 = []
window2 = []
work ( clientTimes,window1, window2 )

writeQueue(window1)
writeQueue(window2)
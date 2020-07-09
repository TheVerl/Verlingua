from datetime import datetime
import os
import sys

dir = os.getcwd()
history = dir + "/constructer/history.txt"
no = dir + "/constructer/no"

with open(history, 'r') as f:
    lines = f.read().splitlines()
    lastLine = lines[-1]
    oldBuildNo = int(lastLine.split()[-1])

now = datetime.now()
time = now.strftime("%c")
newBuildNo = oldBuildNo + 1
string = time + " : Build " + str(newBuildNo) + "\n"

f = open(history, 'a')
f.write(string)
f.close()

f = open(no, 'w')
f.write(str(newBuildNo))
f.close()
    

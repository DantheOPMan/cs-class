outputFile = open("output.txt", "r")
file = outputFile.read()
namesList = file.split()
outputList = []
outputString = ""
count = 0
for word in namesList:
    if '0x' == word[0:2]:
        outputList.append(word)
        outputString += word[2:len(word)]

print(outputString)



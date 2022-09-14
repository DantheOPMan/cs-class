#Daniel Yankovich
#CS 100 2021F Section H01 
#HW 09, November 11, 2021
def file_copy(inputFile, outputFile):
    input = open(inputFile)
    f = open(outputFile, "x")
    f.write(input.read())
    input.close()
    f.close()

file_copy('created_equal.txt', "copy.txt")
copy = open("copy.txt")
print(copy.read())
copy.close()
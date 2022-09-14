#Daniel Yankovich
#CS 100 2021F Section H01 
#HW 06, October 25, 2021

def hasFinalLetter(strlist, letters):
    allStrings = []
    for word in strlist:
        if word[-1] in letters:
            allStrings.append(word)
    return allStrings

print(hasFinalLetter(["poggers", "your mom", "hello", "nice", "dantheopman rules", "vtrue", "on god"], ["e", "g","s"]))
print(hasFinalLetter(["poggers", "your mom", "hello", "nice", "dantheopman rules", "vtrue", "on god"], ["m","d"]))
print(hasFinalLetter(["poggers", "your mom", "hello", "nice", "dantheopman rules", "vtrue", "on god"], ["l"]))

def isDivisible(maxInt, twoInts):
    answer = []
    for i in range(1,maxInt):
        if i % twoInts[0] == 0 and i % twoInts[1] == 0:
            answer.append(i)
    return answer

print(isDivisible(155, [3, 8]))
print(isDivisible(23, [3, 5]))
print(isDivisible(23, [4, 9]))


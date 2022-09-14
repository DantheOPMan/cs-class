#Daniel Yankovich
#CS 100 2021F Section H01 
#HW 09, November 14, 2021

def initialLetters(wordList):
    wordDictionary = {}
    for word in wordList:
        first = word[0:1]
        if first in wordDictionary.keys():
            if word not in wordDictionary[first]:
                wordDictionary[first].append(word)
        if first not in wordDictionary.keys():
            wordDictionary[first] = [word]
    return wordDictionary


horton = ['I', 'say', 'what', 'I', 'mean', 'and', 'I', 'mean', 'what', 'I', 'say']
print(initialLetters(horton))
def initialLetterCount(wordList):
    wordDictionary = {}
    for word in wordList:
        first = word[0:1]
        if first in wordDictionary.keys():
            wordDictionary[first] +=1
        if first not in wordDictionary.keys():
            wordDictionary[first] = 1
    return wordDictionary

horton = ['I', 'say', 'what', 'I', 'mean', 'and', 'I', 'mean', 'what', 'I', 'say']
print(initialLetterCount(horton))
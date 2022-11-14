

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
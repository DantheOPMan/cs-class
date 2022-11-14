def twoWords(wordLength,firstLetter):
    wordOne = ""
    wordTwo = ""

    while(wordLength != len(wordOne)):
        wordOne = input("Enter a " + str(wordLength) + "-letter word please: ")

    while( wordTwo[0:1].upper() != firstLetter.upper()):
        wordTwo = input("Enter a word beginning with " + firstLetter + " please: ")

    return [wordOne, wordTwo]
print(twoWords(4, 'B'))
print(twoWords(7, 'f'))

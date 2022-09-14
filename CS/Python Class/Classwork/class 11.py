


def phonesWithGivenArea(phones, targetAreaCode):
    phoneList = phones.split(",")
    phonesWithArea=[]
    for phone in phoneList:
        if(phone.startswith(str(targetAreaCode))):
            print(phone)
            phonesWithArea.append(phone)
    return phonesWithArea

phones = "971-251-1234,800-123-4567,971-345-2313,201-235-2351"

print(phonesWithGivenArea(phones, 971))


def namesInA(names):
    nameList = names.split(" ")
    for name in nameList:
        if "a" in name.lower():
            return name
    return " "

names = "Don Joe Josh Annery Sophia Charles Hal"
print(namesInA(names))
names = "Don Joe Josh Hal"
print(namesInA(names))
names = "Don Joe Josh Jeffrey"
print(namesInA(names))


def wordsStats(paragraph):
    sentences = paragraph.split("\n")
    lengthOfLine = []
    for sentence in sentences:
        words = sentence.split(" ")
        lengthOfLine.append(len(words))
    return lengthOfLine

paragraph = "Hello my name is inigo montoya\nYou killed my father\nPrepare to die i"
print(wordsStats(paragraph))


def wordsInVowels(paragraph):
    sentences = paragraph.split("\n")
    vowelCount = []
    sentenceCount = 0
    for sentence in sentences:
        vowelCount.append(0)
        words = sentence.split(" ")
        for word in words:
            if (word[0].lower() in "aeiou"):
                words = sentence.split(" ")
                vowelCount[sentenceCount]+=1
        sentenceCount+=1
    return vowelCount

print(wordsInVowels(paragraph))
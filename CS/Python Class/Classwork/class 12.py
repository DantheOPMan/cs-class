def numDigits(num):
    digits = 0
    while(num>=1):
        num = num / 10
        digits+=1
    return digits
import random
def keepRolling():
    attempts = 1
    dieValue = random.randint(1,6)
    while(dieValue != 6):
        dieValue = random.randint(1,6)
        attempts += 1
    return attempts


def firstLongWordInLine(text, length):
    sentences = text.split('\n')
    outputs = []
    count = 0
    for sentence in sentences:
        words = sentence.split()
        output = ""
        for word in words:
            if(len(word)>=length):
                output = word
                break
        outputs.append(output)
    return outputs

print(numDigits(11111))
print(keepRolling())

text = "it is what it is\nexam is not online\nexam is cummulative"
print(firstLongWordInLine(text, 5))

def file_stats(fileName):
    f = open(fileName, 'r')
    text = f.read()
    sentences = text.count("\n")+1
    print(sentences)
    print("lines " + str(sentences))
    words = text.split()
    
    print("words " + str(len(words)))
    text = text.replace("\n","")
    print("characters " + str(len(text)))
    f.close()

file_stats('created_equal.txt')

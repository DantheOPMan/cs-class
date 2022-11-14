
def repeatWords(in_file, out_file):
    inputText = open(in_file)
    lines = inputText.read()
    lines = lines.lower()
    lines = lines.replace("!","")
    lines = lines.replace(".","")
    lines = lines.splitlines()
    outputText = []
    for line in lines:
        words = line.split()
        outputText.append("")
        wordsList = []
        for word in words:
            if(words.count(word) > 1 and not word in wordsList):
                 outputText[len(outputText)-1] += word + " "
                 wordsList.append(word) 
    f = open(out_file, "x")
    output = ""
    print(outputText)
    for line in outputText:
        output +=line +"\n"
    f.write(output)
    f.close()
    inputText.close()

repeatWords("catinthehat.txt", "catinthehatwords.txt")
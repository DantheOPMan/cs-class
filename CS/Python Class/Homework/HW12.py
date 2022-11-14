
def safeOpen(filename):
    try:
        f  = open(filename, 'r')
        text = f.read()
        f.close()
        return text
    except:
        return None

def safeFloat(x):
    try:
        number=  float(x)
        return(number)
    except:
        return 0.0

print(safeOpen('catinthehat.txt'))
print(safeOpen('hi.txt'))
print(safeFloat("hello"))
print(safeFloat("12.3"))
import math
days = 365
months = 12
year = 1

height = 150.55
length = 160.89
width = 123.31

languageAmerica = "English"
languageIsrael = "Hebrew"
languageJapan = "Japanese"

# 1-1 1. If I leave out one of the paranthesis I would get an error breaking the code because python doesn't know how to handle print or how it should output with that syntax, SyntaxError: Missing parentheses in call to 'print'. Did you mean print("hello")?
#print "hello"
#1-1 2. If you leave out a quotation, the code doesn't know where the string ends and causes the rest of the code not to run. SyntaxError: EOL while scanning string literal
#print("hi)
#1-1 3. Basically python just ignores the whitespace between the symbols and if there's nothing between it counts that nothing as 0, thus ignoring all the + signs in between
"""ans = 2+++-2
print(ans)
ans = 2+++2
print(ans)
"""
#1-1 4 Python throws the error SyntaxError: leading zeros in decimal integer literals are not permitted; use an 0o prefix for octal integers when you lead with a 0, sot hey aren't allowed in the syntax
#print(05)
#1-1 5 Python throws an invalid syntax error.
#print(2 2)

#1-2 1
print(42*60 + 42)

#1-2 2
print(10/1.61)

#1-2 3
print(str(int((42*60+ 42)/(10/1.61) / 60))+ " minutes " + str((42*60+ 42)/(10/1.61) % 60) + " seconds")
print(str((10/1.61) / ((42+ 42/60)/60))+ " miles per hour" )

#2-2 42 = n is not allowed because you can't assing a value to a literal value
#x=y=1 is allowed and assigns both their value as 1
#if you put a semicolon at the end the code still runs normally
#if you put a period at the end you get a syntax error
#it doesnt work because it reads xy as the name of a new variable not them individually

#2-2 1
print(4/3*pow(5,3)*math.pi)

#2-2 2
print("$" + str(24.95 *.6 * 60 + 3 + .75*59))

#2-2 3
endTime = (6*60 + 52) + (8+ 15/60)*2 + (7 + 12/60)*3
print(str(int(endTime/60)) + " : " + str(int(endTime%60)))


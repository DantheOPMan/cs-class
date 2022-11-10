    #Daniel Yankovich
#CS 100 2021F Section H01 
#HW 04, October 4, 2021
import time
import turtle

a = 3
b = 4
c = 5

if a < b:
    print("OK")
else:
    print("NOTOK")
if c < b:
    print("OK")
else:
    print("NOTOK")
if a + b == c:
    print("OK")
else:
    print("NOTOK")
if (a^2 + b^2) == c^2:
    print("OK")
else:
    print("NOTOK")

paper = turtle.Screen()
pen = turtle.Turtle()
colorInput = input("What color? ")
lineWidth = int(input("What line width? "))
lineLength = int(input("What line length? "))
shape = input("Line, triangle, or square? ")
sides = 0

pen.color(colorInput)
pen.width(lineWidth)

if shape == "line":
    sides = 1
elif shape == "triangle":
    sides = 3
elif shape == "square":
    sides = 4

for i in range(sides):
    pen.forward(lineLength)
    pen.right(360 / sides)
time.sleep(5000)

#Daniel Yankovich
#CS 100 2021F Section H01 
#HW 03, September 9, 2021

import turtle
import math

paper = turtle.Screen()

pen = turtle.Turtle()

pen.up()
pen.setpos(-200,100)
pen.down()
sides = 3
angle = 360 / sides
sideLength = 100

for i in range(3):
    for x in range(sides):
        pen.forward(sideLength)
        pen.right(angle)
    pen.up()
    pen.forward(sideLength + 60)
    pen.down() 
    sides +=1
    angle = 360/sides

count = 1
while count <= 4:
    pen.circle(50 * count)
    pen.up()
    pen.right(90)
    pen.forward(50)
    pen.left(90)
    pen.down() 
    count+=1

print(math.perm(100))
print(math.log2(1000000))
print(math.gcd(63, 49))
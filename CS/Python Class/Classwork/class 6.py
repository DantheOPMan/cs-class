'''import turtle
paper = turtle.Screen()

pen = turtle.Turtle()
pen.up()
pen.setpos(-500,150)
angle = 120
amount = 50
pen.down()

def draw(amount):
    for i in range(105):
        pen.fd(amount)
        pen.right(angle)
        pen.fd(amount)
        pen.right(angle)
        pen.fd(amount)
        pen.right(angle)
        pen.forward(amount)
        amount = amount * 1.2 

draw(amount)
pen.up()
pen.setpos(-500,-150)
pen.setheading(20)
pen.down()
draw(amount)

import turtle

paper = turtle.Screen()

pen = turtle.Turtle()
pen.up()
pen.setpos(0,-250)
sides = 15
angle = 120
amount = 10
heading = 360/sides
pen.down()
for i in range (sides):
    pen.setheading(heading)
    heading += 360/sides
    for i in range(sides):
        pen.fd(amount)
        pen.right(angle)
        pen.fd(amount)
        pen.right(angle)
        pen.fd(amount)
        pen.right(angle)
        pen.forward(amount)
    
'''
import turtle

paper = turtle.Screen()

pen = turtle.Turtle()
pen.up()
pen.setpos(0,0)
pen.down()
first = int(input("First amount of sides: "))
second = int(input("second amount of sides: "))
length = int(input("length of each side: "))
i = first

while i < second:
    angle = 360/i
    for x in range(i):
        pen.fd(length)
        pen.right(angle)
    i+=1
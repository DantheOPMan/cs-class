import turtle
import time
'''paper = turtle.Screen()
pen = turtle.Turtle()
pen.up()
pen.color("purple")
y=0
x = 0
amount = 50
angle = 60
forward = 20
pen.setpos(-200,0)
while y<3: 
    pen.down()
    while x<4 :
        pen.forward(amount)
        pen.rt(angle)
        x+=1
    pen.up()
    pen.forward(amount + forward)
    x=0
    y+=1
time.sleep(5000)'''

paper = turtle.Screen()

pen = turtle.Turtle()
pen.up()
pen.setpos(-350,150)
angle = 120
amount = 60

pen.down()
pen.fd(amount)
pen.right(angle)
pen.fd(amount)
pen.right(angle)
pen.fd(amount)
pen.right(angle)

pen.fd(amount)
pen.fd(amount*2)
pen.right(angle)
pen.fd(amount*2)
pen.right(angle)
pen.fd(amount*2)
pen.right(angle)

pen.fd(amount*2)
pen.fd(amount*3)
pen.right(angle)
pen.fd(amount*3)
pen.right(angle)
pen.fd(amount*3)
pen.right(angle)

pen.fd(amount*3)
pen.fd(amount*4)
pen.right(angle)
pen.fd(amount*4)
pen.right(angle)
pen.fd(amount*4)
pen.right(angle)

pen.fd(amount*4)
pen.fd(amount*5)
pen.right(angle)
pen.fd(amount*5)
pen.right(angle)
pen.fd(amount*5)
pen.right(angle)
time.sleep(5000)
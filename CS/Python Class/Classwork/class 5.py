import turtle

paper = turtle.Screen()
pen = turtle.Turtle()
pen.up()
pen.setpos(0,0)
pen.down()
pen.speed(1000)

angle = int(input("What is the angle: "))
amount = int(input("What is the length: "))
headingChange = int(input("How much should heading change by: "))
step = int(input("how much should the size step by?: "))
sides = 360/(int(angle))
heading = 0

def squares():
    side = int(sides)
    while side > 0:
        pen.forward(int(amount))
        pen.right(int(angle))
        side -= 1

run = True
while run == True:
    pen.setheading(heading)
    heading -= int(headingChange)
    squares();
    amount = int(amount) + step
    if int(amount) > 1000:
        run = False

counter = 0
for number in range(0,100):
    if counter < 10:
        if number % 3 == 0:
            print(number)
            counter += 1
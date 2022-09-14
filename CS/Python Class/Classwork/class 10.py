'''def getInitials (initials):
    output = ""
    for i in initials:
        output += i[0]
    return output

initials = ["Daniel","Charles","Nick"]

print(getInitials(initials))'''

import turtle

s = turtle.Screen()
p = turtle.Pen()
def spiral(p,radius,angle):
    p.speed(0)
    p.down()
    p.fd(radius)
    p.bk(radius)
    p.right(angle)

def drawMultiple(p,x,radius,angle):
    for i in range(0,x):
        spiral(p,radius,angle)
        radius += 10

drawMultiple(p,100, 30,10)
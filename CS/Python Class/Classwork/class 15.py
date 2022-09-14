import math
class Point:
    def __init__(self, x_coor, y_coor):
        self.x = x_coor
        self.y = y_coor

    def getCoordinates(self):
        return (self.x, self.y)

    def move_to(self, newX, newY):
        self.x = newX
        self.y = newY
    
    def distanceTo(self, otherPoint):
        return math.sqrt((self.x - otherPoint.x ** 2) + (self.y - otherPoint.y**2))


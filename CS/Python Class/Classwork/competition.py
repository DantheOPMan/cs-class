class KinematicsCalculator:
    def __init__(self, velocityInitial, velocityFinal, acceleration):
        self.velocityInitial = velocityInitial
        self.velocityFinal = velocityFinal
        self.acceleration = acceleration

    def speed(self, time):
        return (self.velocityInitial + self.acceleration * time)

    def displacement(self, time):
        return ((self.velocityInitial + self.velocityFinal) / 2 * time )

calc = KinematicsCalculator(3, 12, 2)

print(calc.speed(5))
print(calc.displacement(5))

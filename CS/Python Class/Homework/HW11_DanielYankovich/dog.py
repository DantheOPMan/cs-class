class Dog:
    def __init__(self, name, breed):
        self.name = name
        self.breed = breed
        self.tricks = []
    def teach(self, trick):
        self.tricks.append(trick)
        print(self.name + " knows " + trick)
    

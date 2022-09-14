#Daniel Yankovich
#CS 100 2021F Section H01 
#HW 02, September 9, 2021

grades = ['A', 'F', 'C', 'F', 'A', 'B', 'A', 'C', 'A', 'B']
double = [grades[0]]
frequency = [0]
for grade in grades:
    if grade in double:
        frequency[double.index(grade)] += 1
    else:
        frequency.append(1)
        double.append(grade)
print(double)
print(frequency)

dog_breeds = ["collie", "sheepdog", "Chow", "Chihuahua"]
herding_dogs = dog_breeds[0:2]
print(herding_dogs)
tiny_dogs = dog_breeds[-1:]
print(tiny_dogs)
if "Persian" in dog_breeds:
    print(True)
else:
    print(False)
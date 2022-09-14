#create a program that takes a list of 5 exam scores by adding them one at a time.
#The program calculates and prints to the screen the average score, highest score, lowest score, and the number of perfect scores.
import math
scores = []
x=0
while x<5:
    scores.append(int(input("Enter score: ")))
    x+=1



print("Average score: " + str(sum(scores)/len(scores)))
print("Highest score: " + str(max(scores)))
print("Lowest score: " + str(min(scores)))
print("Perfect score: " + str(scores.count(100)))


p1 = ["hello","whats","up"]
p2 = ["your", "mom", "is"]
p3 = p2[0:2] + p1[-1:]
#help(p1)
print(p3)
print(pow(15,4)*math.pi)
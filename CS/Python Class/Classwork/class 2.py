myList = []
print(type(myList))
myList = [10,10.5, True, "hello", [4, "five"]]
print(myList)
myList = myList + [1,2,3]
print(myList)
secondList = [1,2,3] *5
print(secondList)
print(10 in myList)
print(4 in myList)
print("hello" in myList)
print(myList[1:4])
print (secondList[5:9])
myList[0] = 100
print(myList)
print(myList[5]);
print(myList[4][1]);
myList = [10,10.5, True, "hello", [4, "five"]]
print(myList[-1])
print(myList[-1:][-1][-1:])

adder = [1,2,3,4,5,6,7,8]
print(sum(adder))
print(min(adder))
print(max(adder))
print(sum(adder)/len(adder))
adder.append(15);
adder.append(23);
adder.append(12);
print(sum(adder))
print(min(adder))
print(max(adder))
print(sum(adder)/len(adder))

newList = [1,7,1,5]
newData = newList.count(1)*5+1000
print(newData)
print(newList)
answer = newList.append(100)
print(answer)
print(newList)
newList.sort(reverse=False)
print(newList)
newList.sort(reverse=True)
print(newList)
print(newList)
data = 5, 6
print(data)
def findOdds(x):
    
    count = 0
    for i in x:
        if i % 2 == 1:
            count+=1

    return count

y = [1,2,3,61,24,17]
print(findOdds(y))


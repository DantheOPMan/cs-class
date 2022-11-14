months = ["January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December"]
for i in months:
    if i[0] == "J":
        print(i)

for i in range(100):
    if i % 2 == 0 and i % 5 == 0:
        print(i)

horton = "A person's a person, no matter how small."
vowels = "aeiouAEIOU"

for i in horton:
    if i in vowels:
        print(i)    
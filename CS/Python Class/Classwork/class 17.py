def double(y):
    x= 2
    y *=x
    print('inside double', 'x = ', x, 'y = ', y)

x,y = 3,4
print('outside double', 'x = ', x, 'y = ', y)
double(y)
print('after double', 'x = ', x, 'y = ', y)
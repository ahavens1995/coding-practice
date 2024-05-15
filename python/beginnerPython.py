print ("Hello, World!")

# Basic Data Types

# Integers, default is base 10
a = 1
b = 10
# binary
c = 0b101010111 #343 in decimal
print(c)
# octal
d = 0o454312 #153802 in decimal
print(d)
# hex
e = 0xac4d
print(e)

my_num = '12345'
int(my_num) #convert string to number
my_num2 = int(my_num)
my_num2 + b

#show what type a variable is
print(type(a))

print(bin(my_num2))
print(oct(my_num2))
print(hex(my_num2))

# Floats
# any number with a decimal point, division results will be a float, can be defined with scientific notations
a = 4.2
print(type(a))
b = 4.0
c = 10
d = 4
e = c / d
print(e) # prints a float
d = 5
f = c / d
print(f) # prints a float
g = c // d #creates an integer division
print(g)
h = c // 4
print (h)
i = float (3)
print(i)
j = 4e3
print (j)
k = 4e-3
print(k)
#floating point arithmetic not working
a = 0.2
b = 0.1
c = a + b
print(c) #prints 0.30000000000000004

# Complex Numbers
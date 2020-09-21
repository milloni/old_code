numbers = []
length = input("List length?: ")
length = int(length)
input_line = input("numbers: ")
for x in input_line.split():
    numbers.append(int(x))
sorted_numbers = []

while len(numbers) != 0:
    sorted_numbers.append(min(numbers))
    index = numbers.index(min(numbers))
    numbers.pop(index)
print(sorted_numbers) 

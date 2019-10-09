#!/usr/bin/python

for letter in 'Python':     # First Example
   if letter == 'h':
      continue
   print 'Current Letter :', letter

var = 10                    # Second Example
while var > 0:
   var = var -1
   if var == 5:
      continue
   print 'Current variable value :', var
print "Good bye!"

numbers = (1, 2, 3,4,5,6,7)
num_sum = 0
count = 0
for x in numbers:
        num_sum = num_sum + x
        count = count + 1
        print(num_sum)
        if count == 5:
                break

while True:
    print "Hello World"

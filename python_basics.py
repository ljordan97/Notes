#libraries used in these notes
import random

############################################## #
											     #
############################################## #
            #
# C L A S S  #
			#			
############################################## #
											     #
############################################## #

#define class
class Facade:
  pass

#instantiate class, to create class object
cool_instance = CoolClass()
	#if this variable is reassigned, say to another class instance
	#python will garbage collect old class

#getting type of class object
print(type(cool_instance))
	# prints "<class '__main__.CoolClass'>"
		#__main__ means "this file we're running"
			#so this shows that the class was defined here
			# would show imported library.class_name for others

#class variable: the same for every instance of the class
	#created in class definition
class Musician:
  title = "Rockstar"
 
drummer = Musician()
print(drummer.title)

#assign an instance variable, best to do in constructor, with parameters
fake_dict1.fake_key = "This works!"

#check attributes of an object
hasattr(object, “attribute”)

#retrieve, and supply default for, attributes of an object
getattr(object, “attribute”, default)

#show all attributes
dir(object)

#create string representation of class object, for debugging
  def __repr__(self):
    return self.name

### M E T H O D S ###

#methods are functions that are defined as part of a class
	#always take in the object that calls them as 1st arg
		#name this arg "self"
	#can reference class variables as Class.variable 
		#or instance variables as self.variable

# dunder methods
#constructors: used to prepare an object that is being instantiated
class Shouter:
	def __init__(self):
		print("HELLO?!")

shout1 = Shouter() #will print HELLO?! cause its in the constructor
				#any args passed in instantiation will be 
				#received by the __init__ method


#inheritance, e.g. will keep same constructor
class User:    #base, or parent class
  is_admin = False
  def __init__(self, username)
    self.username = username
 
class Admin(User):   #subclass, or child class
  is_admin = True

  	#multiple inheritance is possible. depth first, left to right

#check if one class is a subclass of the other
issubclass(ZeroDivisionError, Exception)
	#true if 1st arg is subclass of the 2nd

	#when creating new exceptions, it's useful to inherit
	#from another, such as Exception
	#this way, all child exceptions can be caught by catching
	#KitchenException
class KitchenException(Exception):
  """
  Exception that gets thrown when a kitchen appliance isn't working
  """
 
class MicrowaveException(KitchenException):
  """
  Exception for when the microwave stops working
  """
 
class RefrigeratorException(KitchenException):
  """
  Exception for when the refrigerator stops working
  """

def get_food_from_fridge():
  if refrigerator.cooling == False:
    raise RefrigeratorException
  else:
    return food

#overriding inherited methods
	#all you have to do is just write another definition

#extending methods with super(), which returns a proxy obj
class Sink:
  def __init__(self, basin, nozzle):
    self.basin = basin
    self.nozzle = nozzle
 
class KitchenSink(Sink):
  def __init__(self, basin, nozzle, trash_compactor=None):
    super().__init__(basin, nozzle)
    if trash_compactor:
      self.trash_compactor = trash_compactor

#reason for extending classes
#If we have a play_game() function that takes an instance of 
#Chess or Checkers, it could call the .play() method without 
#having to check which class the object is an instance of.
	#when two classes implement the same method names and attr
	#we say they implement the same interface

#polymorphism: same syntax doing different actions depending on type of data
	#class hierarchies that implement the same interface 
		#can be polymorphic
		#like the different method defs for Checkers or Chess objects

#adding built-in functions to custom classes
__add__ for + functionality

#turn object attribute into an iterator, can now use for loops
def __iter__(self):
    return iter(self.user_list)



############################################## #
											     #
############################################## #
                		  #
# D I C T I O N A R I E S  #
						  #			
############################################## #
											     #
############################################## #


menu = {"avocado toast": 6, "carrot juice": 5, "blueberry muffin": 2}

#add value to dictionary
dictionary[key] = value

#update a dictionary with multiple KVPs
sensors.update({"pantry": 22, "guest room": 25, "patio": 34})

#combine two lists into one dict
students = {key:value for key, value in zip(names, heights)}

#retrieve a value by key, if it exists			USEFUL
	#specity value to return if it doesn't
building_heights.get('Shanghai Tower', 0)

#generate list to operate on all keys in a dictionary
	#convert dict to list using list()
		#preserves only the keys

#get all keys: return a dict_keys object from dictionary (user immutable)
	#can be used in place of a list for iteration
	for student in test_scores.keys():
  		print(student)

#get all values: return a dict_values object
	for score_list in test_scores.values()

#get all key-value pairs: return dict_list object
	for company, value in biggest_brands.items():

############################################## #
											     #
############################################## #
                #
# M O D U L E S  #
				#
############################################## #
											     #
############################################## #

#imports
# """
# project
# --> myfile.py
# --> functions
# ----> file.py
# ----> __init__.py
# """
# from functions.file import function1

#get documentation on a module
print(dir(module_name))

#datetime
from datetime import datetime
#get current time
current time = datetime.now()

#random
import random
#get randint
random_list = [random.randint(0,50) for i in range(101)]
#make random choice from list
randomer_number = random.choice(random_list)

#matplotlib
from matplotlib import pyplot as plt
#new plot
plt.plot(numbers_a, numbers_b)
#display plot
plt.show()

#decimal
import decimal import Decimal
#its a custom datatype that's better for arithmetic than float
cost_of_gum = Decimal('0.10')



############################################## #
											     #
############################################## #
                #
# S T R I N G S  #
				#
############################################## #
											     #
############################################## #

#escape characters
double_quote = "\"" 

#formatting
"My favorite song is {song} by {artist}.".format(song=song, artist=artist)

############################################## #
											     #
############################################## #
                  #
#    I N P U T     #
		          #
############################################## #
											     #
############################################## #

#input polling loop
while True:
     try:
        x = int(input("Please enter a number: "))
        break
     except ValueError:
         print("Oops!  That was no valid number.  Try again...")

############################################## #
											     #
############################################## #
                       #
#   F U N C T I O N S   #
		   		       #
############################################## #
											     #
############################################## #

def function_name():
	#tasks
#arguments
	#3 types
	#positional: passed by position in function def / call
	#keyword: passed by name
		#calculate_taxi_price(rate=0.5, discount=10, miles_to_travel=100):
	#default: not passed
		#def calculate_taxi_price(miles_to_travel, rate, discount = 10)

#multiple returns
	#return first_day, second_day, third_day
	#first_day, second_dat, third_day = trip_return_function()


############################################## #
											     #
############################################## #
                #
#   L O O P S    #
				#
############################################## #
											     #
############################################## #

collection = [1, 2, 3, 4]

#for loop, definite iteration
for temporary_variable in collection:
	#temporary_variable stores value of element in collection
	#collection gets iterated through

#for loop to iterate independently from a collection
for temp in range(6): #6 iterations [0...5]
	print("Learning loops!")

#while loops, indefinite iteration, multi-statement elegance
while count <= 3: print(count); count += 1

#list comprehensions
numbers = [2, -1, 79, 33, -45]
doubled = [num * 2 for num in numbers]

#conditional list comprehensions
numbers = [2, -1, 79, 33, -45]
negative_doubled = [num * 2 for num in numbers if num < 0]
# or this
doubled = [num * 2 if num < 0 else num * 3 for num in numbers ]

#breaking loops
#break, stops current iteration right then and there

#skipping iterations
#continue, skips current iteration right then and there

############################################## #
											     #
############################################## #
                #
#   L I S T S    #
				#
############################################## #
											     #
############################################## #

my_list = [3, 2, 1]

#get index of 1st occurance of an element in a list
my_list.index(1) # should return 2 
				 # additional 2 args to limit search to range

#get length of list
length = len(my_list) #starts at 1

#select last item in a list
last_item = my_list[-1]

#select first 3
first_three = my_list[:3]

#select last 3
last_three = my_list[-3:]

#add items to a list
new_list = incomplete_list + [3, 6]

#count item instances in lists
num_i = new_list.count(3)

#sort a list, updates original
new_list.sort() #reverse=True

#sort a list, store it to new list
sorted_list = sorted(new_list)

#insert item to list, 1st arg is index, 2nd arg is element to ins
new_list.insert(2, 55)

#pop items from a list, arg is index to pop, defaults to -1
removed_element = new_list.pop()

#remove items from a list, will remove 1st instance for dupes
my_list.remove("3")

#create a linear list based on a range
	#zero counted, exclusive upper bound as ARG
my_range = range(10) #creates a range object (type), range(0,10)
	#convert range object to list type
	#ARGs for range(inclusive_lower_bound, exslusive_upper, slope)

list(my_range) #[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

#combine multiple lists in order to make list of tuples
# zipper style
names = ["Jenny", "Alexus", "Sam", "Grace"]
heights = [61, 70, 67, 65]

names_and_heights = zip(names, heights) #creates a zip obj
converted_zip_list = list(names_and_heights)




############################################## #
											     #
############################################## #
                #
#  T U P L E S   #
				#
############################################## #
											     #
############################################## #

#like lists in that they are data structures to store 
#multiple pieces of data, but they are immutable

#used to make order of sub-datasets immutable
#e.g. below, data not similar but should be grouped
my_tuple = ("Levi", 23, "Programmer")
my_name = my_tuple[0]
my_job = my_tuple[-1]

#unpacking a tuple, num vars must match num elements
name, age, occupation = my_info
print(name) #"Levi"

one_element_tuuple = (4) #doesn't work
print(one_element_tuple) #prints 4, bc parenthesis in this
						 #context denote an expression
one_element_tuuple = (4,) #correct way



############################################## #
											     #
############################################## #
                #
#    M I S C     #
				#
############################################## #
											     #
############################################## #

#multi-line commenting
#highlight text, ctrl + /

#convert num to string, needed for concatenation
age = 10
str(age)

#multi-line strings
multi = """this
is 
a
multi-line
string"""

#repeat concatenation of string
concat = "this string "
triple_concat = concat * 3

#creating global variables from within a function (not recommended)
global_var = 3
def foo:
	#load the global variabl into scope
	global global_var
	global_var +=2



############################################## #
											     #
############################################## #
                #
#  R A N D O M   #
				#
############################################## #
											     #
############################################## #

#generate randint
rand_int_var = random.randint(1,9)
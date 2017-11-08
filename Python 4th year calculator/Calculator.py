import sys
import pygame
from Tkinter import *
import tkMessageBox


root = Tk()
root.config(bg = "slate grey")
root.title("Calculator")

root.geometry("322x366")

answer = ""

def result():
    
    answer = str(value_of_thing.get())
    answer = answer.split(" ")
    
    if len(answer) == 3:
        
        oneans = answer[0]
        operator = answer[1]
        twoans = answer[2]
    
        oneans = float(oneans)
        twoans = float(twoans)
        
        if operator == "/":
            tkMessageBox.showinfo("Answer", "{0} / {1} = {2}".format(oneans, twoans, oneans / twoans))
         
        elif operator == "x":
            tkMessageBox.showinfo("Answer", "{0} x {1} = {2}".format(oneans, twoans, oneans * twoans))
           
        elif operator == "+":
            tkMessageBox.showinfo("Answer", "{0} + {1} = {2}".format(oneans, twoans, oneans + twoans))
          
        elif operator == "-":
            tkMessageBox.showinfo("Answer", "{0} - {1} = {2}".format(oneans, twoans, oneans - twoans))

    else:
        tkMessageBox.showinfo("Error", "Sorry our calculator can't do that yet!")

def oneclick():
    value_of_thing.insert(INSERT, 1)
    
def twoclick():
    value_of_thing.insert(INSERT, 2)
    
def threeclick():
    value_of_thing.insert(INSERT, 3)
    
def fourclick():
    value_of_thing.insert(INSERT, 4)

def fiveclick():
    value_of_thing.insert(INSERT, 5)
    
def sixclick():
    value_of_thing.insert(INSERT, 6)
    
def sevenclick():
    value_of_thing.insert(INSERT, 7)
    
def eightclick():
    value_of_thing.insert(INSERT, 8)
    
def nineclick():
    value_of_thing.insert(INSERT, 9)
    
def zeroclick():
    value_of_thing.insert(INSERT, 0)
    
def equalclick():
    value_of_thing.insert(INSERT, " = ")
    
def pointclick():
    value_of_thing.insert(INSERT, ".")
    
def plusclick():
    value_of_thing.insert(INSERT, " + ")
    
def minusclick():
    value_of_thing.insert(INSERT, " - ")

def multiplyclick():
    value_of_thing.insert(INSERT, " x ")
    
def divideclick():
    value_of_thing.insert(INSERT, " / ")
    
def clr():
    global clr
    clr.delete(0, END)
    
value_of_thing = Entry(root, width = 54)
value_of_thing.grid(row = 0, columnspan = 4)

equal = Button(text = "=")
equal.config( height = 5, width = 10, bg = "goldenrod", command = result)
equal.grid(row = 4, column = 3)

plus = Button(text = "+")
plus.config( height = 5, width = 10 , bg = "goldenrod", command = plusclick)
plus.grid(row = 4, column = 2)

point = Button(text = ".")
point.config( height = 5, width = 10, bg = "goldenrod", command = pointclick)
point.grid(row = 4, column = 1)

zero = Button(text = "0")
zero.config( height = 5, width = 10, bg = "dim gray", command = zeroclick)
zero.grid(row = 4, column = 0)

one = Button(text = "1")
one.config( height = 5, width = 10, bg = "red", command = oneclick)
one.grid(row = 3, column = 0)

two = Button(text = "2")
two.config( height = 5, width = 10, bg = "red", command = twoclick)
two.grid(row = 3, column = 1)

three = Button(text = "3")
three.config( height = 5, width = 10, bg = "red", command = threeclick)
three.grid(row = 3, column = 2)

minus = Button(text = "-")
minus.config(height = 5, width = 10, bg = "goldenrod", command = minusclick)
minus.grid(row = 3, column = 3)

four = Button(text = "4")
four.config( height = 5, width = 10, bg = "dark slate blue", command = fourclick)
four.grid(row = 2, column = 0)

five = Button(text = "5")
five.config( height = 5, width = 10, bg = "dark slate blue", command = fiveclick)
five.grid(row = 2, column = 1)

six = Button(text = "6")
six.config( height = 5, width = 10, bg = "dark slate blue", command = sixclick)
six.grid(row = 2, column = 2)

multiply = Button(text = "x")
multiply.config(height =5, width = 10, bg = "goldenrod", command = multiplyclick)
multiply.grid(row = 2, column = 3)

seven = Button(text = "7")
seven.config( height = 5, width = 10, bg = "lawn green", command = sevenclick)
seven.grid(row = 1, column = 0)

eight = Button(text = "8")
eight.config( height = 5, width = 10, bg = "lawn green", command = eightclick)
eight.grid(row = 1, column = 1)

nine = Button(text = "9")
nine.config( height = 5, width = 10, bg = "lawn green", command = nineclick)
nine.grid(row = 1, column = 2)

divide = Button(text = "/")
divide.config(height = 5, width = 10, bg = "goldenrod", command = divideclick)
divide.grid(row = 1, column = 3)

root.mainloop()

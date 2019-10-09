
import random
import pyttsx3

list_a = []
list_b = []
list_c = []

def insult_me():
    word_a=random.choice(list_a)
    word_b=random.choice(list_b)
    word_c=random.choice(list_c)
    insult =  word_a + " "+ word_b + " "+ word_c+ "!"
    return insult

with open("insults.csv", "r") as f:
       for line in f:
        words = line.split(",")
        list_a.append(words[0])
        list_b.append(words[1])
        list_c.append(words[2].strip())

while True:
    who=input("who are you insulting?" + "\n")
    if who == "you" or who == "we" or who == "they":
        be = "are"
    elif who == "I":
        be = "am"
    else:
        be = "is"
    sayInsult = who + " " + be + " " + "a "+ insult_me()
    engine = pyttsx3.init()
    engine.say(sayInsult)
    engine.runAndWait()

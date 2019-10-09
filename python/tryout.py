
import random
import pyttsx3
from guizero import App, Text, PushButton
import _thread



list_a = []
list_b = []
list_c = []


def insult_me():
    word_a=random.choice(list_a)
    word_b=random.choice(list_b)
    word_c=random.choice(list_c)
    insult = "You" + " " + word_a + " "+ word_b + " "+ word_c+ "!"
    return insult

def new_insult():
    new_val = insult_me()
    message.value = new_val
    # try:
    #    _thread.start_new_thread( speak, (new_val, ) )
    # except:
    #    print ("Error: unable to start thread")


def speak(messageT):
    print("speak")
    engine = pyttsx3.init()
    engine.say(messageT)
    engine.runAndWait()







with open("insults.csv", "r") as f:

       for line in f:
        words = line.split(",")
        list_a.append(words[0])
        list_b.append(words[1])
        list_c.append(words[2].strip())


app = App("Shakespearean insult generator", height=180,width=500)
message = Text(app, insult_me(), color= "#003344", size= 20 )
button = PushButton(app, new_insult, text="Insult me")

app.display()

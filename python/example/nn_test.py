import numpy
import pyttsx3


data_1 = [3,2,4,3,3.5,2,5.5,1,4.5]
data_2 = [1.5,1,1.5,1,0.5,0.5,1,1,1]
target = [1,0,1,0,1,0,1,0,1]
engine = pyttsx3.init()


def sigmoid(x):
    return 1/(1+numpy.exp(-x))

def predict(x,y,w1,w2,b):
    z = x * w1 + y * w2 + b
    p = sigmoid(z)

    if p>0.5:
        engine.say('red flower')
        engine.runAndWait()
    else:
        engine.say('blue flower')
        engine.runAndWait()


w1 = numpy.random.randn()
w2 = numpy.random.randn()
b = numpy.random.randn()
learningRate = 0.2

#training loop, number represents the training number, usually big
for i in range(100000):
    # pick random data point
    num=numpy.random.randint(low=0,high=8)

    # calculate the prediction starting with the random weight and bias
    z = data_1[num] * w1 + data_2[num] * w2 + b
    # make a prediction using sigmoid
    prediction = sigmoid(z)

    #compare the model prediction with the actual target value
    cost= (prediction - target[num])**2

    #find the slope of the cost w, r, t each parameter (w1 w2 b)
    #bring derivative through square function
    dcost_dpred= 2* (prediction - target[num])

    #bring derivative through sigmoid (prediction is sigmoid)
    #dpred_dz = sigmoid(z) * (1-sigmoid(z))
    dpred_dz = prediction * (1-prediction)

    dz_dw1=data_1[num]
    dz_dw2=data_2[num]
    dz_db=1

    #pertial derivatives using the chain rule
    dcost_dw1=dcost_dpred*dpred_dz*dz_dw1
    dcost_dw2=dcost_dpred*dpred_dz*dz_dw2
    dcost_db=dcost_dpred*dpred_dz*dz_db

    #adjust the parameters
    w1-=learningRate*dcost_dw1
    w2-=learningRate*dcost_dw2
    b-=learningRate*dcost_db

print ("w1: " , w1 ,"  w2: ", w2 ,"   b: " , b)

while True:

    petal1=float(input("petal width?" + "\n"))
    petal2=float(input("petal height?" + "\n"))

    predict(petal1,petal2,w1,w2,b)

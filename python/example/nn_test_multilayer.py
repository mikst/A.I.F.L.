import numpy
import pyttsx3


data_1 = [3,2,4,2.5,3.5,2,5.5,1,4.5]
data_2 = [1.5,1,1.5,1,0.5,0.5,1,1,1]
target = [1,0,1,0,1,0,1,0,1]
engine = pyttsx3.init()


def sigmoid(x):
    return 1/(1+numpy.exp(-x))

# def predict(x,y, w1_1, w1_2, b1,w2_1, w2_2, b2, w3_1, w3_2, b3 ):
def predict(x, y):

    print("x: ", x, " y:", y)

    # calculate the prediction starting with the random weight and bias
    z1 = x * w1_1 + y * w1_2 + b1
    # make a prediction using sigmoid
    prediction1 = sigmoid(z1)

    # calculate the prediction starting with the random weight and bias
    z2 = (x * w2_1 ) + (y * w2_2) + b2
    # make a prediction using sigmoid
    prediction2 = sigmoid(z2)

    # calculate the prediction starting with the random weight and bias
    z3 = prediction1 * w3_1 + prediction2 * w3_2 + b3
    # make a prediction using sigmoid
    prediction3 = sigmoid(z3)
    print("result: ",prediction3)

    if prediction3>0.5:
       engine.say('red flower')
       engine.runAndWait()
    else:
       engine.say('blue flower')
       engine.runAndWait()


w1_1 = numpy.random.randn()
w1_2 = numpy.random.randn()
b1 = numpy.random.randn()
w2_1 = numpy.random.randn()
w2_2 = numpy.random.randn()
b2 = numpy.random.randn()
w3_1 = numpy.random.randn()
w3_2 = numpy.random.randn()
b3 = numpy.random.randn()
learningRate = 0.2

#training loop, number represents the training number, usually big
for i in range(100000):
    # pick random data point
    num=numpy.random.randint(low=0,high=8)

    # calculate the prediction starting with the random weight and bias
    z1 = data_1[num] * w1_1 + data_2[num] * w1_2 + b1
    # make a prediction using sigmoid
    prediction1 = sigmoid(z1)

    # calculate the prediction starting with the random weight and bias
    z2 = data_1[num] * w2_1 + data_2[num] * w2_2 + b2
    # make a prediction using sigmoid
    prediction2 = sigmoid(z2)

    # calculate the prediction starting with the random weight and bias
    z3 = prediction1 * w3_1 + prediction2 * w3_2 + b3
    # make a prediction using sigmoid
    prediction3 = sigmoid(z3)

#----------------------------------

    #compare the model prediction with the actual target value
    cost3= (prediction3 - target[num])**2

    #find the slope of the cost w, r, t each parameter (w1 w2 b)
    #bring derivative through square function
    dcost_dpred3= 2* (prediction3 - target[num])

    #bring derivative through sigmoid (prediction is sigmoid)
    #dpred_dz = sigmoid(z) * (1-sigmoid(z))
    dpred_dz3 = prediction3 * (1-prediction3)

    dz_dw3_1=prediction1
    dz_dw3_2=prediction2
    dz_db3=1

    #pertial derivatives using the chain rule
    dcost_dw3_1=dcost_dpred3*dpred_dz3*dz_dw3_1
    dcost_dw3_2=dcost_dpred3*dpred_dz3*dz_dw3_2
    dcost_db3=dcost_dpred3*dpred_dz3*dz_db3

    #adjust the parameters
    w3_1_orig = w3_1
    w3_2_orig = w3_2
    w3_1-=learningRate*dcost_dw3_1
    w3_2-=learningRate*dcost_dw3_2
    b3-=learningRate*dcost_db3

#---------------------------------

    dE_dNet = dcost_dpred3 * dpred_dz3
    dNet_dHout1 = w3_1_orig
    dE_dHout1 = dE_dNet * dNet_dHout1

    dHout1_dHnet1 = prediction1 * (1-prediction1)

    # w1_1
    dHnet1_dW1_1 = data_1[num]
    dE_dW1_1 = dE_dHout1 * dHout1_dHnet1 * dHnet1_dW1_1

    w1_1 -= learningRate * dE_dW1_1

    # w1_2
    dHnet1_dW1_2 = data_2[num]
    dE_dW1_2 = dE_dHout1 * dHout1_dHnet1 * dHnet1_dW1_2

    w1_2 -= learningRate * dE_dW1_2

    # b
    b1 -= learningRate * dE_dHout1 * dHout1_dHnet1

    #----------------------------
    dNet_dHout2 = w3_2_orig
    dE_dHout2 = dE_dNet * dNet_dHout2

    dHout2_dHnet2 = prediction2 * (1-prediction2)

    # w2_1
    dHnet2_dW2_1 = data_1[num]
    dE_dW2_1 = dE_dHout2 * dHout2_dHnet2 * dHnet2_dW2_1

    w2_1 -= learningRate * dE_dW2_1

    # w2_2
    dHnet2_dW2_2 = data_2[num]
    dE_dW2_2 = dE_dHout2 * dHout2_dHnet2 * dHnet2_dW2_2

    w2_2 -= learningRate * dE_dW2_2

    # b
    b2 -= learningRate * dE_dHout2 * dHout2_dHnet2





print ("w1_1: " , w1_1 ,"  w1_2: ", w1_2 ,"   b1: " , b1, "w2_1: " , w2_1 ,"  w2_2: ", w2_2 ,"   b2: " , b2, "w3_1: " , w3_1 ,"  w3_2: ", w3_2 ,"   b3: " , b3)

while True:

    petal1=float(input("petal width?" + "\n"))
    petal2=float(input("petal height?" + "\n"))

    # predict(petal1, petal2, w1_1, w1_2, b1, w2_1, w2_2, b2, w3_1, w3_2, b3 )
    predict(petal1, petal2)

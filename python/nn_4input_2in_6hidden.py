import numpy
import pyttsx3

data=[
[824,843,730,789,0.00],
[386,489,377,512,1.00],
[397,431,648,700,0.50],
[377,457,411,492,1.00],
[804,843,752,793,0.00],
[421,484,578,718,0.50],
[406,489,418,517,1.00],
[827,839,695,788,0.00],
[408,447,570,704,0.50],
[404,472,400,504,1.00],
[816,842,708,804,0.00],
[406,456,558,684,0.50],
[397,471,383,510,1.00],
[844,857,742,810,0.00],
[409,459,578,689,0.50],
[399,474,408,509,1.00],
[822,837,665,789,0.00],
[417,451,570,724,0.50],
[394,466,357,518,1.00],
[804,831,695,795,0.00],
[410,442,590,738,0.50],
[394,460,383,509,1.00],
[804,841,695,799,0.00],
[444,443,696,751,0.50],
[388,449,399,491,1.00],
[834,850,729,810,0.00],
[427,479,695,746,0.50],
[391,474,352,516,1.00],
[829,849,722,810,0.00],
[445,445,634,723,0.50],
[397,461,390,496,1.00],
[839,853,718,808,0.00],
[434,482,703,728,0.50],
[394,471,402,500,1.00],
[843,853,727,799,0.00],
[412,465,692,708,0.50],
[391,470,410,502,1.00],
[832,851,737,806,0.00],
[411,451,669,701,0.50],
[402,478,405,517,1.00],
[836,857,696,809,0.00],
[414,461,636,707,0.50],
[394,472,406,514,1.00],
[839,856,690,808,0.00]
]

engine = pyttsx3.init()

# number of neurones in hidden layer1
Num_H1=6
# number of neurones in hidden layer2
Num_H2=3

# initializing weights, bias and prediction for neurones on each layers
H1_weights=[[0, 0, 0],[0, 0, 0],[0, 0, 0],[0, 0, 0],[0, 0, 0],[0, 0, 0]]

H2_weights=[[0, 0, 0],[0, 0, 0],[0, 0, 0]]
H2_weights_last=[[0, 0, 0] ,[0, 0, 0],[0, 0, 0]]

H1_prediction=[0,0,0,0,0,0]
H2_prediction=[0,0,0]

# initializing weights and bias for output layer
out_weights=[0,0,0,0]
out_weights_last=[0,0,0,0]
learningRate = 0.2

propValH=[0,0,0,0]

triout = 1

#initialize the weights with random number
def __init__weights():

    for i in range(Num_H1):
        for t in range(3):
            H1_weights[i][t]=numpy.random.randn()

    for i in range(Num_H2):
        for t in range(3):
            H2_weights[i][t]=numpy.random.randn()

    # initializing weights and bias for output layer
    for i in range(Num_H2+1):
        out_weights[i]=numpy.random.randn()



def sigmoid(x):
    return 1/(1+numpy.exp(-x))


def predict(data1, data2, data3, data4):

    data1=data1/1023
    data2=data2/1023
    data3=data3/1023
    data4=data4/1023


    # hidden layer 1
    for i in range(Num_H1):

        if i%3 == 0:
            z = (data1*H1_weights[i][0])+(data2*H1_weights[i][1])+H1_weights[i][2]

        elif i%3 == 1:
            z = (data2*H1_weights[i][0])+(data3*H1_weights[i][1])+H1_weights[i][2]

        elif i%3 == 2:
            z = (data3*H1_weights[i][0])+(data4*H1_weights[i][1])+H1_weights[i][2]

        #if triout == 1:
            #print ("layer1")

        # make a prediction using sigmoid
        H1_prediction[i]= sigmoid(z)

    # hidden layer 2
    for j in range(Num_H2):
        # calculate the prediction starting with the random weight and bias
        z = (H1_prediction[j*2]*H2_weights[j][0])+(H1_prediction[j*2+1]*H2_weights[j][1])+H2_weights[j][2]

        #if triout ==1:
            #print ("layer2")
        # make a prediction using sigmoid
        H2_prediction[j]= sigmoid(z)

    # output layer
    # calculate the prediction starting with the random weight and bias
    z = (H2_prediction[0]*out_weights[0])+(H2_prediction[1]*out_weights[1])+(H2_prediction[2]*out_weights[2])+out_weights[3]
    # make a prediction using sigmoid
    #if triout==1:
        #print ("output")
    pred = sigmoid(z)

    return pred


__init__weights()

#training loop, number represents the training number, usually big
for l in range(100000):

    # pick random data point
    num=numpy.random.randint(low=0,high=42)

    #if triout == 1:
        #print("start of the training mode")
        #print(data[num][0], data[num][1], data[num][2], data[num][3])
        #print(H1_weights[0][0], H1_weights[0][1], H1_weights[0][2])
        #triout = 0

    prediction = predict(data[num][0], data[num][1], data[num][2], data[num][3])



#----------------------------------
# back propagation output layer

    #find the slope of the cost w, r, t each parameter (w1 w2 b)
    #bring derivative through square function
    dcost_dpred= 2* (prediction - data[num][4])

    #bring derivative through sigmoid (prediction is sigmoid)
    #dpred_dz = sigmoid(z) * (1-sigmoid(z))
    dpred_dz = prediction * (1-prediction)


    for t in range(Num_H2):
        #save the weights parameters
        out_weights_last[t]=out_weights[t]
        #adjust the weights
        out_weights[t]-=learningRate*dcost_dpred*dpred_dz*H2_prediction[t]

    # adjust the bias
    out_weights[Num_H2]-=learningRate*dcost_dpred*dpred_dz
    propVal=dcost_dpred*dpred_dz

    #print("out_weights : ")
    #print(out_weights)
#---------------------------------
    #back propagation for 2nd hidden layer
    #here is the difference for hidde layer, the derivative of cost is calculated from previous layer
    for t in range(Num_H2):
        dcost_dpred = propVal* out_weights_last[t]

        #bring derivative through sigmoid (prediction is sigmoid)
        #dpred_dz = sigmoid(z) * (1-sigmoid(z))
        dpred_dz = H2_prediction[t] * (1-H2_prediction[t])

        dcost_dw1 = dcost_dpred * dpred_dz* H1_prediction[t*2]
        dcost_dw2 = dcost_dpred * dpred_dz * H1_prediction[t*2+1]

        for  q in range(3):
            H2_weights_last[t][q]=H2_weights[t][q]

        H2_weights[t][0]-= learningRate *dcost_dw1
        H2_weights[t][1]-= learningRate *dcost_dw2
        H2_weights[t][2]-= learningRate * dcost_dpred * dpred_dz

        propValH[t]=dcost_dpred * dpred_dz

    #print("H2_weights : ")
    #print(H2_weights)
    #---------------------------------
    #back propagation for 1st hidden layer
    #here is the difference for hidde layer, the derivative of cost is calculated from previous layer
    for t in range(Num_H1):
        dcost_dpred = propValH[int(t/2)%3] * H2_weights_last[t%3][t%2]

        #bring derivative through sigmoid (prediction is sigmoid)
        #dpred_dz = sigmoid(z) * (1-sigmoid(z))
        dpred_dz = H1_prediction[t] * (1-H1_prediction[t])

        dcost_dw1 = dcost_dpred * dpred_dz * data[num][t%3]
        dcost_dw2 = dcost_dpred * dpred_dz * data[num][t%3+1]


        H1_weights[t][0]-= learningRate *dcost_dw1
        H1_weights[t][1]-= learningRate *dcost_dw2
        H1_weights[t][2]-= learningRate * dcost_dpred * dpred_dz

    #print("H1_weights : ")
    #print(H1_weights)
# end of back propagatioin---------------------------
print(H1_weights)
print(H2_weights)
print(out_weights)

while True:

    triout = 1
    sensor1=float(input("sensor1 input?" + "\n"))
    sensor2=float(input("sensor2 input?" + "\n"))
    sensor3=float(input("sensor3 input?" + "\n"))
    sensor4=float(input("sensor4 input?" + "\n"))

    result = predict(sensor1, sensor2, sensor3, sensor4)
    print(result)

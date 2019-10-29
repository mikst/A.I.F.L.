import numpy
import pyttsx3

data=[
[864,865,743,833,0.00],
[461,570,582,717,1.00],
[846,873,779,837,0.00],
[446,560,547,723,1.00],
[837,872,788,838,0.00],
[435,560,544,707,1.00],
[842,868,794,840,0.00],
[447,563,550,636,1.00],
[816,866,781,836,0.00],
[442,562,552,654,1.00],
[805,859,718,808,0.00],
[448,566,553,663,1.00],
[759,845,756,805,0.00],
[448,560,566,671,1.00],
[832,862,787,829,0.00],
[461,560,539,722,1.00],
[804,859,796,828,0.00],
[463,561,580,690,1.00],
[758,846,787,818,0.00],
[464,561,589,703,1.00],
[771,847,769,812,0.00],
[469,559,562,704,1.00],
[794,851,791,819,0.00],
[469,563,595,688,1.00],
[769,840,763,803,0.00],
[465,568,590,675,1.00],
[747,852,792,817,0.00],
[463,567,574,721,1.00],
[796,857,752,809,0.00],
[461,564,598,698,1.00],
[844,858,752,807,0.00],
[456,562,585,656,1.00],
[794,846,811,806,0.00],
[481,580,544,650,1.00],
[836,837,757,804,0.00],
[477,584,577,677,1.00],
[832,861,807,823,0.00],
[500,623,579,727,1.00],
[823,860,754,805,0.00],
[509,633,515,707,1.00],
[829,861,706,799,0.00]
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

    #convert the data into 0-1 scale. original sensor inputs are in the scale of 0-1023
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
print(H1_weights)
print(H2_weights)
print(out_weights)
print("----------end init------------------")

#training loop, number represents the training number, usually big
for l in range(10000):

    # pick random data point
    num=numpy.random.randint(low=0,high=39)

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

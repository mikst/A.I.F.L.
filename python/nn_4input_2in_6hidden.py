import numpy
import pyttsx3

data=[
[443,512,459,578,0],
[828,848,683,797,1],
[422,495,439,544,0],
[776,822,631,769,1],
[417,504,436,544,0],
[771,811,618,755,1],
[420,477,428,529,0],
[769,821,583,755,1],
[433,490,461,537,0],
[781,815,644,775,1],
[428,489,418,530,0],
[783,827,655,779,1],
[426,504,448,526,0],
[773,813,559,755,1],
[424,492,442,534,0],
[730,789,520,735,1],
[443,510,433,536,0],
[773,802,564,757,1],
[468,525,452,540,0],
[775,823,564,757,1],
[480,536,416,559,0],
[477,536,414,564,0],
[757,790,554,736,1],
[468,533,428,539,0],
[725,775,510,713,1],
[491,555,443,554,0],
[765,807,569,757,1],
[497,559,423,558,0],
[743,801,559,747,1],
[495,558,435,552,0],
[825,852,707,813,1],
[491,554,439,550,0],
[829,853,733,818,1],
[472,543,447,538,0],
[816,849,699,826,1],
[483,547,415,540,0],
[838,856,770,837,1],
[497,556,426,549,0],
[810,837,647,816,1],
[818,841,674,799,1],
[505,575,396,561,0],
[825,840,629,793,1],
[481,542,405,542,0],
[814,839,616,792,1],
[508,606,407,581,0],
[785,811,563,764,1],
[429,509,415,514,0],
[726,781,491,746,1],
[495,578,391,554,0],
[818,816,555,778,1],
[486,549,384,539,0]
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

#training loop, number represents the training number, usually big
for l in range(100000):

    # pick random data point
    num=numpy.random.randint(low=0,high=49)

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

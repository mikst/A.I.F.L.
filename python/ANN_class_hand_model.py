import numpy
import pyttsx3

# data from newGloe_data01
# paper =1, scissors =2, rock =0
data=[
[819,932,896,938,0],
[697,525,472,733,2],
[540,540,497,466,1],
[544,570,486,485,1],
[514,542,476,455,1],
[699,544,454,762,2],
[789,570,466,857,2],
[781,935,898,913,0],
[768,931,888,894,0],
[798,938,902,922,0],
[811,949,913,930,0],
[657,540,463,809,2],
[661,557,480,818,2],
[663,566,484,819,2],
[542,570,486,476,1],
[539,566,489,479,1],
[539,567,482,473,1],
[541,575,489,477,1],
[543,577,491,479,1],
[751,580,470,874,2],
[755,588,483,867,2],
[753,926,891,917,0],
[761,932,893,915,0],
[703,539,469,698,2],
[536,556,486,456,1],
[773,582,472,855,2],
[737,903,878,891,0],
[682,538,460,622,2],
[517,570,476,467,1],
[758,577,462,720,2],
[753,915,901,903,0],
[754,915,898,899,0],
[744,906,891,895,0],
[652,548,472,670,2],
[713,559,477,771,2],
[707,566,484,770,2],
[527,546,479,451,1],
[539,565,491,470,1],
[528,562,480,456,1],
[532,582,465,518,1],
[840,579,453,850,2],
[891,553,474,912,2],
[832,940,923,942,0],
[693,869,853,854,0],
[849,914,915,946,0],
[705,545,476,808,2],
[713,570,495,823,2],
[541,530,483,515,1],
[548,534,489,513,1],
[781,844,877,889,0],
[783,843,875,884,0],
[734,524,457,703,2],
[716,532,470,758,2],
[722,539,480,764,2],
[535,522,474,458,1],
[557,571,489,496,1],
]



class Neuron:

    def __init__(self, id):
        self.weights = []
        self.bias = numpy.random.randn()
        self.output_value=0
        self.temp_value=0
        self.inputNeurons= []
        self.outputNeurons= []
        self.id = id
        self.learningRate=0.2

    def setInput(self, inputNeuron):
        self.inputNeurons.append(inputNeuron)
        self.weights.append(numpy.random.randn())

    def forwardUpdate(self):
        out=0
        for n in range(len(self.inputNeurons)):
            out += self.inputNeurons[n].getValue() * self.weights[n]
        self.temp_value = out + self.bias
        self.output_value = self.sigmoid(self.temp_value)

    def sigmoid(self, x):
        return 1/(1+numpy.exp(-x))

    def getValue(self):
        return self.output_value

    def setValue(self, input=0):
        self.output_value = input

    def dump(self):
        print("id: ", self.id)
        #print("output: ", self.output_value)
        #print("value: ", self.temp_value)
        print("b= ", self.bias, ";")
        for n in range(len(self.weights)):
            wname = "w"+ str(n)
            print(wname, "=", self.weights[n], ";")

    def backPropagation(self, target, output):
        if output == 1:
            #bring derivative through square function
            dcost_dpred = 2* (self.output_value - target)
        else:
            dcost_dpred = target

        #bring derivative through sigmoid (prediction is sigmoid)
        #dpred_dz = sigmoid(z) * (1-sigmoid(z))
        dpred_dz = self.output_value * (1-self.output_value)
        # adjust the bias
        self.bias-=self.learningRate*dcost_dpred*dpred_dz


        for i in range(len(self.weights)):
            self.inputNeurons[i].backPropagation( dcost_dpred*dpred_dz * self.weights[i],0)
            #adjust the weights
            self.weights[i]-=self.learningRate * dcost_dpred*dpred_dz * self.inputNeurons[i].output_value






input_neurons = []
hidden1_neurons = []
hidden2_neurons = []
output_neurons = []

def connectNetwork():
    for i in range (4):
        input_neurons.append(Neuron(i))
    for i in range (4):
        hidden1_neurons.append(Neuron(i))
    for i in range (3):
        hidden2_neurons.append(Neuron(i))
    for i in range (3):
        output_neurons.append(Neuron(i))

    hidden1_neurons[0].setInput(input_neurons[0])
    hidden1_neurons[0].setInput(input_neurons[1])
    hidden1_neurons[0].setInput(input_neurons[2])

    hidden1_neurons[1].setInput(input_neurons[0])
    hidden1_neurons[1].setInput(input_neurons[2])
    hidden1_neurons[1].setInput(input_neurons[3])

    hidden1_neurons[2].setInput(input_neurons[0])
    hidden1_neurons[2].setInput(input_neurons[1])
    hidden1_neurons[2].setInput(input_neurons[3])

    hidden1_neurons[3].setInput(input_neurons[1])
    hidden1_neurons[3].setInput(input_neurons[2])
    hidden1_neurons[3].setInput(input_neurons[3])

    #--------------------------------------

    hidden2_neurons[0].setInput(hidden1_neurons[0])
    hidden2_neurons[0].setInput(hidden1_neurons[1])
    hidden2_neurons[0].setInput(hidden1_neurons[2])

    hidden2_neurons[1].setInput(hidden1_neurons[0])
    hidden2_neurons[1].setInput(hidden1_neurons[3])
    hidden2_neurons[1].setInput(hidden1_neurons[2])


    hidden2_neurons[2].setInput(hidden1_neurons[2])
    hidden2_neurons[2].setInput(hidden1_neurons[3])
    hidden2_neurons[2].setInput(hidden1_neurons[1])

    #--------------------------------------

    output_neurons[0].setInput(hidden2_neurons[1])
    output_neurons[0].setInput(hidden2_neurons[0])
    output_neurons[0].setInput(hidden2_neurons[2])

    output_neurons[1].setInput(hidden2_neurons[0])
    output_neurons[1].setInput(hidden2_neurons[2])
    output_neurons[1].setInput(hidden2_neurons[1])

    output_neurons[2].setInput(hidden2_neurons[0])
    output_neurons[2].setInput(hidden2_neurons[1])
    output_neurons[2].setInput(hidden2_neurons[2])


connectNetwork()
#sensorMin = 300
#sensorMax = 900

def training(cycle):
    for i in range (cycle):
        # pick random data point
        num=numpy.random.randint(low=0,high=52)
        for t in range (len(input_neurons)):
            # adjusting the sensor input to 0-1.0 scale. min 300, max 900
            val = (data[num][t]-300)/600
            if val > 1.0:
                val = 1.0
            if val<0:
                val =0
            input_neurons[t].setValue(val)

        for neuron in hidden1_neurons:
            neuron.forwardUpdate()

        for neuron in hidden2_neurons:
            neuron.forwardUpdate()

        for neuron in output_neurons:
            neuron.forwardUpdate()

        for t in range(3):
            if data[num][4] == t:
                output_neurons[t].backPropagation(1,1)
            else:
                output_neurons[t].backPropagation(0,1)


training(10000)

for neuron in hidden1_neurons:
    neuron.dump()
for neuron in hidden2_neurons:
    neuron.dump()
for neuron in output_neurons:
   neuron.dump()

sensor=[0,0,0,0]

while True:

    sensor[0]=float(input("sensor1 input?" + "\n"))
    sensor[1]=float(input("sensor2 input?" + "\n"))
    sensor[2]=float(input("sensor3 input?" + "\n"))
    sensor[3]=float(input("sensor4 input?" + "\n"))

    for t in range (4):
        # adjusting the sensor input to 0-1.0 scale. min 300, max 900
        val = (sensor[t]-300)/(600)
        if val > 1.0:
            val = 1.0
        if val<0:
            val =0
        input_neurons[t].setValue(val)

    for neuron in hidden1_neurons:
        neuron.forwardUpdate()

    for neuron in hidden2_neurons:
        neuron.forwardUpdate()

    for neuron in output_neurons:
        neuron.forwardUpdate()

    print("out1: ", output_neurons[0].output_value)
    print("out2: ", output_neurons[1].output_value)
    print("out3: ", output_neurons[2].output_value)

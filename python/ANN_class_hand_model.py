import numpy
import pyttsx3

# data from newGloe_data01
# paper =1, scissors =2, stone =0
data=[
[493,473,401,388,1],
[601,507,423,600,2],
[605,819,792,786,0],
[516,471,413,393,1],
[626,484,428,736,2],
[580,772,755,755,0],
[496,473,419,395,1],
[599,499,432,613,2],
[738,439,385,777,2],
[517,752,710,724,0],
[785,920,889,901,0],
[587,820,793,781,0],
[496,470,442,406,1],
[469,423,422,379,1],
[669,449,405,635,2],
[603,769,761,778,0],
[489,453,406,380,1],
[494,480,429,393,1],
[667,476,413,609,2],
[674,485,424,627,2],
[662,811,777,813,0],
[737,879,839,883,0],
[733,876,838,882,0],
[648,457,395,645,2],
[694,848,800,826,0],
[489,473,415,387,1],
[736,494,410,750,2],
[478,470,396,379,1],
[466,451,416,382,1],
[741,905,842,854,0],
[615,826,765,745,0],
[621,483,409,583,2],
[463,465,405,358,1],
[477,466,393,371,1],
[655,479,398,620,2],
[663,794,771,788,0],
[526,476,404,505,2],
[652,742,745,769,0],
[467,449,392,358,1],
[648,499,405,674,2],
[829,444,391,824,2],
[615,511,430,584,2]
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
        print("output: ", self.output_value)
        print("value: ", self.temp_value)
        print("bias: ", self.bias)
        #print("number of inputs: ", len(self.inputNeurons))
        print("weights: ", self.weights)

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
    #hidden1_neurons[0].setInput(input_neurons[3])

    hidden1_neurons[1].setInput(input_neurons[0])
    hidden1_neurons[1].setInput(input_neurons[1])
    hidden1_neurons[1].setInput(input_neurons[2])
    #hidden1_neurons[1].setInput(input_neurons[3])

    #hidden1_neurons[2].setInput(input_neurons[0])
    hidden1_neurons[2].setInput(input_neurons[1])
    hidden1_neurons[2].setInput(input_neurons[2])
    hidden1_neurons[2].setInput(input_neurons[3])

    hidden1_neurons[3].setInput(input_neurons[1])
    hidden1_neurons[3].setInput(input_neurons[2])
    hidden1_neurons[3].setInput(input_neurons[3])
    #hidden1_neurons[3].setInput(input_neurons[0])

    hidden2_neurons[0].setInput(hidden1_neurons[0])
    hidden2_neurons[0].setInput(hidden1_neurons[1])
    hidden2_neurons[0].setInput(hidden1_neurons[2])
    #hidden2_neurons[0].setInput(hidden1_neurons[3])


    hidden2_neurons[1].setInput(hidden1_neurons[0])
    hidden2_neurons[1].setInput(hidden1_neurons[2])
    hidden2_neurons[1].setInput(hidden1_neurons[3])
    #hidden2_neurons[1].setInput(hidden1_neurons[1])


    hidden2_neurons[2].setInput(hidden1_neurons[1])
    hidden2_neurons[2].setInput(hidden1_neurons[2])
    hidden2_neurons[2].setInput(hidden1_neurons[3])
    #hidden2_neurons[2].setInput(hidden1_neurons[0])



    output_neurons[0].setInput(hidden2_neurons[0])
    output_neurons[0].setInput(hidden2_neurons[1])
    output_neurons[0].setInput(hidden2_neurons[2])

    output_neurons[1].setInput(hidden2_neurons[0])
    output_neurons[1].setInput(hidden2_neurons[1])
    output_neurons[1].setInput(hidden2_neurons[2])

    output_neurons[2].setInput(hidden2_neurons[0])
    output_neurons[2].setInput(hidden2_neurons[1])
    output_neurons[2].setInput(hidden2_neurons[2])


connectNetwork()

def training(cycle):
    for i in range (cycle):
        # pick random data point
        num=numpy.random.randint(low=0,high=40)
        for t in range (len(input_neurons)):
            input_neurons[t].setValue(data[num][t]/1023)

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
        input_neurons[t].setValue(sensor[t]/1023)

    for neuron in hidden1_neurons:
        neuron.forwardUpdate()

    for neuron in hidden2_neurons:
        neuron.forwardUpdate()

    for neuron in output_neurons:
        neuron.forwardUpdate()

    print("out1: ", output_neurons[0].output_value)
    print("out2: ", output_neurons[1].output_value)
    print("out3: ", output_neurons[2].output_value)

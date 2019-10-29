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
hidden_neurons = []
output_neurons = []

def connectNetwork():
    for i in range (4):
        input_neurons.append(Neuron(i))
    for i in range (4):
        hidden_neurons.append(Neuron(i))
    for i in range (1):
        output_neurons.append(Neuron(i))

    hidden_neurons[0].setInput(input_neurons[0])
    hidden_neurons[0].setInput(input_neurons[1])

    hidden_neurons[1].setInput(input_neurons[1])
    hidden_neurons[1].setInput(input_neurons[2])

    hidden_neurons[2].setInput(input_neurons[2])
    hidden_neurons[2].setInput(input_neurons[3])

    hidden_neurons[3].setInput(input_neurons[3])
    hidden_neurons[3].setInput(input_neurons[0])

    output_neurons[0].setInput(hidden_neurons[0])
    output_neurons[0].setInput(hidden_neurons[1])
    output_neurons[0].setInput(hidden_neurons[2])
    output_neurons[0].setInput(hidden_neurons[1])

connectNetwork()

def training(cycle):
    for i in range (cycle):
        # pick random data point
        num=numpy.random.randint(low=0,high=39)
        for t in range (len(input_neurons)):
            input_neurons[t].setValue(data[num][t]/1023)

        for neuron in hidden_neurons:
            neuron.forwardUpdate()

        for neuron in output_neurons:
            neuron.forwardUpdate()

        for neuron in output_neurons:
            neuron.backPropagation(data[num][4],1)


training(10000)

for neuron in hidden_neurons:
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

    for neuron in hidden_neurons:
        neuron.forwardUpdate()

    for neuron in output_neurons:
        neuron.forwardUpdate()

    print(output_neurons[0].getValue())

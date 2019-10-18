import pyttsx3
import numpy
from random import choice, seed

engine = pyttsx3.init() # Init TTS engine

# a generic function to be used as a trigger for neurons?
def sigmoid(x):
    return 1/(1+numpy.exp(-x))

def getColor(pred):
    return 'red' if pred > 0.5 else 'blue'

"""
    Defining a class for a petal
"""
class Petal():

    def __init__(self, w, l, c = None):
        """
            Function initialising a petal
                - w is the width
                - l the length
                - c the color. Might be unknown (None).
        """
        self.width = w
        self.length = l
        self.color = c
        
    def __str__(self):
        """
            The to string function for petals
        """
        retStr = 'Petal ({0} - {1})'.format(self.width, self.length)
        
        if not self.color is None:
            retStr +=  ' -> {0}'.format(getColor(self.color))
            
        return retStr


 
"""
    Defining a class to represent what a neuron
"""
class neuron():

    def __init__(self, idx):
        """
            Function initialising a neuron
        """
        self.w = [
                numpy.random.randn(),
                numpy.random.randn()
                ] # Random init weights
        
        self.b = numpy.random.randn() # Random init bias
        self.idx = idx
        #print(self)
        
    def __str__(self):
        """
            The to string function for a neuron
        """
        retStr = 'N{0} | '.format(self.idx)
        retStr += 'Weight:[{0:.2f} / {1:.2f}]'.format(self.w[0], self.w[1])
        retStr += ' - Bias {0:.2f}'.format(self.b)

        return retStr

"""
    Defining a class to represent what a neural network is.
    This class is very simple because the application is rather simple as well.
    A neural net should probably be implemented very differently to deal
    with generic contexts.
"""
class neuralNet():

    def __init__(self, n, learningRate):
        """
            Function initialising the neural net.
        """
        self.n_neurons = n # The number of neurones in the net.
        self.neurons = []  # Planing to store the neurones in a list.
        self.learningRate = learningRate # Learning rate.
        
        # Creating neurons
        for i in range(n_neurons):
            self.neurons.append(neuron(i))
            
    def __str__(self):
        retStr = 'Net with {0} neurons:\n'.format(self.n_neurons)
        for i in range(self.n_neurons):
            retStr += '\t' + str(self.neurons[i]) + '\n'
        
        return retStr
            
    def predict(self, p_width, p_length):
        """
            Function using the net to make predictions
                - p_width is the petal width
                - p_length is the petal length
            The output is a list of predictions
        """
        preds = [] # List of predictions
        
        for n in self.neurons[:2]:
            """
            for the 2 first neurons
            - Compute prediction from random weight and bias
            """            
            z = p_width * n.w[0] + p_length * n.w[1] + n.b
            preds.append(sigmoid(z))

        
        # calculate the prediction starting with the random weight and bias
        n = self.neurons[-1] # Dealing with last neuron
        z = preds[0] * n.w[0] + preds[1] * n.w[1] + n.b
        preds.append(sigmoid(z))
        
        return preds
    
    def train(self, n_train, data):
        # Training loop.
        # Number represents the training number, usually big.
        for i in range(n_train):
            
            # Pick random petal
            rPetal = choice(train_petals)
            
            # Make a prediction.
            preds = self.predict(rPetal.width, rPetal.length)

            #----------------------------------
            # back propagation output layer

            # Compare the model prediction with the actual target value
            cost3 = (preds[2] - rPetal.color) ** 2

            #find the slope of the cost w, r, t each parameter (w1 w2 b)
            #bring derivative through square function
            dcost_dpred3 = 2 * (preds[2] - rPetal.color)

            #bring derivative through sigmoid (prediction is sigmoid)
            #dpred_dz = sigmoid(z) * (1-sigmoid(z))
            dpred_dz3 = preds[2] * (1 - preds[2])

            dz_dw3_1 = preds[0]
            dz_dw3_2 = preds[1]
            dz_db3 = 1

            #pertial derivatives using the chain rule
            dcost_dw3_1 = dcost_dpred3 * dpred_dz3 * dz_dw3_1
            dcost_dw3_2 = dcost_dpred3 * dpred_dz3 * dz_dw3_2
            dcost_db3 = dcost_dpred3 * dpred_dz3 * dz_db3

            #adjust the parameters
            w3_1_orig = self.neurons[2].w[0] # Weight 1 neuron 3
            w3_2_orig = self.neurons[2].w[1] # Weight 2 neuron 3
            
            self.neurons[2].w[0] -= learningRate * dcost_dw3_1
            self.neurons[2].w[1] -= learningRate * dcost_dw3_2
            self.neurons[2].b -= learningRate * dcost_db3
            
            '''
            NOTE: I assume the rest of the code below
            deals with back propagation. 
            I leave it untouched for now because I need to understand it. 
            Might take a while to implement correctly.
            '''

            #---------------------------------
            # Back propagation for hidden layer1 (N0)
            # here is the difference for hidde layer,
            # the derivative of cost is calculated from previous layer
            dcost_dz1 = dcost_dpred3 * dpred_dz3
            dz3_dpred1 = w3_1_orig
            dcost_dpred1 = dcost_dz1 * dz3_dpred1            
            
            # Bring derivative through sigmoid (prediction is sigmoid)
            dpred_dz1 = preds[0] * (1 - preds[0])
            
            # Updating weights and bias for neurone 0
            # W1
            dz_dw1_1 = rPetal.width
            dcost_dw1_1 = dcost_dpred1 * dpred_dz1 * dz_dw1_1
            self.neurons[0].w[0] -= learningRate * dcost_dw1_1
            
            # W2
            dz_dw1_2 = rPetal.length
            dcost_dw1_2 = dcost_dpred1 * dpred_dz1 * dz_dw1_2
            self.neurons[0].w[1] -= learningRate * dcost_dw1_2

            # B            
            self.neurons[0].b -= learningRate * dcost_dpred1 * dpred_dz1
            

            #----------------------------
            # Back propagation for hidden layer1
            # Here is the difference for hidde layer,
            # the derivative of cost is calculated from previous layer
            
            dcost_dz2 = dcost_dpred3 * dpred_dz3
            dz3_dpred2 = w3_2_orig
            dcost_dpred2 = dcost_dz2 * dz3_dpred2
            
            #bring derivative through sigmoid (prediction is sigmoid)            
            dpred_dz2 = preds[1] * (1 - preds[1])

            # W1
            dz_dw2_1 = rPetal.width
            dcost_dw2_1 = dcost_dpred2 * dpred_dz2 * dz_dw2_1
            self.neurons[1].w[0] -= learningRate * dcost_dw2_1

            # W2
            dz_dw2_2 = rPetal.length
            dcost_dw2_2 = dcost_dpred2 * dpred_dz2 * dz_dw2_2
            self.neurons[1].w[1] -= learningRate * dcost_dw2_2

            # b
            #b2 -= learningRate * dcost_dpred2 * dpred_dz2
            self.neurons[1].b -= learningRate * dcost_dpred2 * dpred_dz2
            
            
            '''
                Print the neural net every 10% of the training
                to get a sense of how it evolves.
            '''
            if i % int(n_train / 10) == 0:
                print('Training {0}%:'.format(i / int(n_train) * 100))
                print(self)
            



"""
    Toy program starts here.

    Because we are playing around with random values from numpy, 
    let us set a seed to one aprticular value.
    This allows for controlled experiements.
"""
numpy.random.seed(42) # Numpy's random
seed(42) # Python's random


n_neurons = 3      # Number of neuron in network
learningRate = 0.2 # Might have to be tuned for better results.
n_train = 10000    # Number of iterations in the training loop.

# Creating a net containing n_neurons with learningRate
print('Creating arnn with {0} neurons'.format(n_neurons))
arnn = neuralNet(n_neurons, learningRate)
print(arnn)

# Adding 9 petals to the training set.
# NOTE: Not sure what is coding for what: 0/1 -> blue-red
# 0 codes for blue(red?)
# 1 codes for red(blue?)
train_petals = []
train_petals.append(Petal(0.375,  0.75, 1.0))
train_petals.append(Petal(0.25,   0.5,  0.0))
train_petals.append(Petal(0.3125, 0.5,  0.0))
train_petals.append(Petal(0.4375, 0.25, 1.0))
train_petals.append(Petal(0.6875, 0.5,  1.0))
train_petals.append(Petal(0.125,  0.5,  0.0))
train_petals.append(Petal(0.5625, 0.5,  1.0))

# These were discarded from training set and included in testing set.
#train_petals.append(Petal(0.5,    0.75, 1.0)) 
#train_petals.append(Petal(0.25,   0.25, 0.0))


# Train the net on on the train_petals data set.
# NOTE : The train function is for now highly broken.
print('Training arnn with {} examples. ({} ite)'.format(len(train_petals), n_train))
arnn.train(n_train, train_petals)

# Net is traind now. Show weights and biases
print()
print('arnn after training')
print(arnn)


print('')
print('Using arnn to make predictions on known petals')

for petal in train_petals:
    c = arnn.predict(petal.width, petal.length)
    print('\t{0} predicted to be {1:.3f} ({2})'.format(petal, c[-1], getColor(c[-1])))

test_petals = []
test_petals.append(Petal(0.375, 0.75))  # Known red petal from training
test_petals.append(Petal(0.25,  0.5))   # Known blue petal from training
test_petals.append(Petal(0.5,   0.75))  # Known red but not used in training
test_petals.append(Petal(0.25,  0.25))  # Known blue but not used in training
test_petals.append(Petal(0.5,   0.5))   # Unknow petal

# Making predictions now.
print('')
print('Using arnn to make predictions on unseen petals')

for petal in test_petals:
    c = arnn.predict(petal.width, petal.length)
    #print('{0}'.format(c[-1]))
    print('\t{0} predicted to be {1:.3f} ({2})'.format(petal, c[-1], getColor(c[-1])))

# Uncomment to let user enter new petals.
# The call to espeak is a nice creepy touch.
#while True:
    
    ##NOTE: Not sure why quantities are divided by 8 and 2?
    ##pw = float(input('Petal width?'))/8
    ##pl = float(input("Petal height?"))/2
    #pw = float(input('Petal width?'))
    #pl = float(input("Petal height?"))
    
    ##New petal
    #p = Petal(pw, pl)
    
    #c = arnn.predict(p.width, p.length)
    #output = 'Petal ({0}) predicted to be {1:.3f}'.format(p, c[-1])
    #print(output)
    #engine.say('{0}'.format(getColor(c[-1])))
    #engine.runAndWait()
#

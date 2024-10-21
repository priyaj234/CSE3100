#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>

//dummy randomization
double randomRangeZeroAndOne()
{
    double x = (double)rand() / (double)RAND_MAX;
    double y = (double)rand() / (double)RAND_MAX;
    return x-y;
}

//neuron struct 
typedef struct {
    int inputSize;
    double* w; //weight parameter
    double b; //bias parameter
} neuron;

//layer struct
typedef struct {
    int inputSize;
    int numNeurons;
    neuron* nArray;
} layer;

//Feedforward network structure
typedef struct {
    int numLayers;
    //have an array with layers
    layer* lArray;
    //store the final output in this variable
    double* output;
} networkFF;

//Build the neuron  
neuron InitalizeNeuron(int inputSize){
    double* w = (double*)malloc(inputSize * sizeof(double));
    double b = randomRangeZeroAndOne();
    //start the network with random values
    for(int i=0;i<inputSize;i++){
        w[i] = randomRangeZeroAndOne();
    }
    neuron n = {inputSize, w, b};
    return n; 
}

 //build the network 
networkFF InitializeNetwork(int networkInputSize, int numLayers, int* numNeuronsPerLayer){
    //First create the layer array 
    layer* layerArray = (layer*)malloc(numLayers * sizeof(layer));
    //Fill in each layer with neurons 
    for(int i=0;i<numLayers;i++){
        //Each layer contains an array of neurons 
        int currentNumNeurons = numNeuronsPerLayer[i];
        neuron* neuronArray = (neuron*)malloc(currentNumNeurons * sizeof(neuron));
        //fill in the array of neurons
        for(int j=0;j<currentNumNeurons;j++){
            //first layer handled differently 
            if(i == 0){
                neuronArray[j] = InitalizeNeuron(networkInputSize);
            }
            else{
                //input comes from previous layer's output size 
                neuronArray[j] = InitalizeNeuron(numNeuronsPerLayer[i-1]);
            }
        }        
        //Neurons all build time to make the layer
         layer l =  {neuronArray[0].inputSize, currentNumNeurons, neuronArray};
         layerArray[i] = l;
    }
    //lastly fill in the network 
    networkFF network = {numLayers, layerArray, NULL};
    return network;
}

void printLayerWeights(networkFF* network){
    int numLayers = (*network).numLayers;
    //Go through each layer of the network 
    for(int i=0;i<numLayers;i++){
        layer currentLayer = (*network).lArray[i];
        int numNeuronsPerLayer = currentLayer.numNeurons;
        //Go through the neuron in each layer
        for(int j = 0; j< numNeuronsPerLayer;j++){
            printf("Layer-%d-Neuron-%d\n", i, j);
            neuron currentNeuron = (*network).lArray[i].nArray[j];
            //print the weight for each neuron
            int inputSize = currentNeuron.inputSize;
            for(int k=0;k<inputSize;k++){
                printf("w[%d]=%lf\n", k, currentNeuron.w[k]);
            }
        }
    }
}

//compute forward pass on the neuron
double ForwardPassNeuron(neuron* n, double* x){
    //Get the input size 
    int inputSize = (*n).inputSize;
    //memory for the solution
    double output = 0;
    //first apply the weight 
    for(int i = 0;i<inputSize;i++){
        output = output + (*n).w[i]*x[i];
    }
    //apply the bias 
    output = output + (*n).b;
    //apply an activation function 
    output = 1/(1+exp(-output));
    return output;
}

//compute a forward pass on the network 
void ForwardPassNetworkFF(double* x, networkFF* network){
    //basic variable setup
    int numLayers = (*network).numLayers;
    //allocate memory for the output of each layer of the network 
    double** layerOutputs = (double**)malloc((numLayers + 1)* sizeof(double*));
    layerOutputs[0] = x; //first layer output is treated as input x to the network
    //initialize the arrays to hold the output of each layer  
    for(int i = 1; i< numLayers+1;i++){
        layer currentLayer = (*network).lArray[i-1];
        int numNeuronsPerLayer = currentLayer.numNeurons;
        layerOutputs[i] = (double*)malloc(numNeuronsPerLayer * sizeof(double));
    }
    //Go through each layer and compute the output
    for(int i=1;i<numLayers+1;i++){
        layer currentLayer = (*network).lArray[i-1];
        int numNeuronsPerLayer = currentLayer.numNeurons;
        //go through each neuron in the layer
        //TODO: instead of processing the neurons in series try using forks and pipes
        int fdc[2], fdp[2];
        if (pipe(fdp) < 0){ //error testing the parent pipe
            perror("pipe() failed");
        }
        if (pipe(fdc) < 0){ //error testing the child pipe
            perror("pipe() failed");
        }
        pid_t pid = fork(); //forking
        if (pid < 0){ //error checking the forking
           perror("fork() failed");
        }
        if (pipe == 0){
           //run child
            close(fdc[0]);
            close(fdp[1]);
            for(int j=0; j < numNeuronsPerLayer/2; j++){
                layerOutputs[i][j] = ForwardPassNeuron(&currentLayer.nArray[j], layerOutputs[i-1]);
            }
            close(fdc[1]);
            close(fdp[0]);
        }
       //run parent
        close(fdc[1]);
        close(fdp[0]);
        for(int k=numNeuronsPerLayer/2; k < numNeuronsPerLayer; k++){
            layerOutputs[i][k] = ForwardPassNeuron(&currentLayer.nArray[k], layerOutputs[i-1]); 
        }
        close(fdc[0]);
        close(fdp[1]);


    }
    //save the final result
    (*network).output = layerOutputs[numLayers];
    //free up the memory (except the zeroth layer which is the input x and the last layer whose output we need)
    for(int i=1;i<numLayers;i++){
        free(layerOutputs[i]);
    }
}

void TestSimpleNetwork(){
    //size of the input
    int networkInputSize = 5;
    //layer structure of the network
    int numNeuronsPerLayer[6] = {4, 3, 7, 8, 2, 10};
    //number of layers 
    int numLayers = 6;
    //Build the network 
    networkFF network = InitializeNetwork(networkInputSize, numLayers, numNeuronsPerLayer);
    //sample input to the network, an array of size 5
     double x[5] = {2, 3, 4, 5, 6};
     //Do a forward pass on the network
    ForwardPassNetworkFF(x, &network);
    //print the output of the network 
    for(int i=0;i<10;i++){
        printf("y[%d]=%lf\n", i, network.output[i]);
    }
    printf("Simple neural network code complete!\n");
}

void TestBigNetwork(){
    //size of the input
    int networkInputSize = 10000;
    //layer structure of the network
    int numNeuronsPerLayer[6] = {40000, 3000, 7000, 8000, 200, 15};
    //number of layers 
    int numLayers = 6;
    //Build the network 
    networkFF network = InitializeNetwork(networkInputSize, numLayers, numNeuronsPerLayer);
    //sample input to the network, first index corresponds to sample number
    //second index corresponds to the dimensions associated with the sample 
     double x[100][10000];
     for(int i=0;i<100;i++){
        for(int j=0;j<10000;j++){
            x[i][j] = randomRangeZeroAndOne();
        }
     }
     //Do a forward pass on the network
    time_t start = time(NULL);
    for(int j=0;j<100;j++){
        printf("Currently working on sample:%d\n", j);
        ForwardPassNetworkFF(x[j], &network);
    }
    //print the time taken in seconds 
    printf("%.2f\n", (double)(time(NULL) - start));
    //print the output of the network 
    for(int i=0;i<15;i++){
        printf("y[%d]=%lf\n", i, network.output[i]);
    }
    printf("Big neural network code complete!\n");
}

//Main funtion
int main(int argc, char *argv[])
{
    if(strcmp("simple", argv[1]) == 0){
        TestSimpleNetwork();
    }
    if(strcmp("big", argv[1]) == 0){
        TestBigNetwork(); 
    }  
    else{
        printf("Command not recognized, nothing to do!");
    }
    return 0;
}
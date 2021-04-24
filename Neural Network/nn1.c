#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUTS 12									//Number of Inputs
#define N1 100										//Number of first layer neurons
#define N2 10										//Number of second layer neurons

double inputs[INPUTS];								//Inputs array		
double weights1[INPUTS][N1];						//First layer weights
double weights2[N1][N2];							//Second layer weights
double biases1[N1];									//First layer biases
double biases2[N2];									//Second layer biases
double DL1[N1];										//First layer inner state
double DL2[N2];										//Second layer inner state
double OL1[N1];										//Fisrt layer output
double OL2[N2];										//Second layer output

double Sigmoid(double x);
double DerSigmoid(double x);
void CreateInputs();
void CreateWeights();
void ActivateNN(double *vector);

int main() {										//Main function
	
	CreateInputs();
	CreateWeights();
	ActivateNN(inputs);
	
	return 0;
}

double Sigmoid(double x) {							//Sigmoid function
	
	return 1 / (1 + exp(-x));
}

void CreateInputs(){								//Random input creation
	
	int i;
	srand(time(NULL));
	
	for(i=0; i<INPUTS; i++){
		inputs[i] = (((((rand() % RAND_MAX) / (double)RAND_MAX))*2) - 1);	//Inputs in [-1,1]
	}
	
}

void CreateWeights(){								//Random weights and biases creation in [0, 0.1]
	
	int i,j,k;
	srand(time(NULL));
	
	for(i=0; i<INPUTS; i++){
		for(j=0; j<N1; j++){
			weights1[i][j] = ((rand() % RAND_MAX) / (double)RAND_MAX)/10;
		}
	}
	
	for(i=0; i<N1; i++){
		biases1[i] = ((rand() % RAND_MAX) / (double)RAND_MAX)/10;
		for(j=0; j<N2; j++){
			weights2[i][j] = ((rand() % RAND_MAX) / (double)RAND_MAX)/10;
		}
	}
	
	for(i=0; i<N2; i++){
		biases2[i] = ((rand() % RAND_MAX) / (double)RAND_MAX)/10;
	}

}


void ActivateNN(double *vector){							//Neural Net Activation Function
	
	int i,j;
	double neuron;
	
	for(i=0; i<N1; i++){									//For first layer
		neuron = biases1[i];								//Add bias
		for(j=0; j<INPUTS; j++){
			neuron += vector[j] * weights1[j][i];			//Add weight*input
		}
		DL1[i] = neuron;									
		OL1[i] = Sigmoid(neuron);							//Output
	}
	
	for(i=0; i<N2; i++){									//For second layer
		neuron = biases2[i];								//Add bias
		for(j=0; j<N1; j++){
			neuron += OL1[j] * weights2[j][i];				//Add weight*input
		}
		DL2[i] = neuron;
		OL2[i] = Sigmoid(neuron);							//Output
	}
	
	
}




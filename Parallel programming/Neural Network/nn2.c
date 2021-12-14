#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INPUTS 12									//Number of Inputs
#define N1 100										//Number of first layer neurons
#define N2 10										//Number of second layer neurons
#define LR 0.1
#define ITERATIONS 1000

double inputs[INPUTS];								//Inputs array		
double weights1[INPUTS][N1];						//First layer weights
double weights2[N1][N2];							//Second layer weights
double biases1[N1];									//First layer biases
double biases2[N2];									//Second layer biases
double DL1[N1];										//First layer inner state
double DL2[N2];										//Second layer inner state
double OL1[N1];										//Fisrt layer output
double OL2[N2];										//Second layer output
double desired[N2];


double Sigmoid(double x);
double DerSigmoid(double x);
void CreateInputs();
void CreateWeights();
void ActivateNN(double *vector);
void CreateDesired();
void TrainNN(double *inputs, double *desired);

int main() {										//Main function
	
	CreateInputs();
	CreateWeights();
	CreateDesired();
	TrainNN(inputs,desired);
	
	return 0;
}

double Sigmoid(double x) {							//Sigmoid function
	
	return 1 / (1 + exp(-x));
}

double DerSigmoid(double x){						//Derivative of Sigmoid function
	return x*(1-x);	
}

void CreateInputs(){								//Random input creation
	
	int i;
	srand(time(NULL));
	
	for(i=0; i<INPUTS; i++){
		inputs[i] = (((((rand() % RAND_MAX) / (double)RAND_MAX))*2) - 1);	//Inputs in [-1,1]
	}
	
}

void CreateWeights(){								//Random weights creation in [0,0.1] and biases in [0,1]
	
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

void CreateDesired(){										//Create desired results in [0,1] which is the range of
															//... possible values of the sigmoid function
	int i;
	srand(time(NULL));
	
	for(i=0; i<N2; i++){
		desired[i] = ((rand() % RAND_MAX) / (double)RAND_MAX);
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

void TrainNN(double *inputs, double *desired){				//Neural net training function
	
	double delta1[N1], delta2[N2], error, error_sum = 0;
	int i,j, iterations = 0;
	
	while(iterations<ITERATIONS){							//For the set number of iterations
		ActivateNN(inputs);									//Activation of neural net
		error_sum = 0;										//Initialization of sum of errors
		
		for(i=0; i<N2; i++){								//For every output
			error = (desired[i] - OL2[i]);					//Error calculation
            if(error>0)
			    error_sum += error;		
            else
                error_sum += -error;							
			delta2[i] = error * DerSigmoid(OL2[i]);			//Calculation of delta array for output layer
		}
		
		for(i=0; i<N1; i++){								//Back propagation to the hidden layer
			error = 0;
			for(j=0; j<N2; j++){
				error += delta2[j]*weights2[i][j];			//Error back propagation
			}
			delta1[i] = error*DerSigmoid(OL1[i]);			//Calculation of delta array for hidden layer
		}
		
		for(i=0; i<N2; i++){								//Weight updating for ouput layer
			biases2[i] += delta2[i]*LR;						//Biases updating	
			for(j=0; j<N1; j++){
				weights2[j][i] += OL1[j]*delta2[i]*LR;		//Weight updating
			}
		}
		
		for(i=0; i<N1; i++){								//Weight updating for hidden layer
			biases1[i] += delta1[i]*LR;						//Biases updating
			for(j=0; j<INPUTS; j++){
				weights1[j][i] += inputs[j]*delta1[i]*LR;	//Weight updating
			}
		}
		
		
		iterations ++;
		printf("Σφάλμα εκπαίδευσης επανάληψης %d: %f\n", iterations, error_sum);

	}
	
}




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define INPUTS 28*28									//Number of Inputs
#define N1 100										//Number of first layer neurons
#define N2 10										//Number of second layer neurons
#define LR 0.001
#define WEIGHT_DIVIDER 10000
#define N_TRAIN 60000
#define N_TEST  10000
#define EVALUATIONS 10000
#define EPOCHS 100
	
double weights1[INPUTS][N1];						//First layer weights
double weights2[N1][N2];							//Second layer weights
double biases1[N1];									//First layer biases
double biases2[N2];									//Second layer biases
double DL1[N1];										//First layer inner state
double DL2[N2];										//Second layer inner state
double OL1[N1];										//Fisrt layer output
double OL2[N2];										//Second layer output
int train_desired[N_TRAIN];
int test_desired[N_TEST];
double train_inputs[N_TRAIN][INPUTS];
double test_inputs[N_TEST][INPUTS];
double desired[N2];


double Sigmoid(double x);
double DerSigmoid(double x);
void CreateWeights();
void ActivateNN(double *vector);
void TrainNN(double *inputs, double *desired);
void ReadTrainingData();
void ReadTestData();
void Softmax(double * input, int length);
void TrainByMnistData();
void EvaluateByMnistData();
double ReLu(double x);
double DerReLu(double x);

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
#pragma GCC option("arch=native","tune=native","no-zero-upper") 

int main() {										//Main function
	
	CreateWeights();
	
	ReadTrainingData();
	TrainByMnistData();
	
	ReadTestData();
	EvaluateByMnistData();
	
	return 0;
}

double Sigmoid(double x) {							//Sigmoid function
	
	return 1 / (1 + exp(-x));
}

double DerSigmoid(double x){						//Derivative of Sigmoid function
	return x*(1-x);	
}

double ReLu(double x) {                             //ReLu function
	if(x<=0){
		return 0;
	}
	else return x;
}

double DerReLu(double x){                           //Derivative of ReLu function
	if(x<0){
		return 0;
	}
	else if(x > 0){
		return 1;
	}
}

void Softmax(double * input, int length){                   //Softmax function

    int i;
    float sum, max;

    for (i = 1, max = input[0]; i < length; i++) {
        if (input[i] > max) {
            max = input[i];
        }
    }

    for (i = 0, sum = 0; i < length; i++) {
        input[i] = exp(input[i] - max);
        sum += input[i];
    }

    for (i = 0; i < length; i++) {
        OL2[i] = input[i]/sum;
    }

}


void CreateWeights(){								//Random weights and biases creation  
	
	int i,j,k;
	srand(time(NULL));
	
	printf("Weight initialization... ");
	
	for(i=0; i<INPUTS; i++){
		for(j=0; j<N1; j++){
			weights1[i][j] = ((((rand() % RAND_MAX) / (double)RAND_MAX)*2)-1)/WEIGHT_DIVIDER;
		}
	}
	
	for(i=0; i<N1; i++){
		biases1[i] = ((((rand() % RAND_MAX) / (double)RAND_MAX)*2)-1)/WEIGHT_DIVIDER;
		for(j=0; j<N2; j++){
			weights2[i][j] = ((((rand() % RAND_MAX) / (double)RAND_MAX)*2)-1)/WEIGHT_DIVIDER;
		}
	}
	
	for(i=0; i<N2; i++){
		biases2[i] = ((((rand() % RAND_MAX) / (double)RAND_MAX)*2)-1)/WEIGHT_DIVIDER;
	}
	
	printf("Completed!\n");

}

void ReadTrainingData(){                                    //Training data read function
	
	printf("Saving train data... ");
	
    FILE *fp;
    fp = fopen("fashion-mnist_train.csv","r");
    if (fp == NULL) {
    	printf("Error! Couldn't find training file.\n");
	}
	
    char line[(INPUTS+1)*4];
    int i=0, j=0;
	
	char c;
	do {                                //Skipping csv labels (1st line)
  		c = fgetc(fp);
	} while (c != '\n');
	
	char *eptr;
    double number;
	
    while ((fgets(line, sizeof(line), fp)) != NULL && j<N_TRAIN){           //Iterate for every line of data
	
		i = 0;  	
        char* tmp = strdup(line);
        const char* token;  
		      
  		for (token = strtok(tmp, ",");                                     //Split line by commas
            token && *token;
            token = strtok(NULL, ",")){
            	number = strtod(token, &eptr);
            	if(i!=0){
            		train_inputs[j][i-1] = number/255.0;                   //Pixel Normalization
				}
				else{
					train_desired[j] = atoi(token);                        //Class saved
				}
            	i++;
		}
        j++;
        free(tmp);
    }

   fclose(fp);
   printf("Completed!\n");
   
}

void ReadTestData(){                                            //Test data read function
	
	printf("Saving evaluation data... ");
	
    FILE *fp;
    fp = fopen("fashion-mnist_test.csv","r");
    if (fp == NULL) {
    	printf("Error! Couldn't find test file.\n");
	}
	
    char line[(INPUTS+1)*4];
    int i=0, j=0;
	
	char c;
	do {                                //Skipping csv labels (1st line)
  		c = fgetc(fp);
	} while (c != '\n');
	
	char *eptr;
    double number;
	
    while ((fgets(line, sizeof(line), fp)) != NULL && j<N_TEST){    //Iterate for every line of data
	
		i = 0;  	
        char* tmp = strdup(line);
        const char* token;  
		      
  		for (token = strtok(tmp, ",");                              //Split line by commas
            token && *token;
            token = strtok(NULL, ",")){
            	number = strtod(token, &eptr);
            	if(i!=0){
            		test_inputs[j][i-1] = number/255.0;             //Pixel Normalization 
				}
				else{
					test_desired[j] = atoi(token);                  //Class saved
				}
            	i++;
		}
        j++;
        free(tmp);
    }

   fclose(fp);
   
   printf("Completed!\n");
   
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
		OL1[i] = ReLu(neuron);							//Output
	}
	
	for(i=0; i<N2; i++){									//For second layer
		neuron = biases2[i];								//Add bias
		for(j=0; j<N1; j++){
			neuron += OL1[j] * weights2[j][i];				//Add weight*input
		}
		DL2[i] = neuron;
	}
	
	Softmax(DL2, N2);
		
}

void TrainNN(double *inputs, double *desired){				//Neural net training function
	
	double delta1[N1], delta2[N2], error, error_sum = 0;
	int i,j, iterations = 0;
	
								
	ActivateNN(inputs);									//Activation of neural net
	error_sum = 0;										//Initialization of sum of errors
	
	for(i=0; i<N2; i++){								//For every output
		error = desired[i]*log(OL2[i]);					//Error calculation
		error_sum -= error;								
		delta2[i] =  OL2[i] - desired[i];		        //Calculation of delta array for output layer
	}
	
	for(i=0; i<N1; i++){								//Back propagation to the hidden layer
		error = 0;
		for(j=0; j<N2; j++){
			error -= delta2[j]*weights2[i][j];			//Error back propagation
		}
		delta1[i] = -error*DerReLu(OL1[i]);			    //Calculation of delta array for hidden layer
	}
	
	for(i=0; i<N2; i++){								//Weight updating for ouput layer
		biases2[i] -= delta2[i]*LR;						//Biases updating	
		for(j=0; j<N1; j++){
			weights2[j][i] -= OL1[j]*delta2[i]*LR;		//Weight updating
		}
	}
	
	for(i=0; i<N1; i++){								//Weight updating for hidden layer
		biases1[i] -= delta1[i]*LR;						//Biases updating
		for(j=0; j<INPUTS; j++){
			weights1[j][i] -= inputs[j]*delta1[i]*LR;	//Weight updating
		}
	}
	
	//printf("%f\n", error_sum);
			
}

void TrainByMnistData(){                                            //Training function using train data
	
	printf("Network training... ");
	
	int i, j, k, label;
	double max_p = 0, success, correct_evaluations = 0; 
	
    for(k=0; k<EPOCHS; k++){                                        //For every epoch
        for(i=0; i<N_TRAIN; i++){                                   //For all training data
		memset(desired, 0, sizeof(desired));
		desired[train_desired[i]] = 1;                              //Set desired position to 1
		TrainNN(train_inputs[i], desired);	                        //Train Neural Net
		
		for(j=0; j<N2; j++){
			if(OL2[j] > max_p){
				max_p = OL2[j];
				label = j;
			}
		}                                                           //Find predicted class
		
		if(label == train_desired[i]){
			correct_evaluations++;
		}
		
		max_p = 0;
			
	    }
    }
	
	
	success = (correct_evaluations/(N_TRAIN*EPOCHS))*100;
    printf("Completed!\n");
	printf("Training correct predictions percentage for %d epochs: %f%%\n", EPOCHS, success);
	
}

void EvaluateByMnistData(){                                         //Evaluating function using test data
	
	printf("Network evaluation... ");
	int i, j, desired_label, label, random_example, max_test_examples;
	double max_p = 0, success, correct_evaluations = 0; 
	
	if(N_TEST>10000){
		max_test_examples = 10000;
	}
	else{
		max_test_examples = N_TEST;
	}
	
	for(i=0; i<EVALUATIONS; i++){                                   //For the set number of evaluations
		
		random_example = rand() % max_test_examples;                //Get random test sample
		desired_label = test_desired[random_example];               //Get sample class
		ActivateNN(test_inputs[random_example]);                    //Activate neural net
		
		for(j=0; j<N2; j++){
			if(OL2[j] > max_p){
				max_p = OL2[j];
				label = j;
			}
		}                                                           //Get predicted class
		
		if(label == desired_label){
			correct_evaluations++;
		}
		
		max_p = 0;
	}
	
	success = (correct_evaluations/EVALUATIONS)*100;
	printf("Completed!\n");
	printf("Evaluation correct predictions percentage for %d random test data: %f%%\n", EVALUATIONS, success);
}




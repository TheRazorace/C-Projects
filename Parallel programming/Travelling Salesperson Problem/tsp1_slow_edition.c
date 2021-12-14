#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000							                    //Αριθμός πόλεων					
#define MAP_SIZE 1000                                       //Κάθετη και οριζόντια διάσταση χάρτη
#define DIMS 2                                              //Διαστάσεις δεδομένων
#define ITERATIONS 10000                                 //Αριθμός ελέγχων για κάθε διαδρομή

double cities[N][DIMS];                                      //Πίνακας που περιέχει τις πόλεις
int travel[N+1];                                            //Πίνακας που περιέχει την διαδρομή
int swapped[2];                                          //Πίνακας που περιέχει τις πόλεις που εναλλάχθηκαν

void CreateCities();
void CreateRandomTravel();
void PrintVec(double *a,int n,int nv);
double CalcDistance();
void SwapCities();
void RestoreCities();

int main(int argc, char *argv[]) {                          //Κύρια συνάρτηση
	
	double minimum_total_distance, new_dist;
	int i = 0;
	
	CreateCities();                                         //Δημιουργία δεδομένων
	//PrintVec(*cities,N,Dims);
	CreateRandomTravel();                                   //Αρχικοποίηση διαδρομής         
	
	minimum_total_distance = CalcDistance();                //Εύρεση πρώτης συνολικής απόστασης


	for(i=0; i<ITERATIONS; i++){          //Όσο η διαδρομή δεν είναι η επιθυμητή
		
		SwapCities();                                       //Εναλλαγή δύο πόλεων
        new_dist = CalcDistance();                          //Εύρεση νέας απόστασης
		
		if (new_dist<minimum_total_distance){               //Αν είναι συντομότερη oι έλεγχοι ξεκινούν από την αρχή
			minimum_total_distance = new_dist;              //Αντικατάσταση προηγούμενης απόστασης
		}
		else{                                               //Αν δεν είναι συντομότερη                                                           
			RestoreCities();                                //Επαναφορά της διαδρομής
		}	

	}

	printf("Ο αλγόριθμος ολοκληρώθηκε μετά από %d επαναλήψεις!\n", ITERATIONS);
	printf("Η μικρότερη διαδρομή έχει μήκος %f χιλιόμετρα.\n", minimum_total_distance);

	return 0;	
}

void CreateCities(void){					                //Συνάρτηση δημιουργίας δεδομένων						
	
	int i,j;
	srand(time(NULL));						                //Ορισμός seed					
	
	for(i=0; i<N; i++){
		for(j=0; j<DIMS; j++){
			cities[i][j] = ((rand() % RAND_MAX) / (double)RAND_MAX) * MAP_SIZE;		//Τυχαίες συντεταγμένες στο (0,1000)	
		}
	}

}

void CreateRandomTravel(){                                  //Συνάρτηση αρχικοποίησης διαδρομής
	int i;
	
	for(i=0; i<N; i++){                                     //Πρώτη διαδρομή η 0, 1, 2, ..., 999, 0
		travel[i] = i;
	}
	travel[N] = 0;

}

double CalcDistance(){                                           //Συνάρτηση υπολογισμού συνολικής διαδρομής
	
	int i,j;
	double dist = 0, temp;
	
	for(i=0; i<N; i++){											//Υπολογισμός απόστασης 2 πόλεων
		for(j=0; j<DIMS; j++){
			temp = cities[travel[i]][j] - cities[travel[i+1]][j]; 
			dist += temp*temp;									//Πρόσθεση στην συνολική απόσταση	  
		}
	}
	
	return dist;
}

void SwapCities(){                                      //Συνάρτηση εναλλαγής 2 πόλεων
	
	int temp;
	
	swapped[0] = rand()%(N-1) + 1;                      //Επιλογή 2 τυχαίων πόλεων εκτός από την πρώτη
	swapped[1] = rand()%(N-1) + 1;
	
	temp = travel[swapped[0]];                          //Εναλλαγή τους
	travel[swapped[0]] = travel[swapped[1]];
	travel[swapped[1]] = temp;
		
}

void RestoreCities(){                                   //Συνάρτηση επαναφοράς πόλεων
	
	int temp;
	temp = travel[swapped[1]];                          //Επιστροφή πόλεων στην προηγούμενή τους θέση
	travel[swapped[1]] = travel[swapped[0]];
	travel[swapped[0]] = temp;

}

/* void PrintVec(double *a, int n1, int n2){			    //Συνάρτηση εκτύπωσης 2D πίνακα		
	int i,j;
	
	for(i=0; i<n1; i++){
		for(j=0; j<n2; j++){
			printf("%f ", a[i*n2 + j]);
		}
		printf("\n");
	}
	printf("\n");
} */


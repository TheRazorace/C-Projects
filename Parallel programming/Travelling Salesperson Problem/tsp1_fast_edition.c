#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000							                    //Αριθμός πόλεων					
#define MAP_SIZE 1000                                       //Κάθετη και οριζόντια διάσταση χάρτη
#define DIMS 2                                              //Διαστάσεις δεδομένων
#define ITERATIONS 1000000                                   //Αριθμός ελέγχων για κάθε διαδρομή

double cities[N][DIMS];                                      //Πίνακας που περιέχει τις πόλεις
int travel[N+1];                                            //Πίνακας που περιέχει την διαδρομή
int swapped[2];                                          //Πίνακας που περιέχει τις πόλεις που εναλλάχθηκαν
double distances[N];                                        //Πίνακας με τις αποστάσεις ανάμεσα στις πόλεις της διαδρομής
float save_distances[4];									//Πίνακας με τις 2 αποστάσεις για κάθε μία από τις πόλεις που άλλαξαν
double minimum_total_distance;

void CreateCities();
void CreateRandomTravel();
void PrintVec(double *a,int n,int nv);
double CalcDistances(int start, int end);
double SwapCities();
void RestoreCities();

int main(int argc, char *argv[]) {                          //Κύρια συνάρτηση
	
	double new_dist;
	int i = 0;
	
	CreateCities();                                         //Δημιουργία δεδομένων
	//PrintVec(*cities,N,DIMS);
	CreateRandomTravel();                                   //Αρχικοποίηση διαδρομής         
	
	minimum_total_distance = CalcDistances(0, N);                //Εύρεση πρώτης συνολικής απόστασης
	
	while(i<ITERATIONS){                            //Όσο η διαδρομή δεν είναι η επιθυμητή
		
		new_dist = SwapCities();                             //Εναλλαγή δύο πόλεων

		if (new_dist<minimum_total_distance){                //Αν είναι συντομότερη οι έλεγχοι ξεκινούν από την αρχή
			minimum_total_distance = new_dist;               //Αντικατάσταση προηγούμενης απόστασης
		}
		else{                                               //Αν δεν είναι συντομότερη
			RestoreCities();                                //Επαναφορά της διαδρομής
		}	
		i++;
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

double CalcDistances(int start, int end){                                           //Συνάρτηση υπολογισμού συνολικής διαδρομής
	
	int i,j;
	double dist = 0, temp;
	
	for(i=start; i<end; i++){														//Υπολογισμός στα δοσμένα όρια
		distances[i] = 0;
		for(j=0; j<DIMS; j++){
			temp = cities[travel[i]][j] - cities[travel[i+1]][j];
			dist += temp*temp;
			distances[i] += temp*temp;													//Αποθήκευση στον πίνακα αποστάσεων
		}	
	}
	
	return dist;
}

double SwapCities(){                                      //Συνάρτηση εναλλαγής 2 πόλεων
	
	int temp;
	float new_dist, swapped_dist;
	
	swapped[0] = rand()%(N-1) + 1;                      //Επιλογή 2 τυχαίων πόλεων εκτός από την πρώτη
	swapped[1] = rand()%(N-1) + 1;

	save_distances[0] = distances[swapped[0] - 1];		//Αποθήκευση της απόστασης προς την πόλη...
	save_distances[1] = distances[swapped[0]];			//...και από την πόλη στο ταξίδι
	save_distances[2] = distances[swapped[1] - 1];
	save_distances[3] = distances[swapped[1]];

	//Αποθήκευση του συνόλου αυτών των αποστάσεων προς αλλαγή
	swapped_dist = save_distances[0] + save_distances[1] +\
				 save_distances[2] + save_distances[3];

	
	temp = travel[swapped[0]];                          //Εναλλαγή των πόλεων στην διαδρομή
	travel[swapped[0]] = travel[swapped[1]];
	travel[swapped[1]] = temp;

	//Υπολογισμός νέας απόστασης, αφαιρώντας το σύνολο των αποστάσεων που άλλαξαν...
	//...και προσθέτοντας τις νέες αποστάσεις μετά την εναλλαγή
	new_dist = minimum_total_distance - swapped_dist +\
		CalcDistances(swapped[0] - 1, swapped[0] + 1) +\
	    CalcDistances(swapped[1] - 1, swapped[1] + 1);

	return new_dist;
		
}

void RestoreCities(){                                   //Συνάρτηση επαναφοράς πόλεων
	
	int temp;
	temp = travel[swapped[1]];                          //Επιστροφή πόλεων στην προηγούμενή τους θέση
	travel[swapped[1]] = travel[swapped[0]];
	travel[swapped[0]] = temp;

	distances[swapped[0] - 1] = save_distances[0];		//Επαναφορά των αποστάσεων
	distances[swapped[0]] = save_distances[1];
	distances[swapped[1] - 1] = save_distances[2];
	distances[swapped[1]] = save_distances[3];

}

void PrintVec(double *a, int n1, int n2){			    //Συνάρτηση εκτύπωσης 2D πίνακα		
	int i,j;
	
	for(i=0; i<n1; i++){
		for(j=0; j<n2; j++){
			printf("%f ", a[i*n2 + j]);
		}
		printf("\n");
	}
	printf("\n");
}


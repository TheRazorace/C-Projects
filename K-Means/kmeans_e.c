#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define N 100000												//Ορισμός διαστάσεων
#define Nv 1000
#define Nc 100
#define THR_KMEANS 0.000001

#define pow(x) x*x											//Macro για υπολογισμό δύναμης

void CreateData(void);										//Δήλωση συναρτήσεων
void CreateCenters(void);
void Classification(void);
void EstimateCenters(void);
void PrintVec(float *a,int n,int nv);
float EuclidianDistance(float *v, float *c);
int Terminate(void);

float vec[N][Nv];											//Δημιουργία των 3 βασικών πινάκων
float center[Nc][Nv];
int classes[N];
float dist_sum = 0.0;										//Παλιό άθροισμα αποστάσεων από τα αντίστοιχα κέντρα
float new_dist_sum;											//Νέο (υπολογίζεται στο classification)

int main(int argc, char *argv[]) {							//Κύρια συνάρτηση
	
	int iterations=0;										//Μετρητής επαναλήψεων
	
	CreateData();
	//PrintVec(*vec,N,Nv);
	CreateCenters();
	//PrintVec(*center,Nc,Nv);
	
	do{
		Classification();
		//PrintVec(*distances,N,Nc);
		EstimateCenters();
		//PrintVec(*center,Nc,Nv);
		
		iterations++;
	} while(Terminate() && iterations<16);										//Όσο δεν υπάρχει σύγκλιση, επανάληψη των βημάτων 2,3
	
	printf("Iterations:%d \n", iterations);
	printf("Algorithm terminated succesfully!\n");
	return 0;
}

void CreateData(void){											//Δημιουργία τυχαίων δεδομένων
	
	int i,j;
	srand(time(NULL));											//Ορισμός seed χρησιμοποιώντας την ώρα συστήματος
	
	for(i=0; i<N; i++){
		for(j=0; j<Nv; j++){
			vec[i][j] = ((rand() % RAND_MAX) / (float)RAND_MAX - 0.5) * 4;			//Δημιουργία δεδομένων με την rand() στο (-2,2)
		}
	}

}

void CreateCenters(void){										//Επιλογή τυχαίων κέντρων από τα δεδομένα 
	
	memcpy(center, vec, sizeof(center));						//Επιλογή των πρώτων Νc δεδομένων ως τα πρώτα κέντρα
}

void Classification(void){										//Αντιστοίχιση δεδομένων με το κοντινότερο κέντρο
	
	int i, j, min_index;
	float min_dist,dist;
	new_dist_sum = 0.0;											//Άθροισμα των ελάχιστων αποστάσεων
		
	for(i=0; i<N; i++){											//Σάρωση για όλα τα δεδομένα
		min_dist = EuclidianDistance(vec[i],center[0]);			//Εύρεση μίας πρώτης απόστασης με το κέντρο 0
		min_index = 0;											//Αποθήκευση του index
		for(j=0; j<Nc; j++){									//Σύγκριση με την απόσταση για κάθε κέντρο
			dist = EuclidianDistance(vec[i],center[j]);
			if(dist<min_dist){									//Αν βρεθεί μικρότερη απόσταση αποθηκεύεται...
				min_dist=dist;									//...το μέγεθός της...
				min_index=j;									//...και το index της
			}
		}
		new_dist_sum += min_dist;								//Η ελάχιστη απόσταση από κέντρο προστίθεται στην μεταβλητή αυτή...
																//...που χρησιμοποιείται για τον έλεγχο σύγκλισης
		classes[i] = min_index;									//Η κλάση του σημείου είναι το index του κοντινότερου κέντρου
	}
	
}

float EuclidianDistance(float * v, float * c){					//Συνάρτηση υπολογισμού ευκλείδειας απόστασης
	
	int i;
	float dis=0.0;
	
	for(i=0; i<Nv; i++){										//Για κάθε διάσταση προστίθεται η το τετράγωνο της διαφοράς...
		dis += pow((v[i] - c[i]));								//...στην συνολική απόσταση με χρήση macro
	}
	
	return dis;	
}

void EstimateCenters(void){										//Υπολογισμός νέων κέντρων

	memset(center, 0, sizeof(center));							//Μηδενισμός του πίνακα με τα κέντρα
	int i,j,k,class_members = 0;								//Στην μεταβλητή class_members αποθηκεύεται το πλήθος των δεδομένων της κάθε κλάσης
	float f;

	for(i=0; i<Nc; i++){
		for(j=0; j<N; j++){
			if(classes[j]==i){									//Αν το δεδομένο ανήκει στην κλάση του κέντρου που εξετάζεται
				class_members++;								//Αυξάνεται το η class_members...
				for(k=0; k<Nv; k++){
					center[i][k] += vec[j][k];					//Και προστίθεται το δεδομένο στο νέο κέντρο
				}
			}
		}

		f = 1.0/class_members;								//Εύρεση μέσου όρου για τα νέα κέντρα
		for(j=0; j<Nv; j++){									//Loop Jamming						
			
			center[i][j] *= f;
		}
		class_members = 0;										//Μηδενισμός του class members για την επόμενη επανάληψη
	}

}

int Terminate(void){											//Έλεγχος σύγκλισης
	
	//printf("%f\n", fabs(new_dist_sum - dist_sum));
	if(fabs(new_dist_sum - dist_sum)>THR_KMEANS){				//Αν η μεταβολή των αποστάσεων είναι μεγαλύτερη του κατωφλιού...		
		dist_sum = new_dist_sum;								//...η νέα απόσταση παίρνει την θέση της παλιάς για την επόμενη
		return 1;												//...επανάληψη και ο αλγόριθμος επιστρέφει στο Classification
	} 
	else return 0;												//Αλλιώς τερματισμός του loop στο main
}

void PrintVec(float *a, int n1, int n2){						//Συνάρτηση τύπωσης πίνακα α διαστάσεων n1*n2
	int i,j;
	
	for(i=0; i<n1; i++){
		for(j=0; j<n2; j++){
			printf("%f ", a[i*n2 + j]);
		}
		printf("\n");
	}
	printf("\n");
}

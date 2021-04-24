#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 6                                             //Ορισμός διαστάσεων
#define Nv 2
#define Nc 2
#define THR_KMEANS 0.1

void CreateData(void);                                  //Δήλωση συναρτήσεων
void CreateCenters(void);
void Classification(void);
void EstimateCenters(void);
void PrintVec(float *a,int n,int nv);
int CheckIfTaken(int val);
float EuclidianDistance(float *v, float *c);
int Terminate(void);

float vec[N][Nv];                                     //Δημιουργία των 3 βασικών πινάκων
float center[Nc][Nv];
int classes[N];
int rand_array[Nc] = {-1};
float dist_sum = 0.0;                           //Παλιό άθροισμα αποστάσεων από τα αντίστοιχα κέντρα
float new_dist_sum;                             //Νέο (υπολογίζεται στο classification)

int main(int argc, char *argv[]) {                      //Κύρια συνάρτηση
	
	CreateData();
	//PrintVec(*vec,N,Nv);
	CreateCenters();
	//PrintVec(*center,Nc,Nv);
	
	do{
		Classification();
		//PrintVec(*distances,N,Nc);
		EstimateCenters();
		//PrintVec(*center,Nc,Nv);                      
		
	} while(Terminate());                               //Όσο δεν υπάρχει σύγκλιση, επανάληψη των βημάτων 2,3
	

	printf("Algorithm terminated succesfully!\n");
	return 0;
}

void CreateData(void){                                  //Δημιουργία τυχαίων δεδομένων
	
	int i,j;
	srand(time(NULL));                                  //Ορισμός seed χρησιμοποιώντας την ώρα συστήματος
	
	for(i=0; i<N; i++){
		for(j=0; j<Nv; j++){
			vec[i][j]=4.0*((rand()%1000000)/1000000.0);         //Δημιουργία δεδομένων με την rand() στο (0,4)
		}
	}
}

void CreateCenters(void){                               //Επιλογή τυχαίων κέντρων από τα δεδομένα 
	
	int i,j,rand_N;
	
	for(i=0; i<Nc; i++){
		
		do{
			rand_N = rand()%N;                          //Επιλογή τυχαίων indexes
		} while(CheckIfTaken(rand_N));                  //Έλεγχος αν το index αυτό έχει ξανα χρησιμοποιηθεί
		
		rand_array[i] = rand_N;                         //Αποθήκευση σε πίνακα που συγκεντρώνονται όλα τα indexes
		for(j=0; j<Nv; j++){
			center[i][j] = vec[rand_N][j];              //Δημιουργία κέντρων
		}
	}
	
}

int CheckIfTaken(int val){                              //Συνάρτηση ελέγχου μοναδικότητας των indexes
	
	int i;
	
	for(i=0; i<Nc; i++){
		if (val==rand_array[i]){
			return 1;
		}
	}
	return 0;
}

void Classification(void){                                          //Αντιστοίχιση δεδομένων με το κοντινότερο κέντρο
	
	int i, j, min_index;
	float min_dist,dist;
	new_dist_sum = 0.0;                                             //Άθροισμα των ελάχιστων αποστάσεων
		
	for(i=0; i<N; i++){                                             //Σάρωση για όλα τα δεδομένα
		min_dist = EuclidianDistance(vec[i],center[0]);             //Εύρεση μίας πρώτης απόστασης με το κέντρο 0
		min_index = 0;                                              //Αποθήκευση του index
		for(j=0; j<Nc; j++){                                        //Σύγκριση με την απόσταση για κάθε κέντρο
			dist = EuclidianDistance(vec[i],center[j]);
			if(dist<min_dist){                                      //Αν βρεθεί μικρότερη απόσταση αποθηκεύεται...
				min_dist=dist;                                      //...το μέγεθός της...
				min_index=j;                                        //...και το index της
			}
		}
		new_dist_sum += min_dist;                                   //Η ελάχιστη απόσταση από κέντρο προστίθεται στην μεταβλητή αυτή...
                                                                    //...που χρησιμοποιείται για τον έλεγχο σύγκλισης
		classes[i] = min_index;                                     //Η κλάση του σημείου είναι το index του κοντινότερου κέντρου
	}
	
}

float EuclidianDistance(float *v, float *c){                        //Συνάρτηση υπολογισμού ευκλείδειας απόστασης
	
	int i;
	float dis=0.0;
	
	for(i=0; i<Nv; i++){                                            //Για κάθε διάσταση προστίθεται η το τετράγωνο της διαφοράς...
		dis += (v[i] - c[i])*(v[i] - c[i]);                         //...στην συνολική απόσταση
	}
	
	return dis;	
}

void EstimateCenters(void){                                         //Υπολογισμός νέων κέντρων
	
	int i,j, class_members[Nc];                      //Στον πίνακα class_members αποθηκεύεται το πλήθος των δεδομένων της αντίστοιχης κλάσης
	float sums[Nc][Nv] = {0.0};                      //Στον πίνακα sum αποθηκεύεται το άθροισμα των δεδομένων που ανοίκουν...
	                                                //...στην ίδια κλάση
	
	for(i=0; i<N; i++){
		for(j=0; j<Nv; j++){
			sums[classes[i]][j] += vec[i][j];                       //Υπολογισμός αθροίσματος
		}
		class_members[classes[i]] = class_members[classes[i]] + 1;  //Υπολογισμός πλήθους δεδομένων της κλάσης
	}
	
	for(i=0; i<Nc; i++){
		for(j=0; j<Nv; j++){
			center[i][j] = sums[i][j]/( (float) class_members[i]);  //Διαίρεση αθροίσματος με το πλήθπς δεδομένων (μέσος όρος)...
		}                                                           //...για να υπολογιστούν τα νέα κέντρα
	}
}

int Terminate(void){                                                //Έλεγχος σύγκλισης
	
	//printf("%f\n", fabs(new_dist_sum - dist_sum));
	if(fabs(new_dist_sum - dist_sum)>THR_KMEANS){                   //Αν η μεταβολή των αποστάσεων είναι μεγαλύτερη του κατωφλιού...
		dist_sum = new_dist_sum;                                    //...η νέα απόσταση παίρνει την θέση της παλιάς για την επόμενη
		return 1;                                                   //...επανάληψη και ο αλγόριθμος επιστρέφει στο Classification
	} 
	else return 0;	                                                //Αλλιώς τερματισμός του loop στο main
}

void PrintVec(float *a, int n1, int n2){                            //Συνάρτηση τύπωσης πίνακα α διαστάσεων n1*n2
	int i,j;
	
	for(i=0; i<n1; i++){
		for(j=0; j<n2; j++){
			printf("%f ", a[i*n2 + j]);
		}
		printf("\n");
	}
	printf("\n");
}

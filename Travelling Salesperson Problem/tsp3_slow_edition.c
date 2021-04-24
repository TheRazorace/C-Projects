#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000							                    //Αριθμός πόλεων					
#define MAP_SIZE 1000                                       //Κάθετη και οριζόντια διάσταση χάρτη
#define DIMS 2                                              //Διαστάσεις δεδομένων

double cities[N][DIMS];                                //Πίνακας που περιέχει τις πόλεις
int travel[N+1];                                            //Πίνακας που περιέχει την 
double minimum_total_distance;

void CreateCities();
void PrintVec(double*a,int n,int nv);
double HeinritzHsiaoAlgorithm();
int CheckIfVisited(int index, int limit);
double CalcDistance(int city1, int city2);

int main(int argc, char *argv[]) {                          //Κύρια συνάρτηση

    int i;
    CreateCities();                                         //Δημιουργία δεδομένων
	//PrintVec(*cities,N,DIMS);
    minimum_total_distance = HeinritzHsiaoAlgorithm(); 
    
    printf("Ο αλγόριθμος ολοκληρώθηκε επιτυχώς!\n");
    printf("Η απόσταση της μικρότερης διαδρομής είναι %f.\n",minimum_total_distance);
    return 0;
}

void CreateCities(void){					                //Συνάρτηση δημιουργίας δεδομένων						
	
	int i,j;
	srand(time(NULL));						                //Ορισμός seed					
	
	for(i=0; i<N; i++){
		for(j=0; j<DIMS; j++){
			cities[i][j] = ((rand() % RAND_MAX) / (double)RAND_MAX) * MAP_SIZE;		//Τυχαίες συντεταγμένες στο (0,10) για ευκολότερους υπολογισμούς
		}
	}

}

double HeinritzHsiaoAlgorithm(){                                       //Συνάρτηση υλοποίησης αλγορίθμου

    int i, j, min_index;
    double dist, min_dist, total_dist=0;

    min_dist = DIMS*MAP_SIZE*MAP_SIZE;                                               //Ως αρχική μικρότερη απόσταση τίθεται η μέγιστη απόσταση...                                           //...που μπορεί να έχουν δύο πόλεις σε έναν χάρτη 1000x1000

    for(i=0; i<N-1; i++){                                                   //Για όλες τις πόλεις
        for(j=1; j<N; j++){

            if(!CheckIfVisited(j, i+1)){                                    //Έλεγχος αν η πόλη είναι ήδη στην διαδρομή
                dist = CalcDistance(travel[i],j);                           //Αν όχι, υπολογισμός απόστασης από την τρέχουσα πόλη
                if(dist<min_dist){                                          //Αν είναι μικρότερη από την εώς τώρα μικρότερη
                    min_dist = dist;                                        //Γίνεται αυτή η μικρότερη
                    min_index = j;                                          //Και αποθηκεύεται η θέση της
                }
            }
        }
        total_dist += min_dist;                                         //Προστίθεται η μικρότερη απόσταση στην συνολική
        travel[i+1] = min_index;
        min_dist = DIMS*MAP_SIZE*MAP_SIZE;                                           //Αρχικοποιέιται ξανά η μικρότερη απόσταση                                   
	}

    dist = CalcDistance(travel[N-1],0);                                     //Εύρεση απόστασης επιστροφής στην αρχική πόλη
    travel[N] = 0;                                                          //Πρόσθεση αρχικής πόλης στο ταξίδι
    total_dist += dist;                                                     //Πρόσθεση απόστασης στην συνολική διαδρομή

    return total_dist;                                          
}

int CheckIfVisited(int index, int limit){                                   //Συνάρτηση ελέγχου για το αν έχει επισκεφθεί μία πόλη

    int i;
    for(i = 0; i <limit; i++){                                              //Ο έλεγχος γίνεται έως το τρέχον σημείο του ταξιδιού
        if(travel[i] == index)                                              //Αν υπάρχει ήδη στο ταξίδι, επιστροφή 1 
            return 1;
    }
    return 0;                                                               //Αλλιώς 0
}

double CalcDistance(int city1, int city2){                             //Συνάρτηση υπολογισμού απόστασης 2 πόλεων

    int i;
	double dist = 0, temp;

    for(i=0; i<DIMS; i++){                                                  
		temp = cities[city1][i] - cities[city2][i];                         //Αφαίρεση των ανάλογων διαστάσεών τους
		dist += temp*temp;                                                  //Πρόσθεση στην συνολική απόσταση
	}

    return dist;
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
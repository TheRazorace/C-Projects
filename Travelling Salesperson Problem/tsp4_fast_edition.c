#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000							                    //Αριθμός πόλεων					
#define MAP_SIZE 1000                                       //Κάθετη και οριζόντια διάσταση χάρτη
#define DIMS 2                                              //Διαστάσεις δεδομένων
#define POSSIBILITY_OF_SHORTEST 90

double cities[N][DIMS];                              //Πίνακας που περιέχει τις πόλεις
int travel[N+1];                                       //Πίνακας που περιέχει την 
int cities_indexes[N-1];
double minimum_total_distance;

void CreateCities();
void CreateCitiesIndexes();
void PrintVec(double*a,int n,int nv);
double HeinritzHsiaoAlgorithm();
void RemoveIndex(int city1, int city2);
double CalcDistance(int city1, int city2);

int main(int argc, char *argv[]) {                          //Κύρια συνάρτηση

    int i;
    CreateCities();                                         //Δημιουργία δεδομένων
    CreateCitiesIndexes();
	//PrintVec(*cities,N,DIMS);
    minimum_total_distance = HeinritzHsiaoAlgorithm(); 

    printf("Ο αλγόριθμος ολοκληρώθηκε επιτυχώς!\n");
    printf("Η μικρότερη διαδρομή έχει μήκος %f χιλιόμετρα.\n", minimum_total_distance);

    return 0;
}

void CreateCities(void){					                //Συνάρτηση δημιουργίας δεδομένων						
	
	int i,j;
	srand(time(NULL));						                //Ορισμός seed					
	
	for(i=0; i<N; i++){
		for(j=0; j<DIMS; j++){
			cities[i][j] = ((rand() % RAND_MAX) / (double)RAND_MAX) * MAP_SIZE;		//Τυχαίες συντεταγμένες στο (0,1) για ευκολότερους υπολογισμούς
		}
	}

}

void CreateCitiesIndexes(){                                  //Συνάρτηση αρχικοποίησης διαδρομής
	int i;
	
	for(i=0; i<N; i++){                                     //Πρώτη διαδρομή η 0, 1, 2, ..., 999, 0
		cities_indexes[i] = i+1;
	}

}

double HeinritzHsiaoAlgorithm(){                                       //Συνάρτηση υλοποίησης αλγορίθμου

    int i, j, min_index, cities_left = N-1;
    int index_to_remove, index_to_remove2, min_index2, possibility;
    double dist, min_dist, min_dist2, total_dist=0;

    min_dist = 2*MAP_SIZE*MAP_SIZE;                                     //Ως αρχική μικρότερη απόσταση τίθεται η μέγιστη απόσταση...
    min_dist2 = 2*MAP_SIZE*MAP_SIZE;                                    //...που μπορεί να έχουν δύο πόλεις σε έναν χάρτη 1000x1000 χωρίς ρίζα

    for(i=0; i<N-1; i++){                                                   //Για όλες τις πόλεις
        for(j=0; j<cities_left; j++){

            dist = CalcDistance(travel[i],cities_indexes[j]);           //Αν όχι, υπολογισμός απόστασης από την τρέχουσα πόλη
            if(dist<=min_dist){                                          //Αν είναι μικρότερη από την εώς τώρα μικρότερη
                min_dist = dist;                                        //Γίνεται αυτή η μικρότερη
                min_index = cities_indexes[j];                           //Και αποθηκεύεται η θέση της
                index_to_remove = j;
            }
            else if(dist<min_dist2){
                min_dist2 = dist;
                min_index2 = cities_indexes[j];
                index_to_remove2 = j;
            }

        }

        possibility = rand()%100;                                           //Εύρεση τυχαίου ακεραίου στο (0,100)    
        if(possibility<= POSSIBILITY_OF_SHORTEST){                          //Αν είναι μικρότερος της πιθανότητας που τέθηκε 
            total_dist += min_dist;                                         //Προστίθεται η μικρότερη απόσταση στην συνολική
            travel[i+1] = min_index;                                        //Προστίθεται η θέση της στο ταξίδι
        }
        else{                                                               //Αλλιώς
            total_dist += min_dist2;                                        //Προστίθεται η δεύτερη μικρότερη απόσταση στην συνολική
            travel[i+1] = min_index2;                                       //Προστίθεται η θέση της στο 
            index_to_remove = index_to_remove2;
        }
      
        cities_left --;                                                     //Προστίθεται η θέση της στο ταξίδι      
        RemoveIndex(index_to_remove, cities_left);      
        min_dist = 2*MAP_SIZE*MAP_SIZE;                                     //Αρχικοποιέιται ξανά η μικρότερη απόσταση      
        min_dist2 = 2*MAP_SIZE*MAP_SIZE;                      
	}

    dist = CalcDistance(travel[N-1],0);                                     //Εύρεση απόστασης επιστροφής στην αρχική πόλη
    travel[N] = 0;                                                          //Πρόσθεση αρχικής πόλης στο ταξίδι
    total_dist += dist;                                                     //Πρόσθεση απόστασης στην συνολική διαδρομή

    return total_dist;                                          
}

void RemoveIndex(int city1, int city2){

    int temp;

    temp = cities_indexes[city1];                          //Εναλλαγή τους
	cities_indexes[city1] = cities_indexes[city2];
	cities_indexes[city2] = temp;

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


void PrintVec(double*a, int n1, int n2){			    //Συνάρτηση εκτύπωσης 2D πίνακα		
	int i,j;
	
	for(i=0; i<n1; i++){
		for(j=0; j<n2; j++){
			printf("%f ", a[i*n2 + j]);
		}
		printf("\n");
	}
	printf("\n");
}
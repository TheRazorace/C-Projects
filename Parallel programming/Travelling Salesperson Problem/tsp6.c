#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

//Problem parameters
#define CITIES 2000                                    //Αριθμός πόλεων 
#define DIMS 2                                          //Αριθμός διαστάσεων των πόλεων
#define ANTS 20                                         //Αριθμός μυρμηγκιών
#define MAP_SIZE 1000                                   //Κάθετη και οριζόντια διάσταση χάρτη
#define MAX_DIST DIMS*MAP_SIZE*MAP_SIZE                 //Μέγιστη απόσταση δύο πόλεων
#define MAX_TOTAL_DISTANCE 10000000                     //Για χάρη σύγκρισης, μια μέγιστη συνολική απόσταση
#define ALPHA 1                                         //Βάρος φερομόνης
#define BETA 1                                          //Βάρος απόστασης
#define QVAL 100                                        //Σταθερά πολλαπλασιασμού των κλασμάτων φερομόνης για έχει μεγαλύτερο βάρος
#define INIT_PHER (1.0/CITIES)                          //Αρχική ποσόστητα φερομόνης κάθε δρόμου
#define ITERATIONS 1                                   //Αριθμός επαναλήψεων αλγορίθμου


//Global structures
struct ant{                                             //Struct μυρμηγκιού
	
	int curCity, nextCity, pathIndex;                   //Μεταβλητές τρέχουσας, επόμενης πόλης και αριθμός πόλεων που έχουν επισκεφτεί
	int visited[CITIES];                                //Λίστα πόλεων που έχουν επισκεφτεί
	int path[CITIES];                                   //Μονοπάτι που ακολουθεί το κάθε μυρμήγκι
	float tourLength;                                   //Συνολική απόσταση διαδρομής
};

double distances[CITIES][CITIES];                       //Πίνακας όλων των αποστάσεων για κάθε πόλη με όλες τις άλλες
struct ant ants[ANTS];                                  //Πίνακας με όλα τα μυρμήγκια
double hormone[CITIES][CITIES];                         //Πίνακας όλων των φερομόνων για κάθε πόλη με όλες τις άλλες
double cities[CITIES][DIMS];                            //Πίνακας με όλες τις συντεταγμένες των πόλεων

float bestdistance = MAX_TOTAL_DISTANCE;                //Μικρότερη συνολική απόσταση
int bestIndex;                                          //Μυρμήγκι με την καλύτερη διαδρομή

void CreateCities();
double CalcDistances(int city1, int city2);
void CalcDistancesMatrix();
void InitializeAnts();
void RestartAnts();
double AntProduct(int from, int to);
int NextCity( int pos );
void SimulateAnts();
void UpdateFeromones();

int main(){

    int iterations = 0;

    CreateCities();                                            //Δημιουργία δεδομένων
    CalcDistancesMatrix();                                     //Υπολογισμός αποστάσεων και φερομόνων
    InitializeAnts();                                          //Ρύθμιση μυρμηγκιών

    while(iterations< ITERATIONS){ 
        SimulateAnts();                                        //Κίνηση μυρμηγκιών
        UpdateFeromones();                                     //Ενημέρωση πίνακα φερομόνων
        RestartAnts();                                         //Επαναρύθμισή τους
        iterations++; 
        printf("Καλύτερη απόσταση έως την επανάληψη %d: %lf\n", iterations, bestdistance);
    }

	return 0;
}


void CreateCities(){					                //Συνάρτηση δημιουργίας δεδομένων						
	
	int i,j;
	srand(time(NULL));						            //Ορισμός seed					
	
	for(i=0; i<CITIES; i++){
		for(j=0; j<DIMS; j++){
			cities[i][j] = ((rand() % RAND_MAX) / (double)RAND_MAX) * MAP_SIZE;		//Τυχαίες συντεταγμένες στο (0,1000)	
		}
	}

}

double CalcDistances(int city1, int city2){                       //Συνάρτηση υπολογισμού απόστασης 2 πόλεων
	
	int i;
	double dist = 0, temp;
	
	for(i=0; i<DIMS; i++){
		temp = cities[city1][i] - cities[city2][i];			
        dist += temp*temp;
	}	

	return dist;
}

void CalcDistancesMatrix(){                                     //Υπολογισμός πίνακα αποστάσεων και πίνακα φερομόνης
    int i= 0, j = 0, start = 1;

    for(i=0; i<CITIES; i++){
        for(j=start; j<CITIES; j++){
            distances[i][j] = CalcDistances(i,j);
            distances[j][i] = distances[i][j];
            hormone[i][j] = INIT_PHER;
            hormone[j][i] = INIT_PHER;
        }
        start++;
    }

}


void InitializeAnts(){                                      //Αρχικοποίηση μυρμηγκιών

    int i,k, init = 0;
    for( i = 0; i < ANTS; i++){                             //Για κάθε μυρμήγκι
        if(init == CITIES)
            init = 0;
  
        for(k = 0; k < CITIES; k++){                        
            ants[i].path[k] = -1;                           //Τοποθέτηση του -1 σε όλες τις θέσεις του μονοπατιού
        } 

        ants[i].curCity = init++;                           //Ορισμός αρχικής θέσης του μυρμηγκιού
        ants[i].pathIndex = 1;                              //Αρχικοποίηση του δείκτη του μονοπατιού
        ants[i].path[0] = ants[i].curCity;                  //Πρώτη πόλη του μονοπατιού
        ants[i].nextCity = -1;                              //Τοποθέτηση του -1 στον δείκτη της επόμενης πόλης
        ants[i].tourLength = 0;                             //Αρχικοποίηση διαδρομής
        ants[i].visited[ants[i].curCity] = 1;               //Ενημέρωση ότι έχει επισκεφτεί η πρώτη πόλη
    }
    
}


void RestartAnts(){                                         //Επαναρχικοποίηση μυρμηγκιών και αποθήκευση καλύτερης απόστασης...
                                                            //...στην ίδια συνάρτηση για λόγους χρόνου (ίδιος βρόγχος - loop jamming)
    int ant,i,to=0;

	for(ant = 0; ant < ANTS; ant++){

	    if(ants[ant].tourLength < bestdistance){            //Αποθήκευση καλύτερης διαδρομής
			bestdistance = ants[ant].tourLength;
			bestIndex = ant;
		}

		for(i = 0; i < CITIES; i++){                        //Αρχικοποίηση ξανά υπόλοιπων μεταβλητών
			ants[ant].visited[i] = 0;
			ants[ant].path[i] = -1;
		}
		
        ants[ant].nextCity = -1;
		ants[ant].tourLength = 0.0;
		ants[ant].curCity = rand()%CITIES;
		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;
		ants[ant].visited[ants[ant].curCity] = 1;
	}
}

double AntProduct(int from, int to){                            //Υπολογισμός αριθμητή πιθανότητας επόμενης διαδρομής...

   return (double) (( pow(hormone[from][to],ALPHA) * pow((1.0/ distances[from][to]), BETA))); //Με τις παραμέτρους ALPHA, BETA 
}

int NextCity( int pos ){                                       //Εύρεση επόμενης πόλης
	int from, to, destination;
	double denom = 0.0, p, max_p = 0;

	from = ants[pos].curCity;                                  

    for(to = 0; to < CITIES; to++){                            //Για κάθε πόλη
		if(ants[pos].visited[to] == 0){                        //Αν το μυρμήγκι δεν την έχει επισκεφτεί
		    //denom += antProduct( from, to );                 //Για καλύτερο χρόνο, δεν υπολογίζεται ο παρονομαστής που είναι κοινός
            p = (double) AntProduct(from,to);                  //Υπολογισμός αριθμητή πιθανότητας
            if(p>max_p){                                       //Αποθήκευση μεγαλύτερης πιθανότητας
                max_p = p;
                destination = to;                              //Και του προορισμού
            }
		}
	}
   
    //assert(denom != 0.0); 

	return destination;
}

void SimulateAnts(){

    int k; 
  
    for(k = 0; k < ANTS; k++){                                                       //Για όλα τα μυρμήγκια
        while( ants[k].pathIndex < CITIES ){                                         //Όσο δεν έχουν επισκεφτεί όλες τις πόλεις
		    ants[k].nextCity = NextCity(k);                                          //Εύρεση επόμενης πόλης μέσω πιθανοτήτων
		    ants[k].visited[ants[k].nextCity] = 1;                                   //Ενημέρωση πίνακα με τις πόλεις που έχει επισκεφτεί
		    ants[k].path[ants[k].pathIndex++] = ants[k].nextCity;                    //Ενημέρωση μονοπατιού
		    ants[k].tourLength += distances[ants[k].curCity][ants[k].nextCity];      //Ενημέρωση συνολικής διαδρομής
		    ants[k].curCity = ants[k].nextCity;                                      //Ορισμός νέας τρέχουσας πόλης
	    }
        ants[k].tourLength += distances[ants[k].path[CITIES -1]][ants[k].path[0]];   //Πρόσθεση της απόστασης για επιστροφή στην αρχική πόλη
    } 
}

void UpdateFeromones(){                                                 //Ενημέρωση πίνακα φερομόνων (χωρίς εξάτμιση τους)

    int from,to,i,ant;
	
	for(ant = 0; ant < ANTS; ant++){                                    //Για κάθε μυρμήγκι
	    for(i = 0; i < CITIES - 1; i++){	                            //Για όλες τις πόλεις
			from = ants[ant].path[i];                                   //Αποθήκευση μιας πόλης ...                                
		    to = ants[ant].path[i+1];                                   //... και της επόμενής της στο μονοπάτι

            hormone[from][to] += (QVAL/ ants[ant].tourLength);          //Ενημέρωση φερομόνης
	        hormone[to][from] = hormone[from][to];                      //Και της συμμετρικής θέσης στον πινακα
        }

	    from = ants[ant].path[i];                                      //Ίδια διαδικασία για την επιστροφή στην αρχική θέση
	    to = ants[ant].path[0];

	    hormone[from][to] += (QVAL/ ants[ant].tourLength);
	    hormone[to][from] = hormone[from][to];

    }
}






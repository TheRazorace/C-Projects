#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6                                      //Ορισμός διαστάσεων
#define Nc 2
#define Nv 2

void CreateData(void);                           //Δήλωση συναρτήσεων
void CreateCenters(void);
void Classification(void);
void EstimateCenters(void);
int Terminate(void);

float vec[N][Nv];                                //Δημιουργία των 3 βασικών πινάκων
float center[Nc][Nv];
int classes[N];

int main(int argc, char *argv[]) {               //Κύρια συνάρτηση
	
	CreateData();                                
	CreateCenters();
	
	do{
		Classification();
		EstimateCenters();
	} while(Terminate());                      //Όσο δεν υπάρχει σύγκλιση, επανάληψη των βημάτων 2,3
	
	printf("Algorithm terminated succesfully!\n");
	return 0;
}

void CreateData(void){                          //Δημιουργία τυχαίων δεδομένων
	
}

void CreateCenters(void){                       //Επιλογή τυχαίων κέντρων από τα δεδομένα 
	
}

void Classification(void){                      //Αντιστοίχιση δεδομένων με το κοντινότερο κέντρο
	
}

void EstimateCenters(void){                     //Υπολογισμός νέων κέντρων
	
}

int Terminate(void){                            //Έλεγχος σύγκλισης
	return 0;	
}


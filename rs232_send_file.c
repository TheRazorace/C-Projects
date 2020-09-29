#include <stdio.h> 
#include <dos.h> 
#include "com.h"
#include <stdlib.h>
#include <string.h>

/*  COM1 -> 3F8
	LSRA_COM1 -> 3FD
	COM2 -> 2F8
	LSRA_COM2 -> 2FD
	TRNSMT_EMPTY -> 20
	DATA_READY -> 1
*/

int send_char(char out_data);
void send_file_name(int res);
void send_file_contents(int res);
char file_name[20];

//Main συνάρτηση αποστολής
int main(int argc, char *argv[]){
	int res;
	
	res = com_init(COM1,0xEF);		//αρχικοποίηση COM1
	
	send_file_name(res);			//αποστολή ονόματος φακέλου
	send_file_contents(res);		//αποστολή περιεχομένων

	return 0;
}

//Συνάρτηση αποστολής περιεχομένων
void send_file_contents(int res){
	int i=0,sz;						//sz: μέγεθος περιεχομένων
	char *buffer;					//πίνακας αποθήκευσης περιεχομένων
	int ch;
	
	FILE *fptr;
	fptr = fopen(file_name,"rb");	//άνοιγμα φακέλου
	
	fseek(fptr, 0L, SEEK_END);
	sz = ftell(fptr);				//εύρεση μεγέθους
	buffer = malloc(sz);			//δυναμική κατανομή πίνακα
	rewind(fptr);					//επιστροφή στην αρχή του φακέλου
	
	while ((ch = fgetc(fptr)) != EOF){
		buffer[i++] = (char) ch;			//αποθήκευση κάθε χακτήρα του φακέλου στον πίνακα
	}
    fclose(fptr);					//κλείσιμο αρχείου 
	
	for(i=0; i<sz; i++){
		res = send_char(buffer[i]);									//αποστολή χαρακτήρα
		printf("com_transmit = %d char = %c\n", res, buffer[i]);    //εκτύπωση χαρακτήρα που στάλθηκε
	}
	res = send_char('\0');							//αποστολή null χαρακτήρα για τερματισμό λήψης από τον receiver
	printf("\nFile contents sent succesfully!\n");
}

//Συνάρτηση αποστολής ονόματος φακέλου
void send_file_name(int res){
	int i;
	FILE *fptr;
	
	printf("Type name of the file you want to send (add extention at the end): ");
	scanf("%s", &file_name);			//επιλογή φακέλου που θα σταλθεί


	fptr = fopen(file_name,"rb");		//άνοιγμα φακέλου
	if(fptr == NULL){
    	printf("Error! There is no such file. Try Again");   	
    	exit(1);             
    }
	
	for(i=0; i<strlen(file_name); i++){
		res = send_char(file_name[i]);		//αποστολή χαρακτήρα ονόματος φακέλου
		printf("com_transmit = %d char = %c\n", res, file_name[i]); //εκτύπωση χαρακτήρα
	}
	res = send_char('\0');					//αποστολή null χαρακτήρα για τερματισμό λήψης από τον receiver
	printf("\nFile name sent succesfully!\n");
	fclose(fptr);
	
}

//Συνάρτηση αποστολής χαρακτήρα με direct access 
int send_char(char out_data){

	while(!(inportb(0x3FD) & 0x20));	//έλεγχος αν ο transmitter register είναι άδειος 
	outportb(0x3F8, out_data);			//αποστολή χαρακτήρα
	return 0;
}

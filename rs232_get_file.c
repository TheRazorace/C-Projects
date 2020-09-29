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

char get_char(void);
char * get_file_name(void);
void get_file_contents(char *file_name);

//Main συνάρτηση λήψης
int main(int argc, char *argv[]){
	char *file_name;
	int res;
	
	res = com_init(COM2,0xEF);		//αρχικοποίηση COM2
	
	file_name = get_file_name();	//λήψη ονόματος φακέλου
	get_file_contents(file_name);	//λήψη περιεχομένων
	return 0;
}

//Συνάρτηση λήψης περιεχομένων
void get_file_contents(char *file_name){
	char ch;
	int i;
	FILE *fptr;
	fptr = fopen(file_name,"w");	//δημιουργία του φακέλου
	
	while ((ch = get_char())!='\0'){			//λήψη χαρακτήρων εώς ότου σταλθεί NULL χαρακτήρας
		printf("com_receive char = %c\n", ch);	//εκτύπωση χαρακτήρα
		fputc(ch,fptr);							//πρόσθεσή του στο αρχείο
	}
	printf("\nFile contents received succesfully!\n");
	printf("\nFile created succesfully!\n");
}

//Συνάρτηση λήψης ονόματος φακέλου
char * get_file_name(){
	char ch;
	int i;
	static char file_name[20] = "";		//όνομα φακέλου που θα δημιουργηθεί
	
	while ((ch = get_char())!='\0'){	//λήψη χαρακτήρων ονόματος εώς ότου ληφθεί NULL χαρακτήρας
		strncat(file_name, &ch, 1);		//πρόσθεση του χαρακτήρα στο string: file_name
		printf("com_receive char = %c\n", ch);	//εκτύπωση χαρακτήρα
	}
	printf("com_receive file name = %s\n", file_name);
	printf("\nFile name received succesfully!\n");
	return file_name;					//επιστροφή ονόματος φακέλου
}

//Συνάρτηση λήψης χαρακτήρα με direct access 
char get_char(void){
	char char_in;
	
	while(!(inportb(0x2FD) & 0x1));     //έλεγχος αν υπάρχει διαθέσιμος χαρακτήρας 
	char_in = inportb(0x2F8);			//αποθήκευση χακτήρα
	return char_in;						//επιστροφή χαρακτήρα
}





	

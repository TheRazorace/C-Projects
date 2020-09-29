#include <stdio.h> 
#include <dos.h> 
#include "com.h"
#include <stdlib.h>

/*  COM1 -> 3F8
	LSRA_COM1 -> 3FD
	COM2 -> 2F8
	LSRA_COM2 -> 2FD
	TRNSMT_EMPTY -> 20
	DATA_READY -> 1
*/

int send_char(char out_data);

int main(int argc, char *argv[]){
	char ch;
	int res;
	int i;
	
	res = com_init(COM1,0xEF);
	
	for(i=0; i<42; i++){
		res = send_char('1'+i);
		printf("com_transmit = %d char = %c\n", res,'1'+i);
	}
	system("PAUSE");
	return 0;
}

int send_char(char out_data){
	char res;
	
	while(!(inportb(0x3FD) & 0x20));
	outportb(0x3F8, out_data);
	return 0;
}













	

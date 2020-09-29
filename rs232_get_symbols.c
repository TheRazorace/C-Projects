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

char get_char(void);

int main(int argc, char *argv[]){
	char ch;
	int res;
	int i;
	
	res = com_init(COM2,0xEF);
	
	for(i=0; i<42; i++){
		ch = get_char();
		printf("com_receive char = %c\n", ch);
	}
	system("PAUSE");
	return 0;
}

char get_char(void){
	
	int res;
	char char_in;
	
	while(!(inportb(0x2FD) & 0x1));
	char_in = inportb(0x2F8);
	return char_in;
}












	

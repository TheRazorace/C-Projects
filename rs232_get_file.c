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

//Main ��������� �����
int main(int argc, char *argv[]){
	char *file_name;
	int res;
	
	res = com_init(COM2,0xEF);		//������������ COM2
	
	file_name = get_file_name();	//���� �������� �������
	get_file_contents(file_name);	//���� ������������
	return 0;
}

//��������� ����� ������������
void get_file_contents(char *file_name){
	char ch;
	int i;
	FILE *fptr;
	fptr = fopen(file_name,"w");	//���������� ��� �������
	
	while ((ch = get_char())!='\0'){			//���� ���������� ��� ���� ������� NULL ����������
		printf("com_receive char = %c\n", ch);	//�������� ���������
		fputc(ch,fptr);							//�������� ��� ��� ������
	}
	printf("\nFile contents received succesfully!\n");
	printf("\nFile created succesfully!\n");
}

//��������� ����� �������� �������
char * get_file_name(){
	char ch;
	int i;
	static char file_name[20] = "";		//����� ������� ��� �� ������������
	
	while ((ch = get_char())!='\0'){	//���� ���������� �������� ��� ���� ������ NULL ����������
		strncat(file_name, &ch, 1);		//�������� ��� ��������� ��� string: file_name
		printf("com_receive char = %c\n", ch);	//�������� ���������
	}
	printf("com_receive file name = %s\n", file_name);
	printf("\nFile name received succesfully!\n");
	return file_name;					//��������� �������� �������
}

//��������� ����� ��������� �� direct access 
char get_char(void){
	char char_in;
	
	while(!(inportb(0x2FD) & 0x1));     //������� �� ������� ���������� ���������� 
	char_in = inportb(0x2F8);			//���������� �������
	return char_in;						//��������� ���������
}





	

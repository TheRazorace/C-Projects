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

//Main ��������� ���������
int main(int argc, char *argv[]){
	int res;
	
	res = com_init(COM1,0xEF);		//������������ COM1
	
	send_file_name(res);			//�������� �������� �������
	send_file_contents(res);		//�������� ������������

	return 0;
}

//��������� ��������� ������������
void send_file_contents(int res){
	int i=0,sz;						//sz: ������� ������������
	char *buffer;					//������� ����������� ������������
	int ch;
	
	FILE *fptr;
	fptr = fopen(file_name,"rb");	//������� �������
	
	fseek(fptr, 0L, SEEK_END);
	sz = ftell(fptr);				//������ ��������
	buffer = malloc(sz);			//�������� �������� ������
	rewind(fptr);					//��������� ���� ���� ��� �������
	
	while ((ch = fgetc(fptr)) != EOF){
		buffer[i++] = (char) ch;			//���������� ���� ������� ��� ������� ���� ������
	}
    fclose(fptr);					//�������� ������� 
	
	for(i=0; i<sz; i++){
		res = send_char(buffer[i]);									//�������� ���������
		printf("com_transmit = %d char = %c\n", res, buffer[i]);    //�������� ��������� ��� ��������
	}
	res = send_char('\0');							//�������� null ��������� ��� ���������� ����� ��� ��� receiver
	printf("\nFile contents sent succesfully!\n");
}

//��������� ��������� �������� �������
void send_file_name(int res){
	int i;
	FILE *fptr;
	
	printf("Type name of the file you want to send (add extention at the end): ");
	scanf("%s", &file_name);			//������� ������� ��� �� �������


	fptr = fopen(file_name,"rb");		//������� �������
	if(fptr == NULL){
    	printf("Error! There is no such file. Try Again");   	
    	exit(1);             
    }
	
	for(i=0; i<strlen(file_name); i++){
		res = send_char(file_name[i]);		//�������� ��������� �������� �������
		printf("com_transmit = %d char = %c\n", res, file_name[i]); //�������� ���������
	}
	res = send_char('\0');					//�������� null ��������� ��� ���������� ����� ��� ��� receiver
	printf("\nFile name sent succesfully!\n");
	fclose(fptr);
	
}

//��������� ��������� ��������� �� direct access 
int send_char(char out_data){

	while(!(inportb(0x3FD) & 0x20));	//������� �� � transmitter register ����� ������ 
	outportb(0x3F8, out_data);			//�������� ���������
	return 0;
}

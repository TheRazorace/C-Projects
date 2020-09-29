#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void read_table(char table[7][7], float numbers[7]);
void print_table(char table[7][7], float numbers[7]);
void player1_plays(char table [7][7]);
void player2_plays(char table[7][7]);
void computer_plays(char table[7][7]);
int win_check(char table[7][7]);
void Run_Game_pvp();
void Run_Game_pvcpu();

int main() {
	int choice;
	printf("Let's play 4 in a row!\n");
	again:
	printf("Press 0 to play against the computer or 1 to play against another person:");
	scanf("%d", &choice);
	if(choice==1){Run_Game_pvp();}
	else if(choice==0){
		printf("WARNING! The computer is unbeatable!!!\n\n");
		Run_Game_pvcpu();
	}
	else{
		printf("Wrong number! Try again.\n");
		goto again;
	}
	return 0;
} 

//Creates the board and the numbers under the columns
void read_table(char table[7][7], float numbers[7]){
	int i,j;
	for(i=0; i<7; i++){
		for(j=0; j<7; j++){
			table[i][j]='-';
		}
	}
	for(i=0; i<7; i++){
		numbers[i]=i+1;
	}
}

//Prints the board and the numbers under the columns
void print_table(char table[7][7], float numbers[7]){
	int i,j;
	printf("\t\t\t\t\t\t\t\t");
	for(i=0; i<7; i++){
		for(j=0; j<7; j++){
			printf("  %c", table[i][j]);
		}printf("\n");
		printf("\t\t\t\t\t\t\t\t");
	}
	for(i=0; i<7; i++){
		printf("  %.0f", numbers[i]);
	}printf("\n");
	printf("\n");
}

//Player1 (+) plays choosing where to drop his disc
void player1_plays(char table [7][7]){
	int col,i,s=10;
	again:
	printf("Choose the column you want to drop your disc:");
	scanf("%d", &col);
	if(col<1 || col>7){
		printf("Wrong number! Try again.\n");
		goto again;}
	for(i=0; i<7; i++){
		if(table[i][col-1]=='-'){
			s=i;
		}
	}if(s==10){
		printf("The column is full! Try again.\n");
		goto again;
	}
	table[s][col-1]='+';
	printf("\n");
}

//Player2 (*) plays choosing where to drop his disc
void player2_plays(char table[7][7]){
	int col,i,s=10;
	again:
	printf("Choose the column you want to drop your disc:");
	scanf("%d", &col);
	if(col<1 || col>7){
		printf("Wrong number! Try again.\n");
		goto again;}
	for(i=0; i<7; i++){
		if(table[i][col-1]=='-'){
			s=i;
		}
	}if(s==10){
		printf("The column is full! Try again.\n");
		goto again;
	}
	table[s][col-1]='*';
	printf("\n");
}

//Computer (*) plays using if statements to constantly scan the  board
void computer_plays(char table[7][7]){
	int i,j,s=10,r;
	printf("Computer plays!\n");
	srand (time(NULL));	
	again:
	r=rand()%7+1 ;
	
															//1. PRIMARY ATTACK
	//Vertical
	for(j=0; j<7; j++){
		for(i=0; i<5; i++){
			if(table[i+1][j]=='*' && table[i+2][j]=='*' && table[i+3][j]=='*' && table[i][j]=='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	//Horizontal
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+1]=='*' && table[i][j+2]=='*' && table[i][j+3]=='-' && (table[i+1][j+3]!='-' || i==6)){
				table[i][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+1]=='*' && table[i][j+3]=='*' && table[i][j+2]=='-' && (table[i+1][j+2]!='-' || i==6)){
				table[i][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+2]=='*' && table[i][j+3]=='*' && table[i][j+1]=='-' && (table[i+1][j+1]!='-' || i==6)){
				table[i][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j+1]=='*' && table[i][j+2]=='*' && table[i][j+3]=='*' && table[i][j]=='-' && (table[i+1][j]!='-' || i==6)){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	//Diagonal(from left to right)
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+1][j+1]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='-' && table[i+4][j+3]!='-'){
				table[i+3][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+1][j+1]=='*' && table[i+3][j+3]=='*' && table[i+2][j+2]=='-' && table[i+3][j+2]!='-'){
				table[i+2][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='*' && table[i+1][j+1]=='-' && table[i+2][j+1]!='-'){
				table[i+1][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='*' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	//Diagonal(from right to left)
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+1][j-1]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='-' && table[i+4][j-3]!='-'){
				table[i+3][j-3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+1][j-1]=='*' && table[i+3][j-3]=='*' && table[i+2][j-2]=='-' && table[i+3][j-2]!='-'){
				table[i+2][j-2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='*' && table[i+1][j-1]=='-' && table[i+2][j-1]!='-'){
				table[i+1][j-1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i+1][j-1]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='*' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
																	//2. DEFENSE
	//Vertical
	for(j=0; j<7; j++){
		for(i=0; i<5; i++){
			if(table[i+1][j]=='+' && table[i+2][j]=='+' && table[i+3][j]=='+' && table[i][j]=='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	//Horizontal
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i][j+1]=='+' && table[i][j+2]=='+' && table[i][j+3]!='*' && (table[i+1][j+3]!='-' || i==6)){
				table[i][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i][j+1]=='+' && table[i][j+3]=='+' && table[i][j+2]!='*' && (table[i+1][j+2]!='-' || i==6)){
				table[i][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i][j+2]=='+' && table[i][j+3]=='+' && table[i][j+1]!='*' && (table[i+1][j+1]!='-' || i==6)){
				table[i][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j+1]=='+' && table[i][j+2]=='+' && table[i][j+3]=='+' && table[i][j]!='*' && (table[i+1][j]!='-' || i==6)){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	//Diagonal(from left to right)
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i+1][j+1]=='+' && table[i+2][j+2]=='+' && table[i+3][j+3]=='-' && table[i+4][j+3]!='-'){
				table[i+3][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i+1][j+1]=='+' && table[i+3][j+3]=='+' && table[i+2][j+2]=='-' && table[i+3][j+2]!='-'){
				table[i+2][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i+2][j+2]=='+' && table[i+3][j+3]=='+' && table[i+1][j+1]=='-' && table[i+2][j+1]!='-'){
				table[i+1][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='+' && table[i+2][j+2]=='+' && table[i+3][j+3]=='+' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	//Diagonal(from right to left)
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='+' && table[i+1][j-1]=='+' && table[i+2][j-2]=='+' && table[i+3][j-3]=='-' && table[i+4][j-3]!='-'){
				table[i+3][j-3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='+' && table[i+1][j-1]=='+' && table[i+3][j-3]=='+' && table[i+2][j-2]=='-' && table[i+3][j-2]!='-'){
				table[i+2][j-2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='+' && table[i+2][j-2]=='+' && table[i+3][j-3]=='+' && table[i+1][j-1]=='-' && table[i+2][j-1]!='-'){
				table[i+1][j-1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i+1][j-1]=='+' && table[i+2][j-2]=='+' && table[i+3][j-3]=='+' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
															//3. STRATEGY MOVES
				
	//Diagonal(from left to right)  - strategy point (defense)
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i+1][j+1]=='+' && table[i+2][j+2]=='+' && table[i+3][j+3]=='-' && table[i+4][j+3]=='-'){
				if(r-1==j+3){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i+1][j+1]=='+' && table[i+3][j+3]=='+' && table[i+2][j+2]=='-' && table[i+3][j+2]=='-'){
				if(r-1==j+2){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i+2][j+2]=='+' && table[i+3][j+3]=='+' && table[i+1][j+1]=='-' && table[i+2][j+1]=='-'){
				if(r-1==j+1){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='+' && table[i+2][j+2]=='+' && table[i+3][j+3]=='+' && table[i][j]=='-' && table[i+1][j]=='-'){
				if(r-1==j){goto again;}
				else{goto skip;}
			}
		}
	}
	
	//Diagonal(from right to left) - strategy point (defense)
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='+' && table[i+1][j-1]=='+' && table[i+2][j-2]=='+' && table[i+3][j-3]=='-' && table[i+4][j-3]=='-'){
				if(r-1==j-3){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='+' && table[i+1][j-1]=='+' && table[i+3][j-3]=='+' && table[i+2][j-2]=='-' && table[i+3][j-2]=='-'){
				if(r-1==j-2){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='+' && table[i+2][j-2]=='+' && table[i+3][j-3]=='+' && table[i+1][j-1]=='-' && table[i+2][j-1]=='-'){
				if(r-1==j-1){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i+1][j-1]=='+' && table[i+2][j-2]=='+' && table[i+3][j-3]=='+' && table[i][j]=='-' && table[i+1][j]=='-'){
				if(r-1==j){goto again;}
				else{goto skip;}
			}
		}
	}	
	
	//Diagonal(from left to right) - strategy point (attack)
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+1][j+1]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='-' && table[i+4][j+3]=='-'){
				if(r-1==j+3){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+1][j+1]=='*' && table[i+3][j+3]=='*' && table[i+2][j+2]=='-' && table[i+3][j+2]=='-'){
				if(r-1==j+2){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='*' && table[i+1][j+1]=='-' && table[i+2][j+1]=='-'){
				if(r-1==j+1){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='*' && table[i][j]=='-' && table[i+1][j]=='-'){
				if(r-1==j){goto again;}
				else{goto skip;}
			}
		}
	}
	
	//Diagonal(from right to left) - strategy point (attack)
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+1][j-1]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='-' && table[i+4][j-3]=='-'){
				if(r-1==j-3){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+1][j-1]=='*' && table[i+3][j-3]=='*' && table[i+2][j-2]=='-' && table[i+3][j-2]=='-'){
				if(r-1==j-2){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='*' && table[i+1][j-1]=='-' && table[i+2][j-1]=='-'){
				if(r-1==j-1){goto again;}
				else{goto skip;}
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i+1][j-1]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='*' && table[i][j]=='-' && table[i+1][j]=='-'){
				if(r-1==j){goto again;}
				else{goto skip;}
			}
		}
	}		
	
	//Straight line break
	for(i=0; i<7; i++){
		for(j=0; j<3; j++){
			if(table[i][j]=='-' && table[i][j+1]=='-' && table[i][j+2]=='+' && table[i][j+3]=='+' && table[i][j+4]=='-' && table[i+1][j+1]!='-'){
				table[i][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<3; j++){
			if(table[i][j]=='-' && table[i][j+1]=='+' && table[i][j+2]=='+' && table[i][j+3]=='-' && table[i][j+4]=='-' && table[i+1][j+3]!='-'){
				table[i][j+3]='*';
				goto end;
			}
		}
	}
	
	//'Corner' break														
	for(i=0; i<6; i++){
		for(j=0; j<5; j++){
			if(table[i][j]=='+' && table[i][j+1]=='+' &&  table[i+1][j+1]=='+' && table[i][j+2]=='-' && table[i+1][j+2]!='-' ){
				table[i][j+2]='*';
				goto end;
			}
		}
	}	
	
	for(i=0; i<6; i++){
		for(j=0; j<5; j++){
			if(table[i][j]=='-' && table[i][j+1]=='+' &&  table[i][j+2]=='+' && table[i+1][j+1]=='+' && table[i+1][j]!='-' ){
				table[i][j]='*';
				goto end;
			}
		}
	}												
	
	
															//4. SECONDARY MOVE
	//Horizontal
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+1]=='*' && table[i][j+2]=='-' && table[i][j+3]=='-' && (table[i+1][j+3]!='-' || i==6)){
				table[i][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+1]=='*' && table[i][j+2]=='-' && table[i][j+3]=='-' && (table[i+1][j+2]!='-' || i==6)){
				table[i][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+1]=='-' && table[i][j+3]=='*' && table[i][j+2]=='-' && (table[i+1][j+2]!='-' || i==6)){
				table[i][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+1]=='-' && table[i][j+3]=='*' && table[i][j+2]=='-' && (table[i+1][j+1]!='-' || i==6)){
				table[i][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+2]=='*' && table[i][j+3]=='-' && table[i][j+1]=='-' && (table[i+1][j+1]!='-' || i==6)){
				table[i][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i][j+2]=='*' && table[i][j+3]=='-' && table[i][j+1]=='-' && (table[i+1][j+3]!='-' || i==6)){
				table[i][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j+1]=='*' && table[i][j+2]=='*' && table[i][j+3]=='-' && table[i][j]=='-' && (table[i+1][j]!='-' || i==6)){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j+1]=='*' && table[i][j+2]=='*' && table[i][j+3]=='-' && table[i][j]=='-' && (table[i+1][j+3]!='-' || i==6)){
				table[i][j+3]='*';
				goto end;
			}
		}
	}
	
	//Diagonal(from left to right)
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+1][j+1]=='*' && table[i+2][j+2]=='-' && table[i+3][j+3]=='-' && table[i+4][j+3]!='-'){
				table[i+3][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+1][j+1]=='*' && table[i+2][j+2]=='-' && table[i+3][j+3]=='-' && table[i+3][j+2]!='-'){
				table[i+2][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+1][j+1]=='-' && table[i+3][j+3]=='*' && table[i+2][j+2]=='-' && table[i+3][j+2]!='-'){
				table[i+2][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+1][j+1]=='-' && table[i+3][j+3]=='*' && table[i+2][j+2]=='-' && table[i+2][j+1]!='-'){
				table[i+1][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='-' && table[i+1][j+1]=='-' && table[i+2][j+1]!='-'){
				table[i+1][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='-' && table[i+1][j+1]=='-' && table[i+4][j+3]!='-'){
				table[i+3][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='-' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='-' && table[i][j]=='-' && table[i+4][j+3]!='-'){
				table[i+3][j+3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='*' && table[i+2][j+2]=='-' && table[i+3][j+3]=='*' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='*' && table[i+2][j+2]=='-' && table[i+3][j+3]=='*' && table[i][j]=='-' && table[i+3][j+2]!='-'){
				table[i+2][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='-' && table[i+2][j+2]=='*' && table[i+3][j+3]=='*' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i+1][j+1]=='-' && table[i+2][j+2]=='*' && table[i+3][j+3]=='*' && table[i][j]=='-' && table[i+2][j+1]!='-'){
				table[i+1][j+1]='*';
				goto end;
			}
		}
	}
	
	//Diagonal(from right to left)
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+1][j-1]=='*' && table[i+2][j-2]=='-' && table[i+3][j-3]=='-' && table[i+4][j-3]!='-'){
				table[i+3][j-3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+1][j-1]=='*' && table[i+2][j-2]=='-' && table[i+3][j-3]=='-' && table[i+3][j-2]!='-'){
				table[i+2][j-2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+1][j-1]=='-' && table[i+3][j-3]=='*' && table[i+2][j-2]=='-' && table[i+3][j-2]!='-'){
				table[i+2][j-2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+1][j-1]=='-' && table[i+3][j-3]=='*' && table[i+2][j-2]=='-' && table[i+2][j-1]!='-'){
				table[i+1][j-1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='-' && table[i+1][j-1]=='-' && table[i+2][j-1]!='-'){
				table[i+1][j-1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='-' && table[i+1][j-1]=='-' && table[i+4][j-3]!='-'){
				table[i+3][j-3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i+1][j-1]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='-' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i+1][j-1]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='-' && table[i][j]=='-' && table[i+4][j-3]!='-'){
				table[i+3][j-3]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i+1][j-1]=='*' && table[i+2][j-2]=='-' && table[i+3][j-3]=='*' && table[i][j]=='-' && table[i+1][j]!='-'){
				table[i][j]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i+1][j-1]=='*' && table[i+2][j-2]=='-' && table[i+3][j-3]=='*' && table[i][j]=='-' && table[i+3][j-2]!='-'){
				table[i+2][j-3]='*';
				goto end;
			}
		}
	}
	
	//Vertical
	for(j=0; j<7; j++){
		for(i=0; i<6; i++){
			if(table[i+1][j]=='-' && table[i+2][j]=='*' && table[i+3][j]=='*'){
				table[i+1][j]='*';
				goto end;
			}
		}	
	}
	
	//Stick to enemy strategy	
	for(i=0; i<7; i++){
		for(j=0; j<6; j++){
			if(table[i][j]!='-' && table[i][j+1]=='+' && table[i][j+2]=='+' && table[i-1][j]=='-'){
				table[i-1][j]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<6; j++){
			if(table[i][j]=='+' && table[i][j+1]=='+' && table[i][j+2]!='-' && table[i-1][j+2]=='-'){
				table[i-1][j+2]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<6; j++){
			if(table[i][j]=='+' && table[i][j+1]=='-' && (table[i+1][j+1]!='-' || i==6)){
				table[i][j+1]='*';
				goto end;
			}
		}
	}
	
	for(i=0; i<7; i++){
		for(j=0; j<6; j++){
			if(table[i][j]=='-' && table[i][j+1]=='+' && (table[i+1][j]!='-' || i==6)){
				table[i][j]='*';
				goto end;
			}
		}
	}
		
	skip:
	for(i=0; i<7; i++){
		if(table[i][r-1]=='-'){
			s=i;
		}
	}if(s==10){goto again;}
	table[s][r-1]='*';
	end:
	printf("\n");
}

//Checks for a winner
int win_check(char table[7][7]){
	int i,j;
	for(i=0; i<7; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i][j+1]=='+' && table[i][j+2]=='+' && table[i][j+3]=='+'){return 1;}
			if(table[i][j]=='*' && table[i][j+1]=='*' && table[i][j+2]=='*' && table[i][j+3]=='*'){return 1;}
		}
	}
	for(j=0; j<7; j++){
		for(i=0; i<4; i++){
			if(table[i][j]=='+' && table[i+1][j]=='+' && table[i+2][j]=='+' && table[i+3][j]=='+'){return 1;}
			if(table[i][j]=='*' && table[i+1][j]=='*' && table[i+2][j]=='*' && table[i+3][j]=='*'){return 1;}
		}
	}
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(table[i][j]=='+' && table[i+1][j+1]=='+' && table[i+2][j+2]=='+' && table[i+3][j+3]=='+'){return 1;}
			if(table[i][j]=='*' && table[i+1][j+1]=='*' && table[i+2][j+2]=='*' && table[i+3][j+3]=='*'){return 1;}
		}
	}
	for(i=0; i<4; i++){
		for(j=3; j<7; j++){
			if(table[i][j]=='+' && table[i+1][j-1]=='+' && table[i+2][j-2]=='+' && table[i+3][j-3]=='+'){return 1;}
			if(table[i][j]=='*' && table[i+1][j-1]=='*' && table[i+2][j-2]=='*' && table[i+3][j-3]=='*'){return 1;}
		}
	}
	return 0;
}

//Runs game (Human vs Human)
void Run_Game_pvp(){
	int q=0,draw=0;
	char table[7][7];
	float numbers[7];
	read_table(table, numbers);
	print_table(table, numbers);
	while(!q){
		printf("Player1 plays!\n");
		player1_plays(table);
		draw++;
		print_table(table, numbers);
		if(draw==49){
				printf("It is a draw!");
				break;
			}
		win_check(table);
		if(win_check(table)){
			printf("Player1 wins!\n");
			break;
		}
		printf("Player2 plays!\n");
		player2_plays(table);
		draw++;
		print_table(table, numbers);
		win_check(table);
		if(win_check(table)){
			printf("Player2 wins!\n");
			break;
		}
	}
}

//Runs Game (Human vs Computer)
void Run_Game_pvcpu(){
	int q=0,coin,draw=0;
	char table[7][7];
	float numbers[7];
	printf("Time for coin toss. Choose 0 for heads or 1 for tails:");
	scanf("%d", &coin);
	srand (time(NULL));
	read_table(table, numbers);
	print_table(table, numbers);
	if(coin==rand()%2){
		printf("You play first!\n");
		while(!q){
			printf("Your turn!\n");
			player1_plays(table);
			draw++;
			print_table(table, numbers);
			if(draw==49){
				printf("It is a draw!");
				break;
			}
			win_check(table);
			if(win_check(table)){
				printf("You win!\n");
				break;
			}
			computer_plays(table);
			draw++;
			print_table(table, numbers);
			win_check(table);
			if(win_check(table)){
			printf("Computer wins!\n");
			break;
			}
		}
	}else{
		printf("Computer plays first!\n");
		while(!q){
			computer_plays(table);
			draw++;
			print_table(table, numbers);
			if(draw==49){
				printf("It is a draw!");
				break;
			}
			win_check(table);
			if(win_check(table)){
				printf("Computer wins!\n");
				break;
			}
			printf("Your turn!\n");
			player1_plays(table);
			draw++;
			print_table(table, numbers);
			win_check(table);
		if(win_check(table)){
			printf("You win!\n");
			break;
			}
		}
	}
}

